#pragma once
#include <math.h>
#include "checkML.h"

struct Point2D {
	double x_;
	double y_;

	Point2D(double x, double y) : x_(x), y_(y) {}
};

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D(double x, double y) : x_(x), y_(y) {}

	Vector2D normalize();
	Vector2D operator+(Vector2D const& vector);
	Vector2D operator-(Vector2D const& vector);
	double operator*(Vector2D const& vector);
	Vector2D operator*(int num);

	double getX() const { return x_; }
	double getY() const { return y_; }

	double getModulo() const;
};


