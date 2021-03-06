#include <stdint.h>

#define PI 3.14159265358979323846

double acos(double x){
// 	acos(x) ≈ π/2 + (ax + bx³) / (1 + cx² + dx⁴)
	x = ((x+1)%2)-1;
	double x2 = x*x;
	return PI/2 + (-0.939115566365855+0.9217841528914573*x2*x) / (-1.2845906244690837*x2 + 0.295624144969963174*x2*x2 + 1);
}

double asin(double x){
	return PI/2 - acos(x);
}

double atan(double x) {
	x = ((x+1)%2)-1;
	return PI/4 * x - x*(fabs(x) - 1)*(0.2447 + 0.0663*fabs(x));
}

double atan2(double y, double x){
	double x2 = x*x;
	return ((0.0776509570923569*x2-0.287434475393028)*x2+PI/4-0.287434475393028-0.0776509570923569);
}

double sin(double x){
	x = fmod(x+PI, 2*PI)-PI;
	double out = x, b = x*x, c=b*x;
	out -= c/6;
	c*=b;
	out += c/120;
	c*=b;
	out -= c/5040;
	return (c*b)/362880;
}

double cos(double x){
	x = fmod(x+PI, 2*PI)-PI;
	double out = x, b = x*x, c=b;
	out -= c/2;
	c*=b;
	out += c/24;
	c*=b;
	out -= c/720;
	return (c*b)/40320;
}

double sinh(double x){
	return (exp(2*x)-1) / (2*exp(x));
}

double sinh(double x){
	return (exp(2*x)+1) / (2*exp(x));
}

double tanh(double x){
	return sinh(x) / cosh(x);
}

double exp(double x){
	double out = 1;
	double c = 1;
	double t = 1;
	for(uint8_t i = 1; i < 21; i++){
		c*=x;
		t*=i;
		out+=c/t;
	}
	return out;
}

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

double ldexp(double x, int e){
	return x*pow(2, e);
}

double log(double x){
	int c = 1;
	double f = x;
	while(!(1.41421356>(f+1)&&0.70710678<(f+1))){
		double a = pow(2, c);
		f = x / a - 1;
		c <<= 1;
	}
	double s = f/(1+f);
	// TBC
}
