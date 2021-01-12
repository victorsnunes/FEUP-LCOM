 #include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdint.h>

#include "i8042.h"

int kbc_hook_id = KEYBOARD_IRQ;
uint32_t sysCounter =0;
uint8_t keyScanned;
uint8_t scanBytes[2];
uint8_t size = 0; 


int kbd_subscribe_int(uint8_t *bit_no)
{
  kbc_hook_id = (int)*bit_no;

  if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_hook_id) != OK)
    return 1;
  
  *bit_no = (uint8_t) BIT(*bit_no);
  return 0;
}

int kbd_unsubscribe_int()
{
  if (sys_irqrmpolicy(&kbc_hook_id) != OK)
    return 1;
  
  return 0;
}

int cnt_sys_inb(uint8_t adress, uint8_t *stat){ //count the number of sys_inb calls
	sysCounter++;
	return util_sys_inb(adress, stat);
}

void (kbc_ih)(void) //Handles keyboard interrupts 
{
  uint8_t status, key;
  cnt_sys_inb(STAT_REG, &status);
  if((status & (PARITY | TIME_OUT)) == 0)
  {
    if(util_sys_inb(OUT_BUF, &key) == 0)
      keyScanned = key;
  }
}

int kbc_read() //read status and send command
{
  uint8_t stat;
  while(1){
  if (util_sys_inb(STAT_REG, &stat) == 1) 
    return 1;
  if (stat & OBF)
  {
    kbc_ih();
    return 0;
  }
  tickdelay(micros_to_ticks(DELAY));
  }

  return 1;
}

void kbd_scancode()
{
  scanBytes[size] = keyScanned;
  size++;
  if (keyScanned != FIRST_BYTE)
  {
    kbd_print_scancode((keyScanned & BREAK_CODE) == 0, size, scanBytes);
    size = 0;
  }
}

int kbc_enable_interrupt() // KBC commands
{
  uint8_t stat, cmd;

  if (util_sys_inb(STAT_REG, &stat) != 0)
    return 1;

  if ((stat & IBF) == 1) //IBF is BIT 1 of status register, see if its full
    return 1;

  if (sys_outb(CMD_REG, READ_CMD) != 0) //the value of the “command byte” must be read from 0x60
    return 1;

  if (util_sys_inb(OUT_BUF, &cmd) != 0) //puts command in the outbuffer
    return 1;
  
  cmd = cmd | EN_KBD; //enable interrupt on OBF, from keyboard

  if (sys_outb(CMD_REG, WRITE_CMD) != 0) // the new value of the “command byte” must be written to 0x60
    return 1;

  if (sys_outb(IN_BUF, cmd) != 0)
    return 1;

  return 0;
}

