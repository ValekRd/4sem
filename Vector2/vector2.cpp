#include "vector2.h"
#include <iostream>

using namespace std;

ostream& operator << (ostream& stream, const Vector2& v)
{
    stream << "(" << v.x <<", "<< v.y << ")";
    return stream;
}

istream& operator >> (istream& stream, Vector2& v)
{
    stream >> v.x >> v.y;
    return stream;
}

Vector2 Vector2::operator + (const Vector2& other) const
{
    return Vector2 (x + other.x, y + other.y);
}

Vector2& Vector2::operator += (const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 Vector2::operator - (const Vector2& other) const
{
    return Vector2 (x - other.x, y - other.y);
}

Vector2& Vector2::operator -= (const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

float Vector2::operator * (const Vector2& other) const
{
    return other.x * x + other.y * y;
}

float Vector2::operator ^ (const Vector2& other) const
{
    return x * other.y - y * other.x;
}

Vector2 Vector2::operator * (float k) const
{
    return Vector2 (x * k, y * k);
}

Vector2 Vector2::operator / (float k) const
{
    return Vector2 (x / k, y / k);
}

Vector2 Vector2::Norm() const
{
    return Vector2 (x / sqrt(x * x + y * y), y / sqrt(x * x + y * y));
}

Vector2 Vector2::Perpendicular () const
{
    return Vector2(y, -x);
}

float Vector2::Len() const
{
    return sqrt(x * x + y*y);
}

float Vector2::squareLen() const
{
    return (x * x + y * y);
}

Vector2 Vector2::operator - ()
{
    return Vector2 (-x, -y);
}

Vector2& Vector2::rotate (float angle)
{
    x = x * cos(angle) - y * sin(angle);
    y = x * sin(angle) + y * cos(angle);
    return *this;
}

Vector2 Vector2::getRotated (float angle) const
{
    return Vector2(x, y).rotate(angle);
}