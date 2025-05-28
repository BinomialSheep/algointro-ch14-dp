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

/**
 * verify
 * EDPC-F：LCS
 * https://atcoder.jp/contests/dp/tasks/dp_f
 */

// 復元用テーブルを持つ
string solve(string s, string t) {
  vector dp(s.size() + 1, vector(t.size() + 1, -1));
  vector direction(s.size() + 1, vector(t.size() + 1, 0));
  rep(i, s.size() + 1) dp[i][0] = 0;
  rep(j, t.size() + 1) dp[0][j] = 0;

  for (int i = 1; i <= (int)s.size(); i++) {
    for (int j = 1; j <= (int)t.size(); j++) {
      if (s[i - 1] == t[j - 1]) {
        if (chmax(dp[i][j], dp[i - 1][j - 1] + 1)) direction[i][j] = 1;
      }
      if (chmax(dp[i][j], dp[i - 1][j])) direction[i][j] = 2;
      if (chmax(dp[i][j], dp[i][j - 1])) direction[i][j] = 3;
    }
  }
  int i = (int)s.size(), j = (int)t.size();
  string ret = "";
  while (i && j) {
    switch (direction[i][j]) {
      case 1:
        ret.push_back(s[i - 1]);
        i--, j--;
        break;
      case 2:
        i--;
        break;
      case 3:
        j--;
        break;
      default:
        assert(false);
        break;
    }
  }
  reverse(all(ret));
  return ret;
}

// 練習問題14.4-1
void test() {
  string s = "10010101";
  string t = "010110110";
  string res = solve(s, t);
  assert(res == "100110");
}

int main() {
  test();
  return 0;
  string s, t;
  cin >> s >> t;
  string ans = solve(s, t);
  cout << ans << endl;
}