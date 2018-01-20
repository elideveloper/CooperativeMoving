#pragma once

#include "Vec2D.h"

class Shape {
protected:
	Vec2D position;
	Vec2D direction;
public:
	Shape();
	Shape(const Vec2D& pos, const Vec2D& dir);
	Shape(const Shape& shape);
	Vec2D getPosition() const;
	Vec2D getDirection() const;
	virtual double getArea() const = 0;
	virtual bool isInclude(const Vec2D& point) const = 0;
	virtual void shift(const Vec2D& vector);		// shifts position to given vector, keeps direction
	virtual void move(double dist);					// shifts position to given distance by itself direction, keeps direction
	virtual void rotate(const Vec2D& vector);
	virtual void rotate(double angle);
};
