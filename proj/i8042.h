#ifndef __I8042_H_
#define __I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @file i8042.h
 * @brief Code with macros to use the keyboard and the mouse 
 * Constants for programming the i8254 Timer. 
 */


#define KEYBOARD_IRQ 1
#define TWO_BYTES_SCANCODE 0xE0

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
#define CHECK_KBC 0xAA
#define CHECK_KBD_INTERFACE 0xAB
#define DIS_KBD_INTERFACE 0XAD
#define EN_KBD_INTERFACE 0xAE

#define BREAK_CODE BIT(7)

#define DIS_MOUSE_INTER BIT(5)
#define DIS_KBD_INTER BIT(4)
#define EN_MOUSE BIT(1)
#define EN_KBD BIT(0)

//Keys Scancode
#define ESC 0x81
#define ENTER 0x1c
#define SPACEBAR 0x39
#define BACKSPACE 0x0e
#define UP_ARROW 0x48
#define DOWN_ARROW 0x50

#define A 0x1e
#define B 0x30
#define C 0x2e
#define D 0x20
#define E 0x12
#define F 0x21
#define G 0x22
#define H 0x23
#define I 0x17
#define J 0x24
#define K 0x25
#define L 0x26
#define M 0x32
#define N 0x31
#define O 0x18
#define P 0x19
#define Q 0x10
#define R 0x13
#define S 0x1f
#define T 0x14
#define U 0x16
#define V 0x2f
#define W 0x11
#define X 0x2d
#define Y 0x15
#define Z 0x2c

#define ZERO1 0x0b
#define ONE1 0x02
#define TWO1 0x03
#define THREE1 0x04
#define FOUR1 0x05
#define FIVE1 0x06
#define SIX1 0x07
#define SEVEN1 0x08
#define EIGHT1 0x09
#define NINE1 0x0a

#define ZERO2 0x52
#define ONE2 0x4f
#define TWO2 0x50
#define THREE2 0x51
#define FOUR2 0x4b
#define FIVE2 0x4c
#define SIX2 0x4d
#define SEVEN2 0x47
#define EIGHT2 0x48
#define NINE2 0x49


//MOUSE

#define MOUSE_IRQ 12
#define MOUSE_IRQ_PIC2 4

//Packets
#define LB BIT(0)     
#define RB BIT(1)     
#define MB BIT(2)     
#define X_MSB BIT(4) 
#define Y_MSB BIT(5)
#define X_OV BIT(6)  
#define Y_OV BIT(7)  

#define READ_DATA 0xEB          
#define STREAM_MODE 0xEA         
#define ENABLE_DATA_REPORT 0xF4  
#define DISABLE_DATA_REPORT 0xF5 
#define REMOTE_MODE 0xF0

#define ACK 0xFA
#define NACK 0xFE
#define ERROR 0xFC  

#define WRITE_BYTE_TO_MOUSE 0xD4

#define ATTEMPTS 10

/**@}*/

#endif
