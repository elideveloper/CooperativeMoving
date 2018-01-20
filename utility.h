#pragma once

#define PI 3.14159265358979323846
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

const double EPS = 1e-8;

inline double boundBetween(double min, double max, double val)
{
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
