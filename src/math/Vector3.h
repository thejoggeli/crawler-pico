#ifndef __VECTOR_3__
#define __VECTOR_3__

class Vector3 {
public:

    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    Vector3();
    Vector3(float x, float y, float z);
    Vector3(const Vector3& v);
    
    Vector3& operator = (const float val);
    Vector3& operator = (const Vector3& other);

    Vector3& operator += (const Vector3& other);
    Vector3& operator -= (const Vector3& other);
    Vector3& operator *= (const Vector3& other);
    Vector3& operator /= (const Vector3& other);

    Vector3& operator += (const float val);
    Vector3& operator -= (const float val);
    Vector3& operator *= (const float val);
    Vector3& operator /= (const float val);

    static float dot(const Vector3& a, const Vector3& b);
    static Vector3 cross(const Vector3& a, const Vector3& b);
    static float getDistance(const Vector3& a, const Vector3& b);
    
    friend Vector3 operator + (const Vector3& a, const Vector3& b){
        return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
    }
    friend Vector3 operator - (const Vector3& a, const Vector3& b){
        return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);
    }
    friend Vector3 operator * (const Vector3& a, const Vector3& b){
        return Vector3(a.x*b.x, a.y*b.y, a.z*b.z);
    }
    friend Vector3 operator / (const Vector3& a, const Vector3& b){
        return Vector3(a.x/b.x, a.y/b.y, a.z/b.z);
    }

    friend Vector3 operator + (const Vector3& a, float val){
        return Vector3(a.x+val, a.y+val, a.z+val);
    }
    friend Vector3 operator - (const Vector3& a, float val){
        return Vector3(a.x-val, a.y-val, a.z-val);
    }
    friend Vector3 operator * (const Vector3& a, float val){
        return Vector3(a.x*val, a.y*val, a.z*val);
    }
    friend Vector3 operator / (const Vector3& a, float val){
        return Vector3(a.x/val, a.y/val, a.z/val);
    }

    float getLength();
    float getSquaredLength();
    void setLength(float length);



};

#endif