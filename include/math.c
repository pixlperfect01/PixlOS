#include <stdint.h>

#define PI 3.14159265358979323846

double acos(double x){
// 	acos(x) ≈ π/2 + (ax + bx³) / (1 + cx² + dx⁴)
	double x2 = x*x;
	return PI/2 + (-0.939115566365855+0.9217841528914573*x2*x) / (-1.2845906244690837*x2 + 0.295624144969963174*x2*x2 + 1);
}

double asin(double x){
	return PI/2 - acos(x);
}
