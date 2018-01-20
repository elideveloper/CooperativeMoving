#include "Shape.h"

Shape::Shape() : position(Vec2D()), direction(Vec2D())
{}

Shape::Shape(const Vec2D& pos, const Vec2D& dir) : position(pos), direction(dir.getUnit())
{}

Shape::Shape(const Shape& shape) : position(shape.position), direction(shape.direction)
{}

Vec2D Shape::getPosition() const
{
	return this->position;
}

Vec2D Shape::getDirection() const
{
	return this->direction;
}

void Shape::shift(const Vec2D& vector)
{
	this->position = this->position.add(vector);
}

void Shape::move(double dist)
{
	this->position = this->position.add(Vec2D(this->direction.getX() * dist, this->direction.getY() * dist));
}

void Shape::rotate(const Vec2D& vector)
{
	this->direction = this->direction.add(vector.getUnit()).getUnit();
}

void Shape::rotate(double angle)
{
	this->direction.rotate(angle);
}