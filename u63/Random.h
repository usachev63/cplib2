#include <random>

namespace u63 {

inline std::mt19937_64 rng{std::random_device{}()};

template <typename T>
T rand_int(T m) {
  return rng() % m;
}
template <typename T>
T rand_int(T l, T r) {
  return rand_int(r - l + 1) + l;
}

} // namespace u63
