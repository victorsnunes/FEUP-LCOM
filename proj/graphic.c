#include "graphic.h"
#include "lcom/vbe.h"


/**
 * @file graphic.c
 * @brief Code used to interact with the video card 
 */


#define VBE_FUNCTION   0x4F00
#define VBE_MODE_INFO  0x01
#define VBE_SET_MODE   0x02
#define INT            0x10


uint16_t hres; 
uint16_t vres; 
uint8_t bytes_per_pixel;

static uint8_t *video_mem; 
static uint8_t *double_buffer;  //Second buffer, for doing double_buffering
unsigned int vram_size;

int init_mode(uint16_t mode){   
    
    reg86_t reg; 
    memset(&reg, 0, sizeof(reg));            // clearing unused register
    reg.ax = VBE_FUNCTION | VBE_SET_MODE;   // VBE call and set VBE mode
    reg.bx = BIT(14) | mode;               // linear framebuffer
    reg.intno = INT;                   
    
    //send to bios
    if( sys_int86(&reg) != OK) {
        printf("set_vbe_mode: sys_int86() failed \n");
        return 1;
    }
    return 0; 
}

void *(vg_init)(uint16_t mode){

    vbe_mode_info_t mode_info;
    if(my_get_mode_info(mode, &mode_info)) return NULL;

    //Global static variables
    hres = mode_info.XResolution;
    vres = mode_info.YResolution;
    bytes_per_pixel = mode_info.BitsPerPixel/8; 

    int r = 0;
    struct minix_mem_range mr;
    vram_size = hres*vres* bytes_per_pixel;

    mr.mr_base = (phys_bytes) mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;

    if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

    double_buffer = (uint8_t*) malloc (vram_size);

    if(video_mem == MAP_FAILED)
        panic("couldn't map video memory");


    if(init_mode(mode))
        return NULL;

    return video_mem; 
}

//Stores informations about the mode
int my_get_mode_info(uint16_t mode, vbe_mode_info_t *mode_info){
  
    reg86_t reg;
    mmap_t map;
    

    if(lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL ) return 1; 

    phys_bytes buff;
    buff = map.phys;

    memset(&reg, 0, sizeof(reg));
    reg.ax = VBE_FUNCTION | VBE_MODE_INFO;   
    reg.cx = mode;
    reg.es =  PB2BASE(buff);
    reg.di = PB2OFF(buff);
    reg.intno = INT;

    if( sys_int86(&reg) != OK ) {
        lm_free(&map);
        return 2;
    }
    
    *mode_info = *((vbe_mode_info_t *)(map.virt)); 

    if (reg.ah != 0x00) {
        lm_free(&map);
        return 3;
    }

    if (!lm_free(&map)) return 4;

    return 0; 
}

int drawPixel(uint16_t x, uint16_t y, uint32_t color){

    if (color == CHROMA_KEY_GREEN_888) return 0;

    if(x >= hres) x -= hres;
    if(y >= vres) y -= vres;

    memcpy(&double_buffer[((y*hres)+x)*bytes_per_pixel], &color, bytes_per_pixel);
    return 0; 

}

void write_buffer_to_videomem() {
  memcpy(video_mem, double_buffer, vram_size);
}
