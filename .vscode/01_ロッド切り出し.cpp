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

// メモ化なし再帰
int cut_rod(vector<int>& prices, int n) {
  if (n == 0) return 0;
  int ret = 0;
  for (int i = 1; i <= min(n, (int)prices.size()); i++) {
    ret = max(ret, prices[i] + cut_rod(prices, n - i));
  }
  return ret;
}

// トップダウン型動的計画法（メモ化再帰）
unordered_map<int, int> memo;
int memoized_cut_rod(vector<int>& prices, int n) {
  if (n == 0) return 0;
  if (memo.count(n)) return memo[n];
  int ret = 0;
  for (int i = 1; i <= min(n, (int)prices.size()); i++) {
    ret = max(ret, prices[i] + memoized_cut_rod(prices, n - i));
  }
  return memo[n] = ret;
}

// ボトムアップ型動的計画法
int bottom_up_cut_rod(vector<int>& prices, int n) {
  vector<int> dp(n + 1);
  for (int i = 1; i <= n; i++) {
    dp[i] = prices[i];
    for (int j = 0; j < i; j++) {
      dp[i] = max(dp[i], dp[j] + dp[i - j]);
    }
  }
  return dp[n];
}

// 復元付き
void print_cut_rod_solution(vector<int>& prices, int n) {
  vector<int> dp(n + 1);
  vector<int> prev(n + 1);
  for (int i = 1; i <= n; i++) {
    dp[i] = prices[i];
    prev[i] = 0;
    for (int j = 1; j < i; j++) {
      if (dp[i] < dp[j] + dp[i - j]) {
        dp[i] = dp[j] + dp[i - j];
        prev[i] = j;
      }
    }
  }
  debug(prev);
  cout << "dp[n]: " << dp[n] << endl << "復元列: ";
  for (int idx = n; idx != 0; idx = prev[idx]) {
    cout << idx - prev[idx] << " ";
  }
  cout << endl;
}
// 復元（prev配列を持たない）
void print_cut_rod_solution_2(vector<int>& prices, int n) {
  vector<int> dp(n + 1);
  for (int i = 1; i <= n; i++) {
    dp[i] = prices[i];
    for (int j = 1; j < i; j++) {
      if (dp[i] < dp[j] + dp[i - j]) {
        dp[i] = dp[j] + dp[i - j];
      }
    }
  }
  cout << "dp[n]: " << dp[n] << endl << "復元列: ";
  int idx = n;
  while (idx != 0) {
    for (int i = idx; i >= 0; i--) {
      if (dp[idx - i] + prices[i] == dp[idx]) {
        cout << i << " ";
        idx -= i;
        break;
      }
    }
  }
  cout << endl;
}

void test_sample() {
  vector<int> prices = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

  for (int i = 1; i < (int)prices.size(); i++) {
    cout << "cut_rod: " << i << " " << cut_rod(prices, i) << endl;
    cout << "memorized: " << i << " " << memoized_cut_rod(prices, i) << endl;
    cout << "bottom_up: " << i << " " << bottom_up_cut_rod(prices, i) << endl;
    print_cut_rod_solution(prices, i);
    print_cut_rod_solution_2(prices, i);
  }
}

int main() { test_sample(); }