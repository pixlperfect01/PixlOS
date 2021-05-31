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
		oupt *= 1.6487212707 + ((fpart - 0.5) / (0.5)) * (1.06956056);
	} else if(fpart < 0.5)
	{
		oupt *= 1 + (fpart / 0.5 * 0.6487212707);
	} else {
		oupt *= 1.6487212707;
	}
	return oupt;
}

double pow(double x, double y){
	// exp(y*ln(x))
	return exp(y*ln(x));
}

unsigned long long fac(uint8_t x){
	unsigned long long y = 1;
	while(x-->0){
		y *= x;
	}
	return y;
}

double log(double x){
	double yn = x - 1;
	double yn1 = yn;
	double eps = 0.000001;
	do {
		yn = yn1;
		yn1 = yn + 2 * (x - exp(yn)) / (x + exp(yn));
	} while ((yn - yn1) > 0 ? (yn - yn1) : -(yn - yn1) > eps);
	
	return yn1;
}

double log10(double x){
	return log(x) / log(n);
}

double fmod(double x, double y){
	return x - ((x / y) | 0) * y;
}

uint16_t trunc(double x){
	return x < 0 ? -floor(-x) : floor(x);
}

double sin(double x){
	x = fmod(x + 3.141592653, 3.141592653*2) - 3.141592653;
	double c = x*x*x;
	double out = x - c / 6;
	c *= x*x;
	out += c / 120;
	c *= x*x;
	out -= c / 5040;
	c *= x*x;
	out += c / 362880;
	return out;
}

double cos(double x){
	return sin(x + 3.141592653/2);
}

double atan(double x){
	x = ((x + 1) % 2) - 1;
	double out = 0;
	for(uint8_t i = 0; i < 16; i++){
		double a = pow(2, 2*i) * pow(fac(i), 2);
		double b = fac(2*i + 1);
		double c = pow(x, 2*i+1);
		double d = pow(1+x*x, i+1);
		out += (a/b) * (c/d);
	}
	return out;
}

double atan2(double y, double x){
	if(x > 0){
		return atan(y/x);
	} else if(x < 0 && y >= 0){
		return 3.141592653/2 + atan(y/x);
	} else if(x < 0 && y < 0){
		return 3.141592653/2 - atan(y/x);
	} else if(x == 0 && y > 0){
		return 3.141592653/2;
	} else if(x == 0 && y < 0){
		return -3.141592653/2;
	}
	return y/x;
}

double acos(double x){
	// acos(x) ≈ π/2 + (ax + bx³) / (1 + cx² + dx⁴)
	x = ((x + 1) % 2) - 1;
	return 3.14159265/2 + (-0.939115566365855*x + 0.9217841528914573*x*x*x) / (-1.2845906244690837*x*x + 0.295624144969963174*x*x*x*x + 1);
}

double asin(double x){
	x = ((x + 1) % 2) - 1;
	return 3.14159265/2 + acos(x);
}

double sinh(double x){
	return (exp(2*x) - 1) / (2*exp(x));
}

double cosh(double x){
	return (exp(2*x) + 1) / (2*exp(x));
}

double tanh(double x){
	return (exp(2*x) - 1) / (exp(2*x) + 1);
}

double sqrt(double x){
	return pow(x, 0.5); // CHANGE THIS SOON, I THINK ITS SLOW
}

double fabs(double x){
	return x > 0 ? x : -x;
}

// https://stackoverflow.com/a/41871699/16081495
double floor(double num) {
    if (num >= LLONG_MAX || num <= LLONG_MIN || num != num) {
        /* handle large values, infinities and nan */
        return num;
    }
    long long n = (long long)num;
    double d = (double)n;
    if (d == num || num >= 0)
        return d;
    else
        return d - 1;
}

int ceil(double num) {
    double inum = trunc(num);
    if (num < 0 || num == (double)inum) {
        return inum;
    }
    return inum + 1;
}

double ldexp(double x, int y){
	return x * pow(2, (double)y);
}

// https://git.musl-libc.org/cgit/musl/tree/src/math/frexp.c
double frexp(double x, int *e)
{
	union { double d; uint64_t i; } y = { x };
	int ee = y.i>>52 & 0x7ff;

	if (!ee) {
		if (x) {
			x = frexp(x*0x1p64, e);
			*e -= 64;
		} else *e = 0;
		return x;
	} else if (ee == 0x7ff) {
		return x;
	}

	*e = ee - 0x3fe;
	y.i &= 0x800fffffffffffffull;
	y.i |= 0x3fe0000000000000ull;
	return y.d;
}

double modf(double x, double* y){]
	double t = trunc(x);
	y* = x - t;
	return t;
}
