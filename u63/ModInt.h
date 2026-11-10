#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <type_traits>

namespace u63 {

template <typename ModProvider>
struct BasicModInt {
  int32_t r{0};

  static_assert(std::is_same_v<std::decay_t<decltype(ModProvider::value)>, int32_t>);
  static constexpr int32_t mod() { return ModProvider::value; }

  constexpr BasicModInt() : r{0} {}
  /*implicit*/ constexpr BasicModInt(int64_t value) {
    if (value <= -mod() || value >= mod()) value %= mod();
    if (value < 0) value += mod();
    r = value;
  }
  static constexpr BasicModInt unsafe(int32_t value) {
    BasicModInt result;
    result.r = value;
    return result;
  }

  template <typename T>
  explicit constexpr operator T() {
    return static_cast<T>(r);
  }

  constexpr BasicModInt &operator+=(BasicModInt other) {
    r += other.r;
    if (r >= mod()) r -= mod();
    return *this;
  }
  constexpr friend BasicModInt operator+(BasicModInt lhs, BasicModInt rhs) { return lhs += rhs; }
  constexpr BasicModInt operator+() const { return *this; }
  constexpr BasicModInt &operator++() const { return *this += 1; }
  constexpr BasicModInt operator++(int) {
    BasicModInt copy{*this};
    *this += 1;
    return copy;
  }

  constexpr BasicModInt &operator-=(BasicModInt other) {
    r -= other.r;
    if (r < 0) r += mod();
    return *this;
  }
  constexpr friend BasicModInt operator-(BasicModInt lhs, BasicModInt rhs) { return lhs -= rhs; }
  constexpr BasicModInt operator-() const {
    BasicModInt neg{*this};
    if (neg.r > 0) neg.r = mod() - neg.r;
    return neg;
  }
  constexpr BasicModInt &operator--() const { return *this -= 1; }
  constexpr BasicModInt operator--(int) {
    BasicModInt copy{*this};
    *this -= 1;
    return copy;
  }

  constexpr BasicModInt &operator*=(BasicModInt other) {
    r = static_cast<int64_t>(r) * other.r % mod();
    return *this;
  }
  constexpr friend BasicModInt operator*(BasicModInt lhs, BasicModInt rhs) { return lhs *= rhs; }

  constexpr friend BasicModInt bpow(BasicModInt a, int64_t k) {
    BasicModInt result{1};
    for (BasicModInt base{a}; k > 0; k /= 2, base *= base) {
      if (k & 1) {
        result *= base;
      }
    }
    return result;
  }

  constexpr friend BasicModInt inv(BasicModInt a) { return BasicModInt{calc_inverse(a.r)}; }

  constexpr BasicModInt &operator/=(BasicModInt other) { return *this *= inv(other); }
  constexpr friend BasicModInt operator/(BasicModInt lhs, BasicModInt rhs) { return lhs /= rhs; }

  constexpr friend bool operator==(BasicModInt lhs, BasicModInt rhs) { return lhs.r == rhs.r; }
  constexpr friend bool operator!=(BasicModInt lhs, BasicModInt rhs) { return lhs.r != rhs.r; }
  constexpr friend bool operator<(BasicModInt lhs, BasicModInt rhs) { return lhs.r < rhs.r; }
  constexpr friend bool operator<=(BasicModInt lhs, BasicModInt rhs) { return lhs.r <= rhs.r; }
  constexpr friend bool operator>(BasicModInt lhs, BasicModInt rhs) { return lhs.r > rhs.r; }
  constexpr friend bool operator>=(BasicModInt lhs, BasicModInt rhs) { return lhs.r >= rhs.r; }

  friend std::istream &operator>>(std::istream &is, BasicModInt &x) {
    int64_t y;
    is >> y;
    x = BasicModInt{y};
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, BasicModInt x) { return os << x.r; }

private:
  static constexpr int64_t calc_inverse(int64_t a);
};

template <typename ModProvider>
constexpr int64_t BasicModInt<ModProvider>::calc_inverse(int64_t x) {
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
using ModInt = BasicModInt<std::integral_constant<int32_t, M>>;

struct VariableModProvider {
  static inline int32_t value{1};
};
using VariableModInt = BasicModInt<VariableModProvider>;

} // namespace u63
