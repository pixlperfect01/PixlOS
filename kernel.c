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
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
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
			for(uint8_t y = 1; y < 25; y++){
				for(uint8_t x = 0; x < 80; x++){
					const size_t index = y * VGA_WIDTH + x;
					const size_t index1 = (y + 1) * VGA_WIDTH + x;
					terminal_buffer[index] = terminal_buffer[index1];
				}
			}
			for(uint8_t x = 0; x < 80; x++){
				const size_t index = 24 * VGA_WIDTH + x;
				terminal_buffer[index] = vga_entry(' ', terminal_color);
			}
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
 
	/* I cant cast for some rsn */
	terminal_writestring("1) Hello, kernel World!\n");
	terminal_writestring("2) Hello, kernel World!\n");
	terminal_writestring("3) Hello, kernel World!\n");
	terminal_writestring("4) Hello, kernel World!\n");
	terminal_writestring("5) Hello, kernel World!\n");
	terminal_writestring("6) Hello, kernel World!\n");
	terminal_writestring("7) Hello, kernel World!\n");
	terminal_writestring("8) Hello, kernel World!\n");
	terminal_writestring("9) Hello, kernel World!\n");
	terminal_writestring("10) Hello, kernel World!\n");
	terminal_writestring("11) Hello, kernel World!\n");
	terminal_writestring("12) Hello, kernel World!\n");
	terminal_writestring("13) Hello, kernel World!\n");
	terminal_writestring("14) Hello, kernel World!\n");
	terminal_writestring("15) Hello, kernel World!\n");
	terminal_writestring("16) Hello, kernel World!\n");
	terminal_writestring("17) Hello, kernel World!\n");
	terminal_writestring("18) Hello, kernel World!\n");
	terminal_writestring("19) Hello, kernel World!\n");
	terminal_writestring("20) Hello, kernel World!\n");
	terminal_writestring("21) Hello, kernel World!\n");
	terminal_writestring("22) Hello, kernel World!\n");
	terminal_writestring("23) Hello, kernel World!\n");
	terminal_writestring("24) Hello, kernel World!\n");
	terminal_writestring("25) Hello, kernel World!\n");
	terminal_writestring("26) Hello, kernel World!\n");
	terminal_writestring("27) Hello, kernel World!\n");
	terminal_writestring("28) Hello, kernel World!\n");
	terminal_writestring("29) Hello, kernel World!\n");
	terminal_writestring("30) Hello, kernel World!\n");
	terminal_writestring("31) Hello, kernel World!\n");
	terminal_writestring("32) Hello, kernel World!\n");
	terminal_writestring("33) Hello, kernel World!\n");
	terminal_writestring("34) Hello, kernel World!\n");
	terminal_writestring("35) Hello, kernel World!\n");
	terminal_writestring("36) Hello, kernel World!\n");
	terminal_writestring("37) Hello, kernel World!\n");
	terminal_writestring("38) Hello, kernel World!\n");
	terminal_writestring("39) Hello, kernel World!\n");
	terminal_writestring("40) Hello, kernel World!\n");
	terminal_writestring("41) Hello, kernel World!\n");
	terminal_writestring("42) Hello, kernel World!\n");
	terminal_writestring("43) Hello, kernel World!\n");
	terminal_writestring("44) Hello, kernel World!\n");
	terminal_writestring("45) Hello, kernel World!\n");
	terminal_writestring("46) Hello, kernel World!\n");
	terminal_writestring("47) Hello, kernel World!\n");
	terminal_writestring("48) Hello, kernel World!\n");
	terminal_writestring("49) Hello, kernel World!\n");
	terminal_writestring("50) Hello, kernel World!\n");
	terminal_writestring("51) Hello, kernel World!\n");
	terminal_writestring("52) Hello, kernel World!\n");
	terminal_writestring("53) Hello, kernel World!\n");
	terminal_writestring("54) Hello, kernel World!\n");
	terminal_writestring("55) Hello, kernel World!\n");
	terminal_writestring("56) Hello, kernel World!\n");
	terminal_writestring("57) Hello, kernel World!\n");
	terminal_writestring("58) Hello, kernel World!\n");
	terminal_writestring("59) Hello, kernel World!\n");
	terminal_writestring("60) Hello, kernel World!\n");
	terminal_writestring("61) Hello, kernel World!\n");
	terminal_writestring("62) Hello, kernel World!\n");
	terminal_writestring("63) Hello, kernel World!\n");
	terminal_writestring("64) Hello, kernel World!");
}
