#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>


#define KEYBOARD_IRQ 1
#define ESC 0x81
#define FIRST_BYTE 0xE0

#define DELAY 20000

#define STAT_REG 0x64
#define CMD_REG 0x64
#define OUT_BUF 0x60
#define IN_BUF 0x60

#define PARITY BIT(7)
#define TIME_OUT BIT(6)
#define IBF BIT(1)
#define OBF BIT(0)

#define READ_CMD 0x20
#define WRITE_CMD 0x60
#define CHECK_KBC 0xAA
#define CHECK_KBD_INTERFACE 0xAB
#define DIS_KBD_INTERFACE 0XAD
#define EN_KBD_INTERFACE 0xAE

#define BREAK_CODE BIT(7)

#define DIS_MOUSE_INTER BIT(5)
#define DIS_KBD_INTER BIT(4)
#define EN_MOUSE BIT(1)
#define EN_KBD BIT(0)

#endif /* _LCOM_I8042_H */
