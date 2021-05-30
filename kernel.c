#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
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

char* intToStr(uint8_t n){
	char* out = (char*) 0x00;
	uint8_t i = 0;
	while(n > 0)
	{
		uint8_t curr_c;
		uint16_t curr = n % 10;
		n /= 10;
		
		if(curr == 0)
			out[i] = '0';
		else if(curr == 1)
			out[i] = '1';
		else if(curr == 2)
			out[i] = '2';
		else if(curr == 3)
			out[i] = '3';
		else if(curr == 4)
			out[i] = '4';
		else if(curr == 5)
			out[i] = '5';
		else if(curr == 5)
			out[i] = '6';
		else if(curr == 7)
			out[i] = '7';
		else if(curr == 8)
			out[i] = '8';
		else if(curr == 9)
			out[i] = '9';
		
		i++;
	}
	
	return out;
}
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

#define min(a,b) __extension__\
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
       _a < _b ? _a : _b; })

enum flag_itoa {
    FILL_ZERO = 1,
    PUT_PLUS = 2,
    PUT_MINUS = 4,
    BASE_2 = 8,
    BASE_10 = 16,
};

static char * sitoa(char * buf, unsigned int num, int width, enum flag_itoa flags)
{
    unsigned int base;
    if (flags & BASE_2)
        base = 2;
    else if (flags & BASE_10)
        base = 10;
    else
        base = 16;

    char tmp[32];
    char *p = tmp;
    do {
        int rem = num % base;
        *p++ = (rem <= 9) ? (rem + '0') : (rem + 'a' - 0xA);
    } while ((num /= base));
    width -= p - tmp;
    char fill = (flags & FILL_ZERO)? '0' : ' ';
    while (0 <= --width) {
        *(buf++) = fill;
    }
    if (flags & PUT_MINUS)
        *(buf++) = '-';
    else if (flags & PUT_PLUS)
        *(buf++) = '+';
    do
        *(buf++) = *(--p);
    while (tmp < p);
    return buf;
}

int my_vsprintf(char * buf, const char * fmt, va_list va)
{
    char c;
    const char *save = buf;

    while ((c  = *fmt++)) {
        int width = 0;
        enum flag_itoa flags = 0;
        if (c != '%') {
            *(buf++) = c;
            continue;
        }
    redo_spec:
        c  = *fmt++;
        switch (c) {
        case '%':
            *(buf++) = c;
            break;
        case 'c':;
            *(buf++) = va_arg(va, int);
            break;
        case 'd':;
            int num = va_arg(va, int);
            if (num < 0) {
                num = -num;
                flags |= PUT_MINUS;
            }
            buf = sitoa(buf, num, width, flags | BASE_10);
            break;
        case 'u':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_10);
            break;
        case 'x':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags);
            break;
        case 'b':
            buf = sitoa(buf, va_arg(va, unsigned int), width, flags | BASE_2);
            break;
        case 's':;
            const char *p  = va_arg(va, const char *);
            if (p) {
                while (*p)
                    *(buf++) = *(p++);
            }
            break;
        case 'm':;
            const uint8_t *m  = va_arg(va, const uint8_t *);
            width = min(width, 64); // buffer limited to 256!
            if (m)
                for (;;) {
                    buf = sitoa(buf, *(m++), 2, FILL_ZERO);
                    if (--width <= 0)
                        break;
                    *(buf++) = ':';
                }
            break;
        case '0':
            if (!width)
                flags |= FILL_ZERO;
            // fall through
        case '1'...'9':
            width = width * 10 + c - '0';
            goto redo_spec;
        case '*':
            width = va_arg(va, unsigned int);
            goto redo_spec;
        case '+':
            flags |= PUT_PLUS;
            goto redo_spec;
        case '\0':
        default:
            *(buf++) = '?';
        }
        width = 0;
    }
    *buf = '\0';
    return buf - save;
}

int sprintf(char * buf, const char * fmt, ...)
{
    va_list va;
    va_start(va,fmt);
    int ret = my_vsprintf(buf, fmt, va);
    va_end(va);
    return ret;
}
 
size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	if(c == '\n')
	{
		++terminal_row;
		terminal_column = 0;
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT){
// 			for(uint8_t y = 1; y < 25; y++){
// 				for(uint8_t x = 0; x < 80; x++){
// 					const size_t index = y * VGA_WIDTH + x;
// 					const size_t index1 = (y + 1) * VGA_WIDTH + x;
// 					terminal_buffer[index] = terminal_buffer[index1];
// 				}
// 			}
// 			for(uint8_t x = 0; x < 80; x++){
// 				const size_t index = 24 * VGA_WIDTH + x;
// 				terminal_buffer[index] = vga_entry(' ', terminal_color);
// 			}
		}
	}
}
 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 	for(uint8_t i = 0; i < 64; i++){
		char b[256];
		terminal_writestring(sprintf(b, "%d) Hello, kernel World!\n", i+1));
	}
}
