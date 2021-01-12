#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>


#define KEYBOARD_IRQ 1
#define ESC 0x81
#define FIRST_BYTE 0xE0

#define MOUSE_IRQ 12
#define MOUSE_IRQ_PIC2 4


#define DELAY 20000

#define STAT_REG 0x64
#define CMD_REG 0x64
#define OUT_BUF 0x60
#define IN_BUF 0x60

#define PARITY BIT(7)
#define TIME_OUT BIT(6)
#define AUX BIT(5)
#define IBF BIT(1)
#define OBF BIT(0)


#define READ_CMD 0x20
#define WRITE_CMD 0x60
#define WRITE_BYTE_TO_MOUSE 0xD4
#define CHECK_KBC 0xAA
#define CHECK_KBD_INTERFACE 0xAB
#define DIS_KBD_INTERFACE 0XAD
#define EN_KBD_INTERFACE 0xAE

#define BREAK_CODE BIT(7)

#define DIS_MOUSE_INTER BIT(5)
#define DIS_KBD_INTER BIT(4)
#define EN_MOUSE BIT(1)
#define EN_KBD BIT(0)

#define READ_DATA 0xEB          
#define STREAM_MODE 0xEA         
#define ENABLE_DATA_REPORT 0xF4  
#define DISABLE_DATA_REPORT 0xF5 
#define REMOTE_MODE 0xF0 

#define LB BIT(0)     
#define RB BIT(1)     
#define MB BIT(2)     
#define X_MSB BIT(4) 
#define Y_MSB BIT(5)
#define X_OV BIT(6)  
#define Y_OV BIT(7)  

#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC  

#define DISABLE_IRQ_LINE 0
#define ENABLE_IRQ_LINE 1

#endif /* _LCOM_I8042_H */
