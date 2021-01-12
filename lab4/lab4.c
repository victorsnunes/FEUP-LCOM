// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"
#include "utils.h"
#include "timer.h"
#include "i8254.h"
#include "i8042.h"

extern uint8_t bytes[3];
extern int b;
extern int timer_counter;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  //lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) { 

  uint8_t mouse_bit = MOUSE_IRQ_PIC2;
  int r, ipcStatus;
  message msg;

  if (mouse_enable_data_reporting() != 0)
    return 1;

  if (mouse_subscribe_int(&mouse_bit) != 0)
    return 2;

  while (cnt > 0)
  {
    if ((r = driver_receive(ANY, &msg, &ipcStatus)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipcStatus))
    {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if (msg.m_notify.interrupts & mouse_bit)
        {
          mouse_ih();          

          if (b == 0) {
             struct packet pckt;
             create_packet(&pckt, bytes);
             mouse_print_packet(&pckt);
             cnt--;
          }
        }
        break;
      default:
        break;
      }
    }
  }

  if (mouse_unsubscribe_int() != 0)
    return 3;

  if (set_mouse_to_minix_default() != 0)
    return 4;

  return 0;
}



int (mouse_test_async)(uint8_t idle_time) {

  uint8_t mouse_bit = MOUSE_IRQ_PIC2;
  uint8_t timer_bit = TIMER0_IRQ;
  int r, ipcStatus;
  message msg;

  if (mouse_enable_data_reporting() != 0)
    return 1;

  if (mouse_subscribe_int(&mouse_bit) != 0)
    return 2;

  if (timer_subscribe_int(&timer_bit) != 0)
    return 3;

  while (timer_counter/60 < idle_time)
  {
    if ((r = driver_receive(ANY, &msg, &ipcStatus)) != 0)
    {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipcStatus))
    {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:

        if (msg.m_notify.interrupts & timer_bit){
          timer_int_handler();
        }

        if (msg.m_notify.interrupts & mouse_bit)
        {
          mouse_ih();          
          timer_counter = 0;
          if (b == 0) {
             struct packet pckt;
             create_packet(&pckt, bytes);
             mouse_print_packet(&pckt);
          }
        }
        break;
      default:
        break;
      }
    }
  }

  if (mouse_unsubscribe_int() != 0)
    return 4;

  if (timer_unsubscribe_int() != 0)
    return 5;

  if (set_mouse_to_minix_default() != 0)
    return 6;

  return 0;

}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* To be completed */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}