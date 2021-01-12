#include <lcom/lcf.h>
#include <lcom/lab3.h>
#include <stdint.h>

#include "keyboard.h"

/**
 * @file keyboard.c
 * @brief Code used to interact with the Keyboard
 */


static int kbc_hook_id = KEYBOARD_IRQ;
uint8_t keyScanned = 0x00;


int keyboard_subscribe_int(uint8_t *bit_no)
{
  kbc_hook_id = (int)*bit_no;

  if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbc_hook_id) != OK)
    return 1;
  
  *bit_no = (uint8_t) BIT(*bit_no);
  return 0;
}

int keyboard_unsubscribe_int()
{
  if (sys_irqrmpolicy(&kbc_hook_id) != OK)
    return 1;
  
  return 0;
}

void keyboard_ih() //Handles keyboard interrupts 
{
  uint8_t status, key;
  util_sys_inb(STAT_REG, &status);
  if(!(status & AUX))
  {
    util_sys_inb(OUT_BUF, &key);
    if (!(status & (PARITY | TIME_OUT)))
      keyScanned = key;
  }

}

int set_keyboard_default() // KBC commands
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

