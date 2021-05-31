#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

double exp(double x){
	
}

double pow(double x, uint16_t y){
	double s = x;
	while(y-->0){
		x *= s;
	}
	return s;
}

unsigned long long fac(uint8_t x){
	unsigned long long y = 1;
	while(x-->0){
		y *= x;
	}
	return y;
}
