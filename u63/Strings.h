#include <span>
#include <string>
#include <vector>

namespace u63 {

template <typename S>
std::vector<int> prefix_function(S &&s) {
  int n = std::ssize(s);
  std::vector<int> pi(n);
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      ++j;
    pi[i] = j;
  }
  return pi;
}

template <int A, int A0, typename S>
std::vector<std::array<int, A>> kmp_automaton(S &&s, std::span<const int> pi) {
  int m = ssize(s);
  std::vector<std::array<int, A>> aut(m + 1);
  for (int j = 0; j <= m; ++j) {
    for (int c = 0; c < A; ++c) {
      if (j > 0 && (j == m || c != s[j] - A0))
        aut[j][c] = aut[pi[j - 1]][c];
      else
        aut[j][c] = j + (c == s[j] - A0);
    }
  }
  return aut;
}

template <int A, int A0, typename S>
std::vector<std::array<int, A>> kmp_automaton(S &&s) {
  std::vector<int> pi = prefix_function(s);
  return kmp_automaton<A, A0, S>(s, pi);
}

template <typename S>
std::vector<int> z_function(S &&s) {
  int n = std::ssize(s);
  std::vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i < r)
      z[i] = std::min(r - i, z[i - l]);
    while (i + z[i] < n && s[i + z[i]] == s[z[i]])
      ++z[i];
    if (i + z[i] > r)
      l = i, r = i + z[i];
  }
  return z;
}

} // namespace u63
