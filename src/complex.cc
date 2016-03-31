#include "complex.h"

unsigned int complex::additions = 0;
unsigned int complex::multiplications = 0;

complex::complex() : a(0.0f), b(0.0f) { }
complex::complex(float a, float b) : a(a), b(b) { }
complex complex::conj() { return complex(this->a, -this->b); }

complex complex::operator*(const complex& c) const {
	complex::multiplications++;
	return complex(this->a*c.a - this->b*c.b, this->a*c.b + this->b*c.a);
}

complex complex::operator+(const complex& c) const {
	complex::additions++;
	return complex(this->a + c.a, this->b + c.b);
}

complex complex::operator-(const complex& c) const {
	complex::additions++;
	return complex(this->a - c.a, this->b - c.b);
}

complex complex::operator-() const {
	return complex(-this->a, -this->b);
}

complex complex::operator*(const float c) const {
	return complex(this->a*c, this->b*c);
}

complex& complex::operator=(const complex& c) {
	this->a = c.a; this->b = c.b;
	return *this;
}

void complex::reset() {
	complex::additions = 0;
	complex::multiplications = 0;
}