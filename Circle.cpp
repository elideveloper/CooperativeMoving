#include "Circle.h"

Circle::Circle()
{}

Circle::Circle(const Circle& circle) : Shape(circle.position, circle.direction), radius(circle.radius)
{}

Circle::Circle(const Vec2D& pos, const Vec2D& dir, double radius) : Shape(pos, dir), radius(radius)
{}

double Circle::getRadius() const
{
	return this->radius;
}

double Circle::getArea() const
{
	return PI * this->radius * this->radius;
}

bool Circle::isInclude(const Vec2D& point) const
{
	return (this->position.getDistance(point) <= this->radius) ? true : false;
}

Circle Circle::getShifted(const Vec2D& vector) const
{
	return Circle(this->position.add(vector), this->direction, this->radius);
}

Circle Circle::getRotated(const Vec2D& vector) const
{
	return Circle(this->position, this->direction.add(vector.getUnit()).getUnit(), this->radius);
}

Circle Circle::getRotated(double angle) const
{
	return Circle(this->position, this->direction.getRotated(angle), this->radius);
}