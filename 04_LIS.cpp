#pragma region header
#include <bits/stdc++.h>

#include <atcoder/all>
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

// 座標圧縮ライブラリ窃盗
// https://ei1333.github.io/luzhiled/snippets/other/compress.html
template <typename T>
struct Compress {
  vector<T> xs;
  Compress() = default;
  Compress(const vector<T>& vec) { add(vec); }
  Compress(const initializer_list<vector<T>>& vec) {
    for (auto& p : vec) add(p);
  }

  void add(const vector<T>& vec) {
    copy(begin(vec), end(vec), back_inserter(xs));
  }
  void add(const T& x) { xs.emplace_back(x); }

  void build() {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
  }

  vector<int> get(const vector<T>& vec) const {
    vector<int> ret;
    transform(begin(vec), end(vec), back_inserter(ret), [&](const T& x) {
      return lower_bound(begin(xs), end(xs), x) - begin(xs);
    });
    return ret;
  }

  int get(const T& x) const {
    return (int)(lower_bound(begin(xs), end(xs), x) - begin(xs));
  }
  // inverted
  const T& operator[](int k) const { return xs[k]; }
};

// Θ(NM)のLIS
// https://atcoder.jp/contests/joisc2007/tasks/joisc2007_buildi
// https://atcoder.jp/contests/joisc2007/submissions/66236788
int solve_building(int N, vector<int> A) {
  const int M = 10000;

  // dp[i] := 高さiを採用した時の最大本数
  vector<int> dp(M + 1);

  for (auto v : A) {
    for (int i = 0; i < v; i++) {
      chmax(dp[v], dp[i] + 1);
    }
  }
  int ans = 0;
  for (auto v : dp) chmax(ans, v);
  return ans;
}

// Θ(N^2)のLIS
// https://atcoder.jp/contests/joisc2007/submissions/66236822
int solve_building_2(int N, vector<int> A) {
  const int INF = 1e9;

  // dp[i] := i本採用した時の最小高さ
  vector<int> dp(N + 1, INF);
  dp[0] = -1;

  for (auto v : A) {
    for (int i = 0; i <= N; i++) {
      if (dp[i] == v) break;
      if (dp[i] > v) {
        dp[i] = v;
        break;
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    if (dp[i] == INF) break;
    ans = i;
  }
  return ans;
}

// O(N log NのLIS)
// https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D
int solve_lis(int N, vector<int>& A) {
  // dp[i] := i本採用した時の最小高さ
  const int INF = 1e9;
  vector<int> dp(N + 1, INF);
  dp[0] = -1;

  for (auto v : A) {
    auto it = lower_bound(all(dp), v);
    *it = v;
  }
  debug(dp);
  int ans = 0;
  for (int i = 1; i <= N; i++) {
    if (dp[i] == INF) break;
    ans = i;
  }
  return ans;
}

// O(N log NのLIS)
// https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D
// 座圧セグ木でLIS

int solve_lis_2(int N, vector<int> A) {
  // 座圧
  Compress c(A);
  c.build();

  // 二項演算S op(S a, S b)
  auto op = [](int a, int b) -> int { return max(a, b); };
  // 単位元 S e()
  auto e = []() -> int { return 0; };
  // dp[i] := 高さiを採用した時の最大本数
  atcoder::segtree<int, op, e> dp(N + 1);  // A(N, e)で初期化

  for (auto v : A) {
    int mx = dp.prod(0, c.get(v) + 1) + 1;
    chmax(mx, dp.get(c.get(v) + 1));
    dp.set(c.get(v) + 1, mx);
  }
  int ans = dp.all_prod();
  return ans;
}

int main() {
  int N;
  cin >> N;
  vector<int> A(N);
  rep(i, N) cin >> A[i];
  int ans = solve_lis_2(N, A);
  cout << ans << endl;
  return 0;
}