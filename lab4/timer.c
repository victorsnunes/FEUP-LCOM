#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "timer.h"
#include "i8254.h"

static int hook_id;
int timer_counter = 0;

///////////////////////////// SETTING //////////////////////////////////////////////////////////

int (timer_set_frequency)(uint8_t timer, uint32_t freq) { //Changes the operating frequency of a timer. Must use the read-back command

  if (freq < 19 || freq > TIMER_FREQ)
    return 1;

  uint8_t st; //status 
  uint16_t div =  TIMER_FREQ/freq;
  
  if(timer_get_conf(timer,&st) != OK)  //read-back command
    return 1;

  uint8_t control_word = st & 0x0F;
  control_word = control_word | TIMER_LSB_MSB;

  switch(timer){
    case 0:
      control_word = control_word | TIMER_SEL0;
      break;
    case 1:
      control_word = control_word | TIMER_SEL1;
      break;
    case 2:
      control_word = control_word | TIMER_SEL2;
      break;
  }

  sys_outb(TIMER_CTRL, control_word);
  uint8_t lsb, msb;

  util_get_LSB(div, &lsb);
  util_get_MSB(div, &msb);

  if(sys_outb(TIMER_0 + timer, lsb) != OK) return 1;
  if(sys_outb(TIMER_0 + timer, msb) != OK) return 1;

  return 0;
}


/////////////////////////////// INTERRUPTIONS ///////////////////////////////////////////////////////


int (timer_subscribe_int)(uint8_t *bit_no) {

  hook_id = *bit_no;

  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK)
    return 1;

  *bit_no = BIT(*bit_no);
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id)!= OK)
    return 1;
  
  return 0;    
    
}


void (timer_int_handler)() {
  timer_counter++;
}


/////////////////////////////////////// CONFS ////////////////////////////////////////////

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(timer < 0 || timer > 2) 
    return 1;

  uint8_t cmd = 0;
  cmd = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);

  if ( sys_outb(TIMER_CTRL, cmd) != OK ){
    printf("Error in sys_outb()\n");
  }

  uint32_t lst;

  if ( sys_inb(TIMER_0, &lst) != OK ){
    printf("Error in sysinb()\n");
    return 1;
  }
  else {
    *st = lst;
    return 0;
  }

  return 1;
}



int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {

  union timer_status_field_val val;
  switch (field) {
    case 0:
      val.byte = st;
      break;

    case 1:
      val.in_mode = st>>4 & 0x03;
      break;

    case 2:
      val.count_mode = st>>1 & 0x07;
      break;

    case 3:
      val.bcd = st & 0x01;
      break;
  }
  timer_print_config(timer, field, val);

  return 0;
}
