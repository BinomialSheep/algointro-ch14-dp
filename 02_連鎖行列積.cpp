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

const ll INF = 8e18;

/**
 * verified
 * https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_10_B&lang=jp
 * https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=10527392#1
 */

ll solve(int N, vector<pair<int, int>> M) {
  // (p, q)型行列を(q, r)型行列を乗算すると、
  // 乗算コストはpqr回であり、乗算後の型は(p, r)
  // dp[i][j] := [i, j]を計算した時の最小コスト
  vector dp(N, vector(N, INF));
  rep(i, N) dp[i][i] = 0;
  rep(i, N - 1) dp[i][i + 1] = M[i].first * M[i].second * M[i + 1].second;

  for (int len = 2; len < N; len++) {
    for (int i = 0;; i++) {
      int j = i + len;
      if (j >= N) break;
      for (int k = i; k < j; k++) {
        // 区間[i, k]と区間[k, j)を計算してから、それらを掛け算する場合
        ll cost =
            dp[i][k] + dp[k + 1][j] + M[i].first * M[k].second * M[j].second;
        dp[i][j] = min(dp[i][j], cost);
      }
      // debug(i, j, dp[i][j]);
    }
  }
  //   debug(dp);

  return dp[0][N - 1];
}

void test_1() {
  int N = 3;
  vector<pair<int, int>> M(N);
  M = {
      {10, 100},
      {100, 5},
      {5, 50},
  };
  ll res = solve(N, M);
  assert(res == 7500);
}
void test_2() {
  int N = 6;
  vector<pair<int, int>> M(N);
  M = {
      {30, 35}, {35, 15}, {15, 5}, {5, 10}, {10, 20}, {20, 25},
  };
  ll res = solve(N, M);
  assert(res == 15125);
}
void test_3() {
  // 練習問題14.2-1
  int N = 6;
  vector<pair<int, int>> M(N);
  M = {
      {5, 10}, {10, 3}, {3, 12}, {12, 5}, {5, 50}, {50, 6},
  };
  ll res = solve(N, M);
  assert(res == 2010);
}

int main() {
  //   test_1();
  //   test_2();
  //   test_3();
  //   return 0;

  int N;
  cin >> N;
  vector<pair<int, int>> M(N);
  rep(i, N) cin >> M[i].first >> M[i].second;

  ll ans = solve(N, M);
  cout << ans << endl;
}