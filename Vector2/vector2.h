#include <iostream>
#include <cmath>



class Vector2 {
    public:

    float x, y;

     Vector2 (float _x = 0, float _y = 0) : x(_x), y(_y)
     {}

    Vector2 operator + (const Vector2& other) const
    {
        Vector2 v;
        v.x = x + other.x;
        v.y = y + other.y;
        return v;
    }

    Vector2& operator += (const Vector2& other)
    {
        x += other.x;
        y += other.y;
    }

    Vector2 operator - (const Vector2& other) const
    {
        Vector2 v;
        v.x = x - other.x;
        v.y = y - other.y;
        return v;
    }

    Vector2& operator -= (const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
    }

    float operator * (const Vector2& other) const           //скалярное умножение
    {
        float result = 0;
        return result = other.x * x + other.y * y;
    }

    float operator ^ (const Vector2& other) const           //векторное умножение
    {
        float result = 0;
        return result = x * other.y - y * other.x;
    }

    Vector2 operator * (float k) const
    {
        return Vector2 (x * k, y * k);
    }

    Vector2 operator / (float k) const
    {
        return Vector2 (x / k, y / k);
    }

    Vector2 Norm() const
    {
        Vector2 v;
        v.x = x / sqrt(x * x + y * y);
        v.y = y / sqrt(x * x + y * y);
        return v;
    }

    Vector2 Perpendicular () const
    {
        return Vector2(y, -x);
    }

    float Len() const
    {
        return sqrt(x * x + y*y);
    }

    float squareLen() const
    {
        return (x * x + y * y);
    }

    Vector2 operator - ()
    {
        return Vector2 (-x, -y);
    }

    Vector2& rotate (float angle)
    {
        x = x * cos(angle) - y * sin(angle);
        y = x * sin(angle) + y * cos(angle);
        return *this;
    }

    Vector2 getRotated (float angle) const
    {
        Vector2 v;
        v.x = x * cos(angle) - y * sin(angle);
        v.y = x * sin(angle) + y * cos(angle);
        return v;
    }
};

std::ostream& operator << (std::ostream& stream, const Vector2& v);
std::istream& operator >> (std::istream& stream, Vector2& v);
