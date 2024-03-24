#include <stdint.h> 
#include <string.h>
#include <console.h>
/*
* Add description later
*/


//#define __DEBUG


#define VGA_CONTROL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e


#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25 
#define MAX_COLS 80

#define MIN(x,y) ((x)<(y)?(x):(y))



/*
 * If we just create the function __GetCursor like this :
 [[maybe_unused]] static  uint16_t __GetCursor(){
    int offset = 0 ;
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_LOW);
    offset  +=inb(VGA_DATA_REGISTER);
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_HIGH);
    offset +=inb(VGA_DATA_REGISTER) << 8;
    return offset;}
 *  The result we will get will be wrong , because the compiler make the assumption that the first and second call to inb will give the same result
 *  since we called the same routine with the same arguments , but this is wrong because we modify the VGA_CONTROL_REGISTER , and thus we need to make it 
 *  volatile , thus creating a function pointer to it marked as volatile  .
 */


static uint8_t inb(uint16_t);
typedef uint8_t(*pFunc1)(uint16_t); 
volatile pFunc1 __pinb = inb;

#ifdef __DEBUG
static uint16_t __GetCursor(void) ;

typedef uint16_t (*pFunc2)(void);
volatile pFunc2 __pGetCursor = __GetCursor;
#endif

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};



static uint8_t inb(uint16_t port){
    uint8_t result ;
    __asm__("in %%dx , %%al" : "=a" (result) : "d" (port));
    return result ;
}


static void outb(uint16_t port , uint8_t data){
    __asm__("out %%al , %%dx" : : "a" (data) , "d" (port));
}



[[maybe_unused]] static  uint16_t __GetCursor(){
    int offset = 0 ;
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_LOW);
    offset  +=__pinb(VGA_DATA_REGISTER);
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_HIGH);
    offset +=__pinb(VGA_DATA_REGISTER) << 8;
    return offset;
}

static void __CursorSet(uint16_t offset){
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_LOW) ;
    outb(VGA_DATA_REGISTER , (uint8_t)(offset & 0xff)) ;
    outb(VGA_CONTROL_REGISTER , VGA_OFFSET_HIGH);
    outb(VGA_DATA_REGISTER , (uint8_t)(offset >> 8));
}

static  inline uint8_t vga_entry_color(enum vga_color fg , enum vga_color bg){
    return fg | bg<<4;
}

static inline uint16_t vga_entry(unsigned char c , uint8_t color ){
    return (uint16_t) c | (uint16_t) color <<8;
}


static uint8_t terminal_row;
static uint8_t terminal_column;
static uint8_t terminal_color ;
static uint16_t *videomem;
static uint8_t terminal_buffer[MAX_COLS *MAX_ROWS];
static struct vga_terminal terminal;

void __InitializeTerminal(void){

    __CursorSet(0);
    terminal.buffer = terminal_buffer;
    terminal.start = 0;
    terminal.virtual_cursor_position = 0;
    terminal.new_line = 0;  
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    videomem = (uint16_t *)VIDEO_ADDRESS;
    for (size_t y = 0; y < MAX_ROWS; ++y){
        for(size_t x=0 ; x < MAX_COLS ; ++x){
            const size_t index  = y * MAX_COLS + x;
            videomem[index] = vga_entry(' ',terminal_color);
        }
    }


}

void __TerminalClear(void){
    __InitializeTerminal();
}



/*
*Support only new line for now
*/

static void handle_max_rows(){
    size_t j ;
    for (size_t i =0 ; i < MAX_ROWS -1 ; i++){
        for (j = 0 ; j < MAX_COLS ; j++){            
            terminal.buffer[i*MAX_COLS + j] =  terminal.buffer[(i+1)*MAX_COLS + j];
        }
    }
    for (j  = 0 ; j < (MAX_ROWS-1)*(MAX_COLS) ; j++){
        videomem[j] = vga_entry(terminal.buffer[j] , terminal_color);
    } 

    for (j = 0 ;j < MAX_COLS ; j++){
        terminal.buffer[(MAX_ROWS -1)*(MAX_COLS) + j] = ' ';
    }


    for (j = 0 ;j < MAX_COLS ; j++){
        videomem[(MAX_ROWS -1)*(MAX_COLS) +j] = vga_entry(terminal.buffer[(MAX_ROWS -1)*(MAX_COLS) + j] , terminal_color);
    }
    
    terminal_row--;
}

static int check_special_char(char c){
    switch (c){
        case 0xa:
            while (terminal.start < terminal.virtual_cursor_position){
                videomem[terminal.start] = vga_entry(terminal.buffer[terminal.start], terminal_color);
                terminal.start++;
            }

            terminal_column = 0 ;
            if (++terminal_row == MAX_ROWS) handle_max_rows();
            terminal.virtual_cursor_position = MIN(terminal_row*(MAX_COLS) , (MAX_ROWS -1)*(MAX_COLS));
            terminal.start = terminal.virtual_cursor_position;

            return 1; 
        default:
            break;
    }
    return 0 ;
}

static  void terminal_putentryat(uint8_t c, uint8_t x, uint8_t y){
    if (check_special_char(c)){
        return ;
    }
    size_t index = y*MAX_COLS +x ;
    terminal.buffer[index] = c ;
    terminal.virtual_cursor_position++;
    if (++terminal_column == MAX_COLS){
        terminal_column = 0 ;
        if (++terminal_row == MAX_ROWS) handle_max_rows();
    }
}

void terminal_putchar(char c){
    terminal_putentryat(c ,  terminal_column , terminal_row);
}

static void terminal_write(const char *data , size_t size){
    for(size_t i = 0 ; i < size ; i++){
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char *data){
    terminal_write(data , strlen(data));
    __CursorSet(terminal_row*MAX_COLS + terminal_column);
    terminal.new_line = 0 ;
}


