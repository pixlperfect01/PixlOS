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
