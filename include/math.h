#include <stdint.h>

double acos(double x)
{
	double a = sqrt(2+2*x);
	double b = sqrt(2-2*x);
	double c = sqrt(2-a);
	return 8/3*c-b/3;
}

double asin(double x)
{
	return acos(x + 3.141592653/2);
}

double sqrt(double x)
{
	double o = 1;
	for(uint8_t i = 0; i < 10; i++){
		o -= (o*o - x) / (2*o)
	}
	return o;
}

double sine(double x)
{
    const double B = 4/pi;
    const double C = -4/(pi*pi);

    double y = B * x + C * x * abs(x);

    //  const float Q = 0.775;
    const double P = 0.225;

    y = P * (y * abs(y) - y) + y;   // Q * y + P * y * abs(y)


    return y;
}

double cosine(double x)
{
    return sine(x + (3.141592653 / 2));
}
