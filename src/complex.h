#ifndef COMPLEX_H
#define COMPLEX_H

class complex {
  private:
  protected:
  public:
    float a, b;
    static unsigned int additions, multiplications;
    complex();
    complex(float a, float b);
    complex conj();
    complex operator*(const complex& c) const;
    complex operator+(const complex& c) const;
    complex operator-(const complex& c) const;
    complex operator-() const;
    complex operator*(const float c) const;
    complex& operator=(const complex& c);
    static void reset();
};

#endif