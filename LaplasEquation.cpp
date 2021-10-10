#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <array>
#include <cmath>
#include <stdint.h>

#define N 6
#define K 6

struct RectanglePoints {
	double x_0, x_l;
	double y_0, y_m;
};

namespace InitialFunctions {
	inline double leftSideRectangle(double y) { return 15 * sqrt(y); }
	inline double rightSideRectangle(double y) { return 30 * y * (1 - y); }
	inline double upSideRectangle(double x) { return 15 * (1 - x); }
	inline double downSideRectangle(double x) { return 0; }

}

using namespace InitialFunctions;

class Grid {
private:

	RectanglePoints rectangle;

	double length_x;
	double length_y;
	double h_xyStep;
	
public:
	Grid(); //default constructor
	Grid(double l, double m, double h, std::array<double, N>& x, std::array<double, N>& y);

    void setPoints();
	void createGrid(std::array<double, N>& x, std::array<double, K>& y);
	void getGrid(std::array<double, N>& x, std::array<double, K>& y);
};

Grid::Grid()
{
	length_x = 1;
	length_y = 1;
	h_xyStep = 0.2;

	setPoints();
}

Grid::Grid(double l, double m, double h, std::array<double, N>& x, std::array<double, K>& y) {

	length_x = l;
	length_y = m;
	h_xyStep = h;

	setPoints();
	createGrid(x, y);
}

void Grid::setPoints()
{

	rectangle.x_0 = 0;
	rectangle.y_0 = 0;
	rectangle.x_l = rectangle.x_0 + length_x;
	rectangle.y_m = rectangle.y_0 + length_y;
}

void Grid::createGrid(std::array<double, N>& x, std::array<double, K>& y)
{
	x[0] = rectangle.x_0;
	y[0] = rectangle.y_0;
	
	for (uint8_t i = 0; i < N; ++i)
	{
		x[i] = i * h_xyStep;
	}

	for (uint8_t j = 0; j < K; ++j)
	{
		y[j] = j * h_xyStep;
	}
}

void Grid::getGrid(std::array<double, N>& x, std::array<double, K>& y)
{
	for (uint8_t i = 0; i < N; i++)
		printf("%lf ", x[i]);
	printf("\n\n");
	for (uint8_t j = 0; j < K; j++)
		printf("%lf ", y[j]);
	printf("\n\n");

}


class LaplasEquationSolver {
public:
	LaplasEquationSolver(double (*u1)[N], std::array<double, N>& x, std::array<double, K>& y);
};

LaplasEquationSolver::LaplasEquationSolver(double (*u1)[N], std::array<double, N>& x, std::array<double, K>& y)
{
	double u2[N][K] = { 0 };
	double w = 0.5;

	for (uint8_t i = 0; i < N; ++i)
	{
		u1[i][0] = downSideRectangle(x[i]);
		u1[i][K - 1] = upSideRectangle(x[i]);
	}

	for (uint8_t j = 0; j < K; ++j)
	{
		u1[0][j] = leftSideRectangle(y[j]);
		u1[N - 1][j] = rightSideRectangle(y[j]);
	}


}



int main() 
{
	std::array<double, N> x = { 0 };
	std::array<double, K> y = { 0 };
	double u[N][K] = { 0 };

	Grid grid(1, 1, 0.2, x, y); //will call 2nd constructor (not default)

	grid.getGrid(x, y);

	LaplasEquationSolver mySolver(u, x, y);

	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < K; ++j)
			printf(" %lf\t", u[i][j]);
		printf("\n\n");
	}

	return 0;
}