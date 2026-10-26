#include <bits/stdc++.h>

using ll = long long;
#define int long long
#define all(a) (a).begin(), (a).end()
#define rep(i, n) for (int i = 0; i < (n); ++i)

void debug_out() { std::cerr << std::endl; }
template <typename Arg, typename... Args>
void debug_out(Arg &&arg, Args &&...args) {
  std::cerr << " " << arg, debug_out(std::forward<Args>(args)...);
}
#ifdef U63
#define DEBUG(...) std::cerr << "[" #__VA_ARGS__ "]:", debug_out(__VA_ARGS__)
#else
#define DEBUG(...) 1337
#endif

template <typename L, typename R>
bool chkmin(L &l, const R &r) {
  return r < l ? l = r, true : false;
}
template <typename L, typename R>
bool chkmax(L &l, const R &r) {
  return r > l ? l = r, true : false;
}

using namespace std;
namespace u63 {}
using namespace u63;

void run() {}

int32_t main() {
  ios::sync_with_stdio(false), cin.tie(nullptr);

  int tests = 1;
  cin >> tests;
  for (int testNo = 1; testNo <= tests; ++testNo) {
    run();
  }
}
