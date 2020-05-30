#pragma once
#include <math.h>
#include <iostream>
#include "checkML.h"

struct Point2D {
	double x_;
	double y_;

	Point2D(double x, double y) : x_(x), y_(y) {}
	Point2D operator+(Point2D const& p1) {
		return Point2D(x_ + p1.x_, y_ + p1.y_);
	}
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
	friend std::ostream& operator<<(std::ostream& out, Vector2D& v);
	friend std::istream& operator>>(std::istream& in, Vector2D& v);

	double getX() const { return x_; }
	double getY() const { return y_; }

	double getModulo() const;
};


