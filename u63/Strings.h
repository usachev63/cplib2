#include <string>
#include <vector>

template <typename S>
std::vector<int> prefixFunction(S &&s) {
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
