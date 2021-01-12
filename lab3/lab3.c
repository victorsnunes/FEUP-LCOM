#include <lcom/lcf.h>

#include <lcom/lab3.h>
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "utils.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>


extern uint8_t keyScanned;
extern uint32_t sysCounter;
extern uint8_t size;
extern int kbc_hook_id;
extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {

  uint8_t bit_no = KEYBOARD_IRQ;
  int ipc_status;
  int r;
  message msg;

    if (kbd_subscribe_int(&bit_no) != 0)
      return 1;

  while(keyScanned != ESC) { 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) 
    { 
      switch (_ENDPOINT_P(msg.m_source)) 
      {
        case HARDWARE: 
          if (msg.m_notify.interrupts & bit_no) 
          {
          kbc_ih();
          kbd_scancode();
          }
          break;

        default:
          break;
      }
    } 
    else {}
  }

  kbd_print_no_sysinb(sysCounter);
  if (kbd_unsubscribe_int() != 0)
    return 1;

  return 0;
}

int(kbd_test_poll)() {
  sysCounter = 0;
  size = 0;
  while (keyScanned != ESC)
  {
    while (kbc_read())
    {
      tickdelay(micros_to_ticks(DELAY));
    }
    kbd_scancode();
  }

  kbc_enable_interrupt();
  kbd_print_no_sysinb(sysCounter);

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {

  uint8_t keyboardBit = KEYBOARD_IRQ;
  uint8_t timerBit = TIMER0_IRQ;
  int ipc_status;
  int r;
  message msg;
  int idle = n * 60;
    

  if (timer_subscribe_int(&timerBit) || kbd_subscribe_int(&keyboardBit))
    return 1;

  while(keyScanned != ESC  && counter < idle) { 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) 
    { 
      switch (_ENDPOINT_P(msg.m_source)) 
      {
        case HARDWARE: 
        if (msg.m_notify.interrupts & timerBit) 
            timer_int_handler();
          
        if (msg.m_notify.interrupts & keyboardBit) 
        {
          kbc_ih();
          counter = 0;
          kbd_scancode();
          }
          break;

        default:
          break;
      }
    } 
    else {}
  }
  
  
  if (timer_unsubscribe_int() || kbd_unsubscribe_int())
    return 1;

  kbd_print_no_sysinb(sysCounter);
  return 0;
}
