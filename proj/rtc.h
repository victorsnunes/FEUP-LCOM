#ifndef _RTC_H_
#define _RTC_H_

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "utils.h"


/** @defgroup rtc rtc
 * @file rtc.h
 * @brief This file contains the definition of implementation of the rtc, used to get the day and 
 * time the game was played, along with some macros.
 * 
 */

#define RTC_IRQ             8  /** <@brief RTC IRQ line */

#define RTC_ADDR_REG        0x70 /** <@brief RTC Address Port **/
#define RTC_DATA_REG        0x71 /** <@brief RTC Data Port **/

#define RTC_REG_A           10
#define RTC_REG_B           11 

#define HOURS               0x04 
#define MINUTES             0x02
#define SECONDS             0x00
#define DAY                 0x07
#define MONTH               0x08
#define YEAR                0x09

#define RTC_BIT_DM          BIT(2)   
#define RTC_UIP             BIT(7)

/**
 * @brief This functions reads a register from the RTC
 * @return int 0 in case of success, 1 otherwise
 */
int read_register();


/**
 * @brief This function checks if the RTC is in the BCD format
 * @return int true in case of success, false otherwise
 */
bool isBCD();

/**
 * @brief if the RTC is in BCD format,the function convert it to decimal
 * @param bcd Number in BCD format to be converted
 */
void bcd_to_dec(uint8_t *bcd);

/**
 * @brief  gets the current date from the RTC in binary.
 */
void getDate();

/**
 * @brief  gets the current time from the RTC in binary.
 */
void getTime();


#endif
