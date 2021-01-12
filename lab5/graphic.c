#include "graphic.h"
#include "lcom/vbe.h"
#include "vbe_macros.h"

static uint8_t *video_mem;

static uint16_t hres;        
static uint16_t vres;
static uint8_t bits_per_pixel; 
static uint8_t GreenMaskSize;     
static uint8_t BlueMaskSize;
static uint8_t RedMaskSize; 
static uint8_t bytes;
//uint8_t bytes = ceil(bits_per_pixel/ 8); 


void getPermission() {

    int r;
    struct minix_mem_range mr; 
    mr.mr_base = (phys_bytes) 0x0;         //getting the base address
    mr.mr_limit = mr.mr_base + 0xFFFFF;    //getting the 1MB (1024*1024)

    //getting permission
    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    return;
}

int init_mode(uint16_t mode){   
    
    reg86_t reg; 
    memset(&reg, 0, sizeof(reg));               // clear unused register to avoid errors 
    reg.ax = VBE_FUNCTION | VBE_SET_MODE;       // VBE call, function 02 -- set VBE mode
    reg.bx = BIT(14) | mode;                    // set bit 14: linear framebuffer
    reg.intno = INT;                   
    
    //sending info to the bios
    if(sys_int86(&reg) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return 1;
    }
    return 0; 
}

void *(vg_init)(uint16_t mode){

    getPermission();

    vbe_mode_info_t mode_info;
    if(vbe_get_mode_info(mode, &mode_info)) return NULL;                  //getting mode

    hres = mode_info.XResolution;                                   //setting static variables
    vres = mode_info.YResolution; 
    bits_per_pixel = mode_info.BitsPerPixel; 
    GreenMaskSize = mode_info.GreenMaskSize;                      //get mask size 
    BlueMaskSize = mode_info.BlueMaskSize; 
    RedMaskSize = mode_info.RedMaskSize; 
    bytes = ceil(bits_per_pixel/8); 

    int r = 0;
    struct minix_mem_range mr;
    unsigned int vram_size = hres*vres* ceil(bits_per_pixel/8.0);   //size of the ram
    mr.mr_base = (phys_bytes)  mode_info.PhysBasePtr;               //getting the base address
    mr.mr_limit = mr.mr_base + vram_size;                           //getting the limit
    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))       //getting permission
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);  //mapping memory to get the first MB
    if(video_mem == MAP_FAILED) panic("couldn't map video memory"); //case of error

    if(init_mode(mode))
        return NULL;

    return video_mem; 
}


int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {

    while(height > 0){
        vg_draw_hline(x, y, width, color); 
        height--; 
        y++; 
    }
    return 0; 
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len ,uint32_t color ){
    while(len>0){
        drawPixel(x, y, color); 
        len--;
        x++; 
    }
    return 0; 
} 
int drawPixel(uint16_t x, uint16_t y, uint32_t color){
    if(x >= hres || y >= vres) return 0;    
    memcpy(&video_mem[((y*hres)+x)*bytes], &color, bytes); 
    return 0; 
}