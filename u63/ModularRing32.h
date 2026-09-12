#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <type_traits>

namespace u63 {

template <typename ModProvider>
class ModularRing32 {
  int32_t r{0};

public:
  static_assert(
      std::is_same_v<std::decay_t<decltype(ModProvider::value)>, int32_t>);
  static constexpr int32_t mod() { return ModProvider::value; }

  constexpr ModularRing32() : r{0} {}
  /*implicit*/ constexpr ModularRing32(int64_t value) {
    if (value <= -mod() || value >= mod())
      value %= mod();
    if (value < 0)
      value += mod();
    r = value;
  }
  static constexpr ModularRing32 unsafe(int32_t value) {
    ModularRing32 result;
    result.r = value;
    return result;
  }

  template <typename T>
  explicit constexpr operator T() {
    return static_cast<T>(r);
  }

  constexpr ModularRing32 &operator+=(ModularRing32 other) {
    r += other.r;
    if (r >= mod())
      r -= mod();
    return *this;
  }
  constexpr friend ModularRing32 operator+(ModularRing32 lhs,
                                           ModularRing32 rhs) {
    return lhs += rhs;
  }
  constexpr ModularRing32 operator+() const { return *this; }
  constexpr ModularRing32 &operator++() const { return *this += 1; }
  constexpr ModularRing32 operator++(int) {
    ModularRing32 copy{*this};
    *this += 1;
    return copy;
  }

  constexpr ModularRing32 &operator-=(ModularRing32 other) {
    r -= other.r;
    if (r < 0)
      r += mod();
    return *this;
  }
  constexpr friend ModularRing32 operator-(ModularRing32 lhs,
                                           ModularRing32 rhs) {
    return lhs -= rhs;
  }
  constexpr ModularRing32 operator-() const {
    ModularRing32 neg{*this};
    if (neg.r > 0)
      neg.r = mod() - neg.r;
    return neg;
  }
  constexpr ModularRing32 &operator--() const { return *this -= 1; }
  constexpr ModularRing32 operator--(int) {
    ModularRing32 copy{*this};
    *this -= 1;
    return copy;
  }

  constexpr ModularRing32 &operator*=(ModularRing32 other) {
    r = static_cast<int64_t>(r) * other.r % mod();
    return *this;
  }
  constexpr friend ModularRing32 operator*(ModularRing32 lhs,
                                           ModularRing32 rhs) {
    return lhs *= rhs;
  }

  constexpr ModularRing32 bpow(int64_t power) const {
    ModularRing32 result{1};
    for (ModularRing32 base{*this}; power > 0; power /= 2, base *= base) {
      if (power & 1) {
        result *= base;
      }
    }
    return result;
  }

  constexpr ModularRing32 inv() const { return ModularRing32{calcInverse(r)}; }

  constexpr ModularRing32 &operator/=(ModularRing32 other) {
    return *this *= other.inv();
  }
  constexpr friend ModularRing32 operator/(ModularRing32 lhs,
                                           ModularRing32 rhs) {
    return lhs /= rhs;
  }

  constexpr friend bool operator==(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r == rhs.r;
  }
  constexpr friend bool operator!=(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r != rhs.r;
  }
  constexpr friend bool operator<(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r < rhs.r;
  }
  constexpr friend bool operator<=(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r <= rhs.r;
  }
  constexpr friend bool operator>(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r > rhs.r;
  }
  constexpr friend bool operator>=(ModularRing32 lhs, ModularRing32 rhs) {
    return lhs.r >= rhs.r;
  }

  friend std::istream &operator>>(std::istream &is, ModularRing32 &x) {
    int64_t y;
    is >> y;
    x = ModularRing32{y};
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, ModularRing32 x) {
    return os << x.r;
  }

private:
  static constexpr int64_t calcInverse(int64_t a);
};

template <typename ModProvider>
constexpr int64_t ModularRing32<ModProvider>::calcInverse(int64_t x) {
  int64_t a{x}, b{mod()};
  int64_t ua{1}; // ua * x + va * mod() = a
  int64_t ub{0}; // ub * x + vb * mod() = b
  while (a > 0) {
    int64_t t{b / a};
    ub -= t * ua;
    b -= t * a;
    std::swap(ua, ub);
    std::swap(a, b);
  }
  return ub;
}

template <int32_t M>
using ModInt32 = ModularRing32<std::integral_constant<int32_t, M>>;

struct VariableModProvider {
  static inline int32_t value{1};
};
using VariableModInt32 = ModularRing32<VariableModProvider>;

} // namespace u63
