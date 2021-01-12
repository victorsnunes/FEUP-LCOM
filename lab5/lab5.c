// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "graphic.h"
#include "keyboard.h"

// Any header files included below this line should have been created by you
extern uint8_t keyScanned; 
extern int contador;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  
  if (init_mode(mode) != OK) return 1;

  tickdelay(micros_to_ticks(delay * 1000000));

  if (vg_exit() != OK) return 2;

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  

  if (vg_init(mode) == NULL) return 1; 

  vbe_mode_info_t mode_info;
  vbe_get_mode_info(mode,&mode_info);
  vg_draw_rectangle(x, y, width, height, color);
  
  
  message msg; 
  int r; 
  int ipc_status; 
  uint8_t irq_set = 0; 
  

  if(kbd_subscribe_int(&irq_set) != 0) return 1;                 //interrupt upon keyboard use

  while(keyScanned != ESC) { 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:        
          if (msg.m_notify.interrupts & irq_set) { 
            kbc_ih();
          }
        break;
        default:
          break;  
      }
    } else{ 
      continue;
    }
  }
  
  if(kbd_unsubscribe_int()) return 1;    
  if(vg_exit()) return 1; 
  return 0;

}
/*
int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  
  message msg; 
  int r; 
  int ipc_status; 
  uint8_t irq_set; 
  if (vg_init(mode) == NULL) return 1;
  vbe_mode_info_t mode_info;
  vbeModeInfo(mode,&mode_info);
  
  if(drawPattern(mode,no_rectangles,first,step,&mode_info)) return 1;
   
  if(kbd_subscribe_int(&irq_set) != 0) return 1;                 //interrupt upon keyboard use

  while(keyScanned != ESC) { 
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      continue;
    }
    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:        
          if (msg.m_notify.interrupts & irq_set) { 
            kbc_ih();
          }
        break;
        default:
          break;  
      }
    } else{ 
      continue;
    }
  }
  
  if(kbd_unsubscribe_int()) return 1;    
  if(vg_exit()) return 1; 
  return 0;

}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  
  printf("%s(): under construction\n", __func__);

  return 1;
}
*/