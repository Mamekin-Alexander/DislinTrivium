#include <iostream>
#include <discpp.h>
#include <utility>	
Dislin g;
typedef std::pair<double, double> T;
double const pi = 4 * atan(1);
T function(double t)
{
	T res(0, 0);
	res.first = sin(t)*(exp(cos(t)) - 2 * cos(4 * t) + sin(5 * 1 / 12 * t));
	res.second = cos(t) *(exp(cos(t)) - 2 * cos(4 * t) + sin(5 * 1 / 12 * t));
	return res;
}
T elips(double t)
{
	T res(0, 0);
	const double a = 10.0;
	const double b = 5.0;
	res.first = a * cos(t);
	res.second = b * sin(t);
	return res;
}
void DrawElips(int n)
{
	const double dt = 4 * pi / (n-1);
	double t = 0;
	double* x = new double[n];
	double* y = new double[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = elips(t).first;
		y[i] = elips(t).second;
		t = t + dt;
	}
	g.qplot(x, y, n);
}
void DrawFunction(int n)
{

	double dt = 12 * pi / (n-1);
	double t = 0;
	double* x = new double[n];
	double* y = new double[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = function(t).first;
		y[i] = function(t).second;
		t = t + dt;
	}
	g.qplot(x, y, n);
	return;
}
int main()
{

	g.metafl("cons");
	g.scrmod("revers");
	g.disini();
	DrawElips(200);
	//DrawFunction(2000);
	g.disfin();
	return 0;
}