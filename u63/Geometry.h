#pragma once

#include <cmath>
#include <iostream>
#include <type_traits>
#include <variant>
#include <vector>

namespace u63 {

template <typename T>
constexpr int sgn(T x) {
  if (x > 0)
    return +1;
  if (x < 0)
    return -1;
  return 0;
}

template <typename T>
  requires std::is_arithmetic_v<T> && std::is_signed_v<T>
struct Vector2 {
  T x{};
  T y{};

  constexpr Vector2() = default;
  constexpr Vector2(T x, T y) : x{x}, y{y} {}
  template <typename U>
  constexpr Vector2(const Vector2<U> &other)
      : x{static_cast<T>(other.x)}, y{static_cast<T>(other.y)} {}
  constexpr Vector2(Vector2<T> A, Vector2<T> B) : x{B.x - A.x}, y{B.y - A.y} {}
};

template <typename T>
using Point2 = Vector2<T>;

template <typename T>
constexpr auto tie(const Vector2<T> &v) {
  return std::tie(v.x, v.y);
}

template <typename T>
constexpr bool operator==(Vector2<T> u, Vector2<T> v) {
  return tie(u) == tie(v);
}
template <typename T>
constexpr bool operator!=(Vector2<T> u, Vector2<T> v) {
  return !(u == v);
}

template <typename T>
constexpr bool operator<(Vector2<T> u, Vector2<T> v) {
  return tie(u) < tie(v);
}
template <typename T>
constexpr bool operator<=(Vector2<T> u, Vector2<T> v) {
  return tie(u) <= tie(v);
}
template <typename T>
constexpr bool operator>(Vector2<T> u, Vector2<T> v) {
  return tie(u) > tie(v);
}
template <typename T>
constexpr bool operator>=(Vector2<T> u, Vector2<T> v) {
  return tie(u) >= tie(v);
}

template <typename T>
constexpr Vector2<T> &operator+=(Vector2<T> &u, Vector2<T> v) {
  u.x += v.x, u.y += v.y;
  return u;
}
template <typename T>
constexpr Vector2<T> operator+(Vector2<T> u, Vector2<T> v) {
  return {u.x + v.x, u.y + v.y};
}
template <typename T>
constexpr Vector2<T> operator+(Vector2<T> v) {
  return v;
}
template <typename T>
constexpr Vector2<T> &operator-=(Vector2<T> &u, Vector2<T> v) {
  u.x -= v.x, u.y -= v.y;
  return u;
}
template <typename T>
constexpr Vector2<T> operator-(Vector2<T> u, Vector2<T> v) {
  return {u.x - v.x, u.y - v.y};
}
template <typename T>
constexpr Vector2<T> operator-(Vector2<T> v) {
  return {-v.x, -v.y};
}
template <typename T>
constexpr Vector2<T> &operator*=(Vector2<T> &v, T k) {
  v.x *= k, v.y *= k;
  return v;
}
template <typename T>
constexpr Vector2<T> operator*(Vector2<T> v, T k) {
  return {v.x * k, v.y * k};
}
template <typename T>
constexpr Vector2<T> operator*(T k, Vector2<T> v) {
  return v * k;
}

template <typename T>
constexpr T dot(Vector2<T> u, Vector2<T> v) {
  return u.x * v.x + u.y * v.y;
}
template <typename T>
constexpr T operator*(Vector2<T> u, Vector2<T> v) {
  return dot(u, v);
}

template <typename T>
constexpr T cross(Vector2<T> u, Vector2<T> v) {
  return u.x * v.y - u.y * v.x;
}

template <typename T>
std::istream &operator>>(std::istream &is, Vector2<T> &v) {
  return is >> v.x >> v.y;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, Vector2<T> v) {
  return os << v.x << " " << v.y;
}

template <typename T>
constexpr T len2(Vector2<T> v) {
  return v.x * v.x + v.y * v.y;
}
template <typename T>
constexpr T dist2(Point2<T> A, Point2<T> B) {
  return len2(B - A);
}

template <typename T>
constexpr double len(Vector2<T> v) {
  return std::sqrt(len2(v));
}
template <typename T>
constexpr double dist(Point2<T> A, Point2<T> B) {
  return std::sqrt(dist2(A, B));
}

/// \pre v != 0
template <typename T>
constexpr Vector2<double> normalize(Vector2<T> v) {
  double L = len(v);
  return {v.x / L, v.y / L};
}

constexpr bool parallel(Vector2<long long> u, Vector2<long long> v) {
  return cross(u, v) == 0;
}

template <typename T>
constexpr Vector2<T> rotatePlus90(Vector2<T> v) {
  return {-v.y, v.x};
}
template <typename T>
constexpr Vector2<T> rotateMinus90(Vector2<T> v) {
  return {v.y, -v.x};
}

/// In range [-pi, pi]
template <typename T>
constexpr double angle(Vector2<T> v) {
  return std::atan2(v.y, v.x);
}

/// In range [-pi, pi]
template <typename T>
constexpr double angle(Vector2<T> u, Vector2<T> v) {
  return std::atan2(cross(u, v), dot(u, v));
}

/// In range [-pi, pi]
template <typename T>
constexpr double angle(Point2<T> O, Point2<T> A, Point2<T> B) {
  return angle(Vector2<T>{O, A}, Vector2<T>{O, B});
}

/// Ax + By = C
template <typename T>
struct Line2 {
  T A{};
  T B{};
  T C{};

  constexpr Line2() = default;
  /// \pre A != 0 || B != 0
  constexpr Line2(T A, T B, T C) : A{A}, B{B}, C{C} {}
  /// Line through two points
  /// \pre P != Q
  constexpr Line2(Point2<T> P, Point2<T> Q)
      : A{-(Q.y - P.y)}, B{Q.x - P.x}, C{A * P.x + B * P.y} {}

  constexpr T operator()(Point2<T> p) const { return A * p.x + B * p.y - C; }

  constexpr Vector2<T> normal() const { return {A, B}; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, Line2<T> line) {
  return os << line.A << " " << line.B << " " << line.C << "\n";
}

template <typename T>
constexpr Line2<double> normalize(Line2<T> line) {
  double L = len(line.normal());
  return {line.A / L, line.B / L, line.C / L};
}

constexpr bool parallel(Line2<long long> l1, Line2<long long> l2) {
  return parallel(l1.normal(), l2.normal());
}

constexpr bool contains(Line2<long long> l, Point2<long long> P) {
  return l(P) == 0;
}

constexpr std::optional<Point2<double>> intersect(Line2<long long> l1,
                                                  Line2<long long> l2) {
  auto det = l1.A * l2.B - l1.B * l2.A;
  if (det == 0)
    return std::nullopt;
  auto det_x = l1.C * l2.B - l1.B * l2.C;
  auto det_y = l1.A * l2.C - l1.C * l2.A;
  return {{det_x / static_cast<double>(det), det_y / static_cast<double>(det)}};
}

constexpr double dist(Line2<long long> l, Point2<long long> P) {
  return std::abs(l(P) / len(l.normal()));
}

constexpr double dist(Line2<long long> l1, Line2<long long> l2) {
  if (!parallel(l1, l2))
    return 0.0;
  Line2 n1 = normalize(l1);
  Line2 n2 = normalize(l2);
  double c1 = n1.C;
  double c2 = dot(n1.normal(), n2.normal()) > 0 ? n2.C : -n2.C;
  return std::abs(c1 - c2);
}

template <typename T>
struct TwoPointsLine2 {
  Point2<T> A{};
  Point2<T> B{};

  constexpr TwoPointsLine2() = default;
  constexpr TwoPointsLine2(Point2<T> A, Point2<T> B) : A{A}, B{B} {}
  template <typename U>
  constexpr TwoPointsLine2(TwoPointsLine2<U> other)
      : A{static_cast<T>(other.A)}, B{static_cast<T>(other.B)} {}
};

constexpr bool degenerate(TwoPointsLine2<long long> l) { return l.A == l.B; }

constexpr bool parallel(TwoPointsLine2<long long> l1,
                        TwoPointsLine2<long long> l2) {
  return parallel(Vector2{l1.A, l1.B}, Vector2{l2.A, l2.B});
}

/// \pre l is not degenerate
constexpr bool contains(TwoPointsLine2<long long> l, Point2<long long> P) {
  Vector2 AB{l.A, l.B}, AP{l.A, P};
  return cross(AB, AP) == 0;
}

/// \pre l is not degenerate
template <typename T>
constexpr double dist(TwoPointsLine2<T> l, Point2<T> P) {
  Vector2 AB{l.A, l.B}, AP{l.A, P};
  return std::abs(cross(AB, AP)) / len(AB);
}

template <typename T>
struct HalfLine2 {
  Point2<T> A{};
  Point2<T> B{};

  constexpr HalfLine2() = default;
  constexpr HalfLine2(Point2<T> A, Point2<T> B) : A{A}, B{B} {}
  template <typename U>
  constexpr HalfLine2(HalfLine2<U> other)
      : A{static_cast<T>(other.A)}, B{static_cast<T>(other.B)} {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const HalfLine2<T> &r) {
  return os << r.A << " " << r.B << "\n";
}

constexpr bool degenerate(HalfLine2<long long> r) { return r.A == r.B; }

constexpr bool parallel(HalfLine2<long long> r1, HalfLine2<long long> r2) {
  return parallel(Vector2{r1.A, r1.B}, Vector2{r2.A, r2.B});
}

/// \pre r is not degenerate
constexpr bool contains(HalfLine2<long long> r, Point2<long long> P) {
  Vector2 AB{r.A, r.B}, AP{r.A, P};
  return cross(AB, AP) == 0 && dot(AB, AP) >= 0;
}

/// \pre r is not degenerate
template <typename T>
constexpr double dist(HalfLine2<T> r, Point2<T> P) {
  Vector2 AB{r.A, r.B}, AP{r.A, P};
  if (dot(AB, AP) >= 0) // continuous
    return dist(TwoPointsLine2{r.A, r.B}, P);
  else
    return dist(r.A, P);
}

template <typename T>
struct LineSegment2 {
  Point2<T> A{};
  Point2<T> B{};

  constexpr LineSegment2() = default;
  constexpr LineSegment2(Point2<T> A, Point2<T> B) : A{A}, B{B} {}
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const LineSegment2<T> &f) {
  return os << f.A << " " << f.B << "\n";
}

template <typename T>
constexpr bool degenerate(LineSegment2<T> f) {
  return f.A == f.B;
}

constexpr bool parallel(LineSegment2<long long> f, LineSegment2<long long> g) {
  return parallel(Vector2{f.A, f.B}, Vector2{g.A, g.B});
}

/// \pre f is not degenerate
constexpr bool contains(LineSegment2<long long> f, Point2<long long> P) {
  Vector2 AB{f.A, f.B};
  Vector2 AP{f.A, P};
  Vector2 BA{f.B, f.A};
  Vector2 BP{f.B, P};
  return cross(AB, AP) == 0 && dot(AB, AP) >= 0 && dot(BA, BP) >= 0;
}

constexpr bool contains1(LineSegment2<long long> f, Point2<long long> P) {
  if (degenerate(f))
    return f.A == P;
  return contains(f, P);
}

/// \pre f, g are not degenerate
constexpr bool checkIntersect(LineSegment2<long long> f,
                              LineSegment2<long long> g) {
  if (contains(f, g.A) || contains(f, g.B) || contains(g, f.A) ||
      contains(g, f.B)) {
    return true;
  }
  auto [A, B] = f;
  auto [C, D] = g;
  Vector2 AB{A, B}, AC{A, C}, AD{A, D};
  if (sgn(cross(AB, AC)) * sgn(cross(AB, AD)) != -1)
    return false;
  Vector2 CD{C, D}, CA{C, A}, CB{C, B};
  if (sgn(cross(CD, CA)) * sgn(cross(CD, CB)) != -1)
    return false;
  return true;
}

constexpr bool checkIntersect1(LineSegment2<long long> f,
                               LineSegment2<long long> g) {
  if (degenerate(f))
    return contains1(g, f.A);
  if (degenerate(g))
    return contains1(f, g.A);
  return checkIntersect(f, g);
}

std::variant<
    std::monostate, Point2<double>,
    LineSegment2<long long>> constexpr intersect1(LineSegment2<long long> f,
                                                  LineSegment2<long long> g) {
  if (!checkIntersect1(f, g))
    return {};
  if (degenerate(f))
    return f.A;
  if (degenerate(g))
    return g.A;
  if (!parallel(f, g))
    return *intersect(Line2{f.A, f.B}, Line2{g.A, g.B});

  Point2 A{f.A}, B{f.B}, C{g.A}, D{g.B};
  Vector2 AB{A, B}, CD{C, D};
  constexpr long long tA = 0;
  auto tB = dot(AB, AB);
  auto tC = dot(AB, Vector2{A, C});
  auto tD = dot(AB, Vector2{A, D});
  if (tC > tD) {
    std::swap(C, D);
    std::swap(tC, tD);
  }

  if (tB == tC)
    return B;
  if (tD == tA)
    return A;

  return LineSegment2{
      tC <= tA ? A : C,
      tD >= tB ? B : D,
  };
}

template <typename T>
constexpr double dist(LineSegment2<T> f, Point2<T> P) {
  Vector2 AB{f.A, f.B}, AP{f.A, P}, BA{f.B, f.A}, BP{f.B, P};
  if (dot(AB, AP) <= 0) // continuous
    return dist(f.A, P);
  if (dot(BA, BP) <= 0) // continuous
    return dist(f.B, P);
  return dist(TwoPointsLine2{f.A, f.B}, P);
}

template <typename T>
constexpr double dist(LineSegment2<T> f, LineSegment2<T> g) {
  if (checkIntersect1(f, g))
    return 0.0;
  return std::min({dist(f, g.A), dist(f, g.B), dist(g, f.A), dist(g, f.B)});
}

template <typename T>
std::vector<Point2<T>> convexHullGraham(std::vector<Point2<T>> points) {
  int n = std::ssize(points);
  if (n == 0)
    return {};
  if (n == 1)
    return {points[0], points[0]};

  for (int i = 1; i < n; ++i)
    if (points[i] < points[0]) // lexicographical
      std::swap(points[0], points[i]);
  std::sort(
      points.begin() + 1, points.end(), [&points](Point2<T> p1, Point2<T> p2) {
        Vector2 v1{points[0], p1}, v2{points[0], p2};
        return cross(v1, v2) > 0 || (cross(v1, v2) == 0 && len2(v1) < len2(v2));
      });
  points.push_back(points[0]);
  std::vector<Point2<T>> hull;
  for (int i = 0; i < std::ssize(points); ++i) {
    while (std::ssize(hull) >= 2 &&
           cross(Vector2{hull.end()[-2], hull.end()[-1]},
                 Vector2{hull.end()[-2], points[i]}) <= 0) {
      Vector2 u{hull.end()[-2], hull.end()[-1]};
      Vector2 v{hull.end()[-1], points[i]};
      if (cross(u, v) > 0 || (cross(u, v) == 0 && dot(u, v) < 0))
        break;
      hull.pop_back();
    }
    hull.push_back(points[i]);
  }
  return hull;
}

template <typename T>
std::vector<Point2<T>> convexHullAndrew(std::vector<Point2<T>> points) {
  if (points.empty())
    return {};
  std::sort(points.begin(), points.end());
  points.erase(std::unique(points.begin(), points.end()), points.end());
  std::vector<Point2<T>> hull;
  for (int rot = 0; rot < 2; ++rot) {
    int sz0 = std::ssize(hull) - rot;
    for (auto A : points) {
      while (std::ssize(hull) - sz0 >= 2 &&
             cross(Vector2{hull.end()[-2], hull.end()[-1]},
                   Vector2{hull.end()[-1], A}) <= 0) {
        hull.pop_back();
      }
      hull.push_back(A);
    }
    std::reverse(points.begin(), points.end());
  }
  return hull;
}

} // namespace u63
