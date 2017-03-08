#include <iostream>
#include "vector2.h"

int main() {

    using namespace std;

    Vector2 v1(2, 2), v2(1, 3);
    cout << "v1 = v5 = " << v1 << "; v2 = " << v2 << endl;
    cout << "summa = " << (v1 + v2) << endl;
    cout << "difference = " << (v1 - v2) << endl;
    cout << "scalar product = " << (v1 * v2) << endl;
    cout << "cross product = " << (v1 ^ v2) << endl;
    cout << "multiplication on constant = " << (v2 * 5) << endl;
    cout << "division on constant = " << (v1 / 2) << endl;
    cout << "norm v1 = " << v1.Norm() << endl;
    cout << "perpendicular v1 = " << v1.Perpendicular() << endl;
    cout << "len v2 = " << v2.Len() << endl;
    cout << "squareLen v1 = " << v1.squareLen() << endl;
    cout << "-v2 = " << - v2 << endl;
    cout << "getRotated v1 = " << v1.getRotated(180) << endl;

    v1 += v2;
    cout << "summa2 = " << v1 << endl;

    Vector2 v3(2, 2), v4(1, 3);
    v3 -= v4;
    cout << "difference2 = " << v3 << endl;

    Vector2 v5(2, 2);
    cout << "rotated v5 = " << v5.rotate(180) << endl;

    return 0;
}