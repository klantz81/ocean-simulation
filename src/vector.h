#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class vector3 {
  private:
  protected:
  public:
    float x, y, z;
    vector3();
    vector3(float x, float y, float z);
    float operator*(const vector3& v);
    vector3 cross(const vector3& v);
    vector3 operator+(const vector3& v);
    vector3 operator-(const vector3& v);
    vector3 operator*(const float s);
    vector3& operator=(const vector3& v);
    float length();
    vector3 unit();
};

class vector2 {
  private:
  protected:
  public:
    float x, y;
    vector2();
    vector2(float x, float y);
    float operator*(const vector2& v);
    vector2 operator+(const vector2& v);
    vector2 operator-(const vector2& v);
    vector2 operator*(const float s);
    vector2& operator=(const vector2& v);
    float length();
    vector2 unit();
};

#endif