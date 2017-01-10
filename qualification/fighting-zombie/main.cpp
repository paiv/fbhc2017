#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef uint8_t u8;
typedef uint32_t u32;
typedef int32_t s32;
typedef double_t r64;


#if 1
vector<r64>
distribution(u32 x, u32 y) {
  vector<r64> res(x * y);
  if (x == 0) return res;

  r64 r = 1.0 / y;
  for (u32 k = 0; k < y; k++)
    res[k] = r;

  vector<r64> t(res.size());

  for (u32 i = 1; i < x; i++) {
    fill(begin(t), end(t), 0);
    res.swap(t);
    for (u32 j = 0; j <= i * y; j++)
      for (u32 k = 0; k < y; k++) {
        res[j + k] += t[j] * r;
      }
  }

  rotate(res.rbegin(), res.rbegin() + x - 1, res.rend());
  return res;
}

r64
probs(s32 dmg, u32 x, u32 y) {
  auto p = distribution(x, y);
  r64 res = 0;
  for (u32 i = max(0, dmg - 1); i < p.size(); i++)
    res += p[i];
  return res;
}

#else
#include <tuple>
#include <unordered_map>
#include <paiv/hash_tuple.hpp>

typedef unordered_map<tuple<s32, u32>, r64> memo_t;

r64
probs(s32 dmg, u32 x, u32 y, memo_t& memo) {
  if (dmg <= 0) return 1;
  if (x == 0 || x * y < dmg)
    return 0;

  auto t = make_tuple(dmg, x);
  auto it = memo.find(t);
  if (it != end(memo)) return it->second;

  r64 res = 0;
  for (u32 i = 1; i <= y; i++) {
    res += probs(dmg - i, x - 1, y, memo);
  }

  res /= y;

  memo[t] = res;

  return res;
}

r64
probs(s32 dmg, u32 x, u32 y) {
  memo_t memo;
  return probs(dmg, x, y, memo);
}
#endif


int
main(int argc, char* argv[]) {

  u32 n; cin >> n;
  for (u32 t = 0; t < n; t++) {

    u32 hp; cin >> hp;
    u32 spells; cin >> spells;

    r64 best = 0;

    for (u32 i = 0; i < spells; i++) {
      u32 x; cin >> x;
      char d; cin >> d;
      u32 y; cin >> y;
      s32 z = 0;

      d = cin.peek();
      if (d == '-' || d == '+')
        cin >> z;

      best = max(best, probs(hp - z, x, y));
    }

    cout << "Case #" << (t + 1) << ": " << fixed << setprecision(6) << best << endl;
  }

  return 0;
}
