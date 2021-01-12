#include "rtc.h"


/**
 * @file rtc.c
 * @brief This file contains the implementation of the rtc, used to get the day and time the game 
 * was played.
 */


uint8_t player_day = 99; /**<@brief represents the day, given by the rtc*/
uint8_t player_month = 99; /**<@brief represents the month, given by the rtc*/
uint8_t player_year = 99; /**<@brief represents the year, given by the rtc*/
uint8_t player_hour = 99; /**<@brief represents the hour, given by the rtc*/
uint8_t player_minute = 99; /**<@brief represents the minute, given by the rtc*/


int read_register() 
{
    uint8_t register_A = 0;

      sys_outb(RTC_ADDR_REG, RTC_REG_A);
      util_sys_inb(RTC_DATA_REG, &register_A);

  	if ((register_A & RTC_UIP) != 0)
	  	return 1;
	  else return 0;
}

bool isBCD() {

	uint8_t register_B = 0;

	sys_outb(RTC_ADDR_REG, RTC_REG_B);
	util_sys_inb(RTC_DATA_REG, &register_B);

	if (!(register_B & RTC_BIT_DM))
		return true;
	else
		return false;

}

void bcd_to_dec (uint8_t* bcd) {

	*bcd = (((*bcd) & 0xF0) >> 4) * 10 + ((*bcd) & 0x0F);

}

void getDate() {
  
  sys_outb(RTC_ADDR_REG, DAY);
  util_sys_inb(RTC_DATA_REG, &player_day);
  
  sys_outb(RTC_ADDR_REG, MONTH);
  util_sys_inb(RTC_DATA_REG, &player_month);

  sys_outb(RTC_ADDR_REG, YEAR);
  util_sys_inb(RTC_DATA_REG, &player_year);

  if(isBCD())
  {
    bcd_to_dec(&player_day);
    bcd_to_dec(&player_month);
    bcd_to_dec(&player_year);
  }
}

void getTime() {
  
  sys_outb(RTC_ADDR_REG, HOURS);
  util_sys_inb(RTC_DATA_REG, &player_hour);

  sys_outb(RTC_ADDR_REG, MINUTES);
  util_sys_inb(RTC_DATA_REG, &player_minute);

  
  if(isBCD())
  {
    bcd_to_dec(&player_hour);
    bcd_to_dec(&player_minute);
  }
  
}
