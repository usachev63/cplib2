#include <bits/stdc++.h>

#define all(a) (a).begin(), (a).end()
#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;

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
