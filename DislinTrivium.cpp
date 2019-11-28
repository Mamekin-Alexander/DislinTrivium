#include <iostream>
#include <discpp.h>
#include <utility>

#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef unix
#include <unistd.h>
#endif

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
namespace elips {
	const double a = 10.0;
	const double b = 5.0;
	T elips(double t)
	{
		T res(0, 0);

		res.first = a * cos(t);
		res.second = b * sin(t);
		return res;
	}
	void DrawElips()
	{
		g.metafl("cons");
		g.scrmod("revers");
		g.disini();
		const int n = 200;
		const double dt = 4 * pi / (n - 1);
		double t = 0;
		double* x = new double[n];
		double* y = new double[n];
		double *xev = new double[n];
		double *yev = new double[n];
		const double focus = sqrt(a*a - b*b);
		for (int i = 0; i < n; i++)
		{
			x[i] = elips(t).first;
			y[i] = elips(t).second;
			xev[i] = (a*a - b * b) / a * std::pow(cos(t), 3);
			yev[i] = (b*b - a * a) / b * std::pow(sin(t), 3);
				t = t + dt;
		}
		g.center();
		g.graf(-10, 10, -10, 2, -15, 15, -15, 2);


		g.xaxis(-a, a, -a, a/2, g.nxposn(a)-g.nxposn(-a), "", 0, g.nxposn(-a), g.nyposn(0));
		g.yaxis(-15, 15, -15, 5 , g.nyposn(-15) - g.nyposn(15), "", 0, g.nxposn(0), g.nyposn(-15));
		g.rlsymb(21, focus, 0);
		g.rlsymb(21, -focus, 0);
		g.messag("F", g.nxposn(focus), g.nyposn(1.5));
		g.messag("F", g.nxposn(-focus), g.nyposn(1.5));
		g.curve(x, y, n);
		g.curve(xev, yev, n);
		g.endgrf();
		g.disfin();
	}
}
void animation()
{
	std::cout << "Frequancy and time of observation of animation are set in code" << '\n';
	g.metafl("cons");
	g.scrmod("revers");
	g.disini();
	const double frequency = 10;
	double t = 0;
	const double dt = 1/frequency/ 100;
	double x, y;
	
	while (t<=2/frequency)
	{	
		g.erase();
		g.graf(-1, 1, -1, 0.5, -1, 1, -1, 0.5);
		x = cos(2*pi*frequency*t);
		y = sin(2*pi*frequency*t);
		g.rlsymb(21, x, y);
#ifdef _WIN32
		Sleep(dt*1000);
#endif
#ifdef unix
		Sleep(dt);
#endif
		t = t + dt;

		g.endgrf();
	}
	g.disfin();
	return;
}
void DrawFunction()
{
	g.metafl("cons");
	g.scrmod("revers");
	g.disini();
	const int n = 2000;
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
	g.disfin();
	return;
}
int main()
{

	char c;
	bool run = true;
	while (run)
	{
		std::cout << "Enter 'f' to see function plot, 'e' - elips, 'a' - animation, 'q' - to quit"<<'\n';
		std::cin >> c;
		switch (c)
		{
		case 'f':
			DrawFunction();
			break;
		case 'e':
			elips::DrawElips();
			break;
		case 'a':
			animation();
			break;
		case 'q':
			run = false;
			break;
		default:
			std::cout << "Error" << '\n';
			break;
		}
	}
	return 0;
}