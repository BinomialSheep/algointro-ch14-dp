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

// ボトムアップ型動的計画法
int bottom_up_cut_rod(vector<int>& prices, int n, int cost) {
  vector<int> dp(n + 1);
  for (int i = 1; i <= n; i++) {
    dp[i] = prices[i];
    for (int j = 1; j < i; j++) {
      dp[i] = max(dp[i], dp[j] + dp[i - j] - cost);
    }
  }
  return dp[n];
}

void test_sample() {
  vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

  for (int i = 1; i < (int)prices.size(); i++) {
    for (int c = 0; c < 3; c++) {
      cout << "bottom_up: " << i << " " << c << " "
           << bottom_up_cut_rod(prices, i, c) << endl;
    }
  }
}

int main() { test_sample(); }