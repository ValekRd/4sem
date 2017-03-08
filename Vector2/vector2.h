#include <iostream>
#include <cmath>



class Vector2 {
    public:

    float x, y;
    Vector2 (float _x = 0, float _y = 0) : x(_x), y(_y) {}
    Vector2 operator + (const Vector2& other) const;
    Vector2& operator += (const Vector2& other);
    Vector2 operator - (const Vector2& other) const;
    Vector2& operator -= (const Vector2& other);
    float operator * (const Vector2& other) const;
    float operator ^ (const Vector2& other) const;
    Vector2 operator * (float k) const;
    Vector2 operator / (float k) const;
    Vector2 Norm() const;
    Vector2 Perpendicular () const;
    float Len() const;
    float squareLen() const;
    Vector2 operator - ();
    Vector2& rotate (float angle);
    Vector2 getRotated (float angle) const;
};

std::ostream& operator << (std::ostream& stream, const Vector2& v);
std::istream& operator >> (std::istream& stream, Vector2& v);
