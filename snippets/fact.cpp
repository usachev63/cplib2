
mint fact[MaxN], ifact[MaxN];

int precalc_fact() {
  fact[0] = 1;
  for (int i = 1; i < MaxN; ++i) fact[i] = fact[i - 1] * i;
  ifact[MaxN - 1] = inv(fact[MaxN - 1]);
  for (int i = MaxN - 2; i >= 0; --i) ifact[i] = ifact[i + 1] * (i + 1);
  return 0;
}
int _precalc_fact = precalc_fact();

mint choose(int n, int k) {
  if (n < 0 || k < 0 || k > n) return 0;
  return fact[n] * ifact[k] * ifact[n - k];
}
