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
template <typename T>
inline bool chmax(T& a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T& a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

// Θ(N^3)。50点解法
// https://atcoder.jp/contests/atc002/submissions/66237005
ll solve(int N, vector<int>& W) {
  const ll INF = 1e18;
  // dp[i][j] := 区間[i, j]における最小コスト
  vector dp(N, vector(N, INF));
  rep(i, N) dp[i][i] = 0;
  rep(i, N - 1) dp[i][i + 1] = W[i] + W[i + 1];

  for (int k = 2; k < N; k++) {
    for (int left = 0; left < N; left++) {
      int right = left + k;
      if (right >= N) break;
      for (int mid = left; mid < right; mid++) {
        ll cost = dp[left][mid] + dp[mid + 1][right];
        for (int i = left; i <= right; i++) cost += W[i];
        chmin(dp[left][right], cost);
      }
    }
  }
  return dp[0][N - 1];
}

// https://atcoder.jp/contests/atc002/tasks/atc002_c?lang=ja
int main() {
  int N;
  cin >> N;
  vector<int> W(N);
  rep(i, N) cin >> W[i];
  cout << solve(N, W) << endl;
  return 0;
}