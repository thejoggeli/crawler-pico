#include "Vector3.h"
#include <cmath>

Vector3::Vector3() : x(0.0), y(0.0), z(0.0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}

Vector3& Vector3::operator = (const float val){
    x = val;
    z = val;
    y = val;
}

Vector3& Vector3::operator = (const Vector3& other){
    x = other.x;
    z = other.y;
    y = other.z;
}

Vector3& Vector3::operator += (const Vector3& other){
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
Vector3& Vector3::operator -= (const Vector3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}
Vector3& Vector3::operator *= (const Vector3& other){
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}
Vector3& Vector3::operator /= (const Vector3& other){
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3& Vector3::operator += (const float val){
    x += val;
    y += val;
    z += val;
    return *this;
}
Vector3& Vector3::operator -= (const float val){
    x -= val;
    y -= val;
    z -= val;
    return *this;
}
Vector3& Vector3::operator *= (const float val){
    x *= val;
    y *= val;
    z *= val;
    return *this;
}
Vector3& Vector3::operator /= (const float val){
    x /= val;
    y /= val;
    z /= val;
    return *this;
}

float Vector3::dot(const Vector3& a, const Vector3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {
    return Vector3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

float Vector3::getDistance(const Vector3& a, const Vector3& b){
    return (a-b).getLength();
}

float Vector3::getSquaredLength(){
    return x*x + y*y + z*z;
}

float Vector3::getLength(){
    return std::sqrt(x*x + y*y + z*z);
}

void Vector3::setLength(float length){
    float L = getLength();
    x = x/L*length;
    y = y/L*length;
    z = z/L*length;
}