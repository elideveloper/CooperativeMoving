#pragma once

#include "Shape.h"

class Circle : public Shape {
	double radius;
public:
	Circle();
	Circle(const Circle& circle);
	Circle(const Vec2D& pos, const Vec2D& dir, double radius);
	double getRadius() const;
	double getArea() const;
	bool isInclude(const Vec2D& point) const;
	Circle getShifted(const Vec2D& vector) const;
	Circle getRotated(const Vec2D& vector) const;
	Circle getRotated(double angle) const;
	// TODO intersections with other shapes
};
