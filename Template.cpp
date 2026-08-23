#ifndef U63
#include <algorithm>
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <ranges>
#include <set>
#include <span>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#else
import std;
import std.compat;
#endif

#include <cassert>

#define all(a) (a).begin(), (a).end()
#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;
using pil = std::pair<int, ll>;
using pli = std::pair<ll, int>;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vpii = std::vector<pii>;
using vpll = std::vector<pll>;
using vvi = std::vector<std::vector<int>>;
using vvl = std::vector<std::vector<ll>>;

template <typename L, typename R>
bool chkmin(L &l, const R &r) {
  return r < l ? l = r, true : false;
}

template <typename L, typename R>
bool chkmax(L &l, const R &r) {
  return r > l ? l = r, true : false;
}

void debug_out() { std::cerr << std::endl; }

template <typename Arg, typename... Args>
void debug_out(Arg &&arg, Args &&...args) {
  std::cerr << " " << arg;
  debug_out(std::forward<Args>(args)...);
}

#ifdef U63
#define DEBUG(...)                                                             \
  do {                                                                         \
    std::cerr << "[" #__VA_ARGS__ "]:";                                        \
    debug_out(__VA_ARGS__);                                                    \
  } while (0);
#else
#define DEBUG(...) ;
#endif

namespace std {

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) {
  return os << p.first << " " << p.second;
}

template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) {
  return is >> p.first >> p.second;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  if (!v.empty()) {
    os << v[0];
    for (int i = 1; i < std::ssize(v); ++i) {
      os << " " << v[i];
    }
  }
  return os;
}

template <typename T>
istream &operator>>(istream &is, vector<T> &v) {
  for (auto &el : v)
    std::cin >> el;
  return is;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &a) {
  if (!a.empty()) {
    os << a[0];
    for (int i = 1; i < N; ++i) {
      os << " " << a[i];
    }
  }
  return os;
}

template <typename T, size_t N>
istream &operator>>(istream &is, array<T, N> &a) {
  for (auto &el : a)
    std::cin >> el;
  return is;
}

template <typename T>
ostream &operator<<(ostream &os, span<T> s) {
  if (!s.empty()) {
    os << s[0];
    for (int i = 1; i < std::ssize(s); ++i) {
      os << " " << s[i];
    }
  }
  return os;
}

} // namespace std

// BEGIN //////////////////////////////////////////////////////////////////////

using namespace std;

void run([[maybe_unused]] int testNo) {}

int32_t main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int tests = 1;
  std::cin >> tests;
  for (int testNo = 1; testNo <= tests; ++testNo) {
    run(testNo);
  }
}
