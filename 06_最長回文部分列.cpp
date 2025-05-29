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

string solve(string S) {
  int N = (int)S.size();
  map<pair<int, int>, pair<int, int>> mp;
  vector<vector<int>> dp(N, vector<int>(N));
  rep(i, N) dp[i][i] = 1;
  for (int k = 1; k < N; k++) {
    rep(left, N) {
      int right = left + k;
      if (right >= N) break;
      if (S[left] == S[right]) {
        if (k == 1) {
          // ..aa..
          dp[left][right] = 2;
        } else {
          // a...a
          if (left + 1 < N && right - 1 >= 0 &&
              chmax(dp[left][right], dp[left + 1][right - 1] + 2)) {
            mp[make_pair(left, right)] = make_pair(left + 1, right - 1);
          }
        }
      }
      if (left + 1 < N && chmax(dp[left][right], dp[left + 1][right])) {
        mp[make_pair(left, right)] = make_pair(left + 1, right);
      }
      if (right - 1 >= 0 && chmax(dp[left][right], dp[left][right - 1])) {
        mp[make_pair(left, right)] = make_pair(left, right - 1);
      }
    }
  }

  string ret = "";
  string ret2 = "";
  pair<int, int> p = make_pair(0, N - 1);
  while (true) {
    if (S[p.first] == S[p.second]) {
      ret.push_back(S[p.first]);
      if (p.first != p.second) ret2.push_back(S[p.second]);
    }
    if (mp.count(p)) {
      p = mp[p];
    } else {
      break;
    }
  }
  reverse(all(ret2));
  ret += ret2;
  debug(ret);
  return ret;
}

void test() {
  string S = "character";
  string ans = solve(S);
  assert(ans == "carac");
}

int main() {
  string S;
  cin >> S;
  string ans = solve(S);
  cout << ans << endl;

  return 0;
}