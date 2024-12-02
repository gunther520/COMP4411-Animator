#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#pragma warning(disable : 4786)

#include <functional>
#include <iostream>
#include <cmath>

//using namespace std;

class Point
{
public:

	Point(void);
	Point(const float& x, const float& y);

	void toStream(std::ostream& output_stream) const;
	void fromStream(std::istream& input_stream);

	float distance(const Point& p) const {
		float xd = x - p.x;
		float yd = y - p.y;
		return sqrtf(xd * xd + yd * yd);
	}

	//operators
	Point operator+(const Point& p) const {
		return Point(x + p.x, y + p.y);
	}

	Point operator-(const Point& p) const {
		return Point(x - p.x, y - p.y);
	}

	Point operator*(const float f) const {
		return Point(x * f, y * f);
	}

	Point operator/(const float f) const {
		return Point(x / f, y / f);
	}

	Point& operator+=(const Point& p) {
		x += p.x;
		y += p.y;
		return *this;
	}

	Point& operator-=(const Point& p) {
		x -= p.x;
		y -= p.y;
		return *this;
	}

	Point& operator*=(const float f) {
		x *= f;
		y *= f;
		return *this;
	}

	Point& operator/=(const float f) {
		x /= f;
		y /= f;
		return *this;
	}


	float x;
	float y;
};

std::ostream& operator<<(std::ostream& output_stream, const Point& point);
std::istream& operator>>(std::istream& input_stream, Point& point);

class PointSmallerXCompare : public std::binary_function<const Point&, const Point&, bool>
{
public:
	bool operator()(const Point& first, const Point& second) const;
};

class PointLargerXCompare : public std::binary_function<const Point&, const Point&, bool>
{
public:
	bool operator()(const Point& first, const Point& second) const;
};

#endif // POINT_H_INCLUDED
