#include "Vector2D.h"

double Vector2D::getModulo() const {
	return sqrt(x_ * x_ + y_ * y_);
}

Vector2D Vector2D::normalize() {
	double mod = getModulo();
	return Vector2D(x_ / mod, y_ / mod);
}

Vector2D Vector2D::operator+(Vector2D const& vector) {
	return Vector2D(x_ + vector.x_, y_ + vector.y_);
}

Vector2D Vector2D::operator-(Vector2D const& vector) {
	return Vector2D(x_ +-vector.x_, y_ - vector.y_);
}

double Vector2D::operator*(Vector2D const& vector) {
	return x_ * vector.x_ + y_ * vector.y_;
}

Vector2D Vector2D::operator*(int num) {
	return Vector2D(x_ * num, y_ * num);
}

std::ostream& operator<<(std::ostream& out, Vector2D& v)
{
	out << v.x_ << " " << v.y_;
	return out;
}

std::istream& operator>>(std::istream& in, Vector2D& v)
{
	in >> v.x_ >> v.y_;
	return in;
}
