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




