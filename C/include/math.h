#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

double exp(double x){
	// e^0 = 1 (duh)
	// e^0.5 = 1.6487212707
	// e^1 = 2.718281828459 (also duh)
	// lin interp:  y = y1 + ((x – x1) / (x2 – x1)) * (y2 – y1)
	uint8_t ipart = floor(x + 0.5);
	double fpart = x - ipart;
	double oupt = pow(2.718281828459, ipart);
	if(fpart > 0.5)
	{
		oupt *= 1.6487212707 + ((fpart - 0.5) / ( 0.5)) * (1.06956056);
	} else if(fpart < 0.5)
	{
		oupt *= 1 + (fpart / 0.5 * 0.6487212707);
	} else {
		oupt *= 1.6487212707;
	}
	return oupt;
}

double pow(double x, uint16_t y){
	double s = x;
	while(y-->0){
		x *= s;
	}
	return x;
}

double powf(double x, double y){
	
}

unsigned long long fac(uint8_t x){
	unsigned long long y = 1;
	while(x-->0){
		y *= x;
	}
	return y;
}

double ln(double x){
	
}
