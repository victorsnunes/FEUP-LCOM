int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();
int kbc_read();
void kbd_scancode();
int cnt_sys_inb(uint8_t adress, uint8_t *stat);
int kbc_enable_interrupt();

