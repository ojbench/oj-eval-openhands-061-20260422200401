#ifndef SJTU_COMPLEX_HPP
#define SJTU_COMPLEX_HPP

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
// 你不可以使用任何其他的头文件!

namespace sjtu {

class divided_by_zero final : public std::exception {
public:
  divided_by_zero() = default;
  ~divided_by_zero() = default;
  const char *what() const noexcept override { return "complex divided by zero!"; }
};

inline int sign(double x) {
  const double eps = 1e-6;
  return (x > eps) - (x < -eps);
}

class complex {
private:
  double a, b; // a + bi

public:
  // constructors
  complex() : a(0.0), b(0.0) {}
  complex(double a) : a(a), b(0.0) {}
  complex(double a, double b) : a(a), b(b) {}

  // accessors
  double &real() { return a; }
  double &imag() { return b; }

  // unary operators
  complex operator-() const { return complex(-a, -b); }
  complex operator~() const { return complex(a, -b); }

  // binary operators
  complex operator+(const complex &rhs) const { return complex(a + rhs.a, b + rhs.b); }
  complex operator-(const complex &rhs) const { return complex(a - rhs.a, b - rhs.b); }
  complex operator*(const complex &rhs) const {
    return complex(a * rhs.a - b * rhs.b, a * rhs.b + b * rhs.a);
  }
  complex operator/(const complex &rhs) const {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) throw divided_by_zero();
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    double ra = (a * rhs.a + b * rhs.b) / denom;
    double rb = (b * rhs.a - a * rhs.b) / denom;
    return complex(ra, rb);
  }

  // compound assignments
  complex &operator+=(const complex &rhs) {
    a += rhs.a; b += rhs.b; return *this;
  }
  complex &operator-=(const complex &rhs) {
    a -= rhs.a; b -= rhs.b; return *this;
  }
  complex &operator*=(const complex &rhs) {
    double na = a * rhs.a - b * rhs.b;
    double nb = a * rhs.b + b * rhs.a;
    a = na; b = nb; return *this;
  }
  complex &operator/=(const complex &rhs) {
    if (sign(rhs.a) == 0 && sign(rhs.b) == 0) throw divided_by_zero();
    double denom = rhs.a * rhs.a + rhs.b * rhs.b;
    double na = (a * rhs.a + b * rhs.b) / denom;
    double nb = (b * rhs.a - a * rhs.b) / denom;
    a = na; b = nb; return *this;
  }

  // comparison
  bool operator==(const complex &rhs) const {
    return std::fabs(a - rhs.a) < 1e-6 && std::fabs(b - rhs.b) < 1e-6;
  }

  // conversion
  explicit operator bool() const { return !(sign(a) == 0 && sign(b) == 0); }

  // output
  friend std::ostream &operator<<(std::ostream &os, const complex &x) {
    os.setf(std::ios::fixed);
    os << std::setprecision(6);
    double ra = (sign(x.a) == 0 ? 0.0 : x.a);
    double rb = (sign(x.b) == 0 ? 0.0 : x.b);
    if (sign(ra) < 0) os << '-';
    os << std::fixed << std::setprecision(6) << std::fabs(ra);
    os << (sign(rb) < 0 ? '-' : '+');
    os << std::fixed << std::setprecision(6) << std::fabs(rb) << 'i';
    return os;
  }
};

} // namespace sjtu

#endif
