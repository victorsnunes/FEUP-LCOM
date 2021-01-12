#include <lcom/lcf.h>

#include "mouse.h"
#include "i8042.h"

#include <stdint.h>
#include <stdio.h>

static int mouseHookID;
uint8_t bytes[3];
int b = 0;

int mouse_subscribe_int(uint8_t *bit_no) {
    mouseHookID = (int)*bit_no;
    if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouseHookID) != 0)
        return 1;

    *bit_no = (uint8_t)BIT(*bit_no);
    return 0;
}

int mouse_unsubscribe_int()
{
    if (sys_irqrmpolicy(&mouseHookID) != 0)  
        return 1;
  
    return 0;
}

void(mouse_ih)()
{
    uint8_t mouseData;
    uint8_t kbc_status;
    util_sys_inb(STAT_REG, &kbc_status);
    if ((kbc_status & (PARITY| TIME_OUT)) == 0) {

        if((kbc_status & OBF) && (kbc_status & AUX)) {

            util_sys_inb(OUT_BUF, &mouseData);
            if ( (b == 0 && (mouseData & BIT(3))) || b != 0 ){
                bytes[b] = mouseData;
                b = (b +1) % 3;
            }  

        }
             
        
    }
    else {
        //Reads the invalid data but doesn't do nothing with it, just to clear up the output buffer
        util_sys_inb(OUT_BUF, &mouseData);
    }
    
}

int set_mouse_to_minix_default() {

    uint8_t kbc_status;
    if (util_sys_inb(STAT_REG, &kbc_status) != 0)
        return 1;

    if ((kbc_status & IBF) != 0)
        return 2;

    if(sys_outb(IN_BUF, DISABLE_DATA_REPORT) != 0)
        return 3;

    if (sys_outb(CMD_REG, WRITE_BYTE_TO_MOUSE) != 0)
        return 4;

    uint8_t mouse_answer;
    if (util_sys_inb(OUT_BUF, &mouse_answer) != 0)
        return 5;

    if (mouse_answer != ACK)
        return 6;

    return 0;
}

void create_packet(struct packet *pckt, uint8_t packetBytes[]){
    for(unsigned i = 0; i < 3; ++i){
        pckt->bytes[i] = packetBytes[i];
    }
    pckt->rb = (packetBytes[0] & RB);
    pckt->mb = (packetBytes[0] & MB);
    pckt->lb = (packetBytes[0] & LB);

    pckt->delta_x = pckt->bytes[1];
    if(pckt->bytes[0] & X_MSB)
        pckt->delta_x |= 0xFF00;   //complement
    
    pckt->delta_y = pckt->bytes[2];
    if(pckt->bytes[0] & Y_MSB)
        pckt->delta_y |= 0xFF00; //complement
    
    pckt->x_ov = pckt->bytes[0] & X_OV;
    pckt->y_ov = pckt->bytes[0] & Y_OV;
}




