#pragma region header
#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

// フィボナッチ数をO(n)で求める問題
ll calc_fib(int n) {
  vector<ll> dp(n + 2);
  dp[1] = dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

void test_sample() {
  for (int i = 1; i <= 92; i++) {
    cout << i << " " << calc_fib(i) << endl;
  }
}

int main() { test_sample(); }