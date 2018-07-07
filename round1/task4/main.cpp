#include <iostream>
#include <vector>
using namespace std;
typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;

// https://www.quora.com/How-do-I-find-the-value-of-nCr-1000000007-for-the-large-number-n-n-10-6-in-C

namespace Qr {

template<typename T, typename T1>
T mod(T x, T1 p) {
    x %= p;
    if (x < 0)
        x += p;
    return x;
}

// template<typename T>
// T inverse(T x, T p) {
//     x = mod(x, p);
//     if (x == 1)
//         return x;
//     return mod(1LL * (-p / x) * (inverse(p % x, p)) , p);
// }

const u32 MAXN = 1000001;
const u32 MOD  = 1000000007;

s32 fact[MAXN];
s32 inv[MAXN];
s32 ifact[MAXN];

template<typename T>
T inverse(T x, T p) {
  x = mod(x, p);
  if (x == 1)
    return x;
  return mod((1LL * (-p / x) * (inv[p % x] % p)) , p);
}


void
precompute() {

  fact[0] = 1;
  for (u32 i = 1; i < MAXN; i++) {
    fact[i] = 1LL * fact[i - 1] * i % MOD;
  }

  // ifact[0] = 1;
  // for (u32 i = 1; i < MAXN; i++) {
  //   ifact[i] = 1LL * ifact[i - 1] * inverse(i, MOD) % MOD;
  // }

  ifact[0] = 1;
  for (u32 i = 1; i < MAXN; i++) {
    inv[i] = inverse(i, MOD);
    ifact[i] = ifact[i - 1] * inv[i] % MOD;
  }
}

u32
NcR(u32 n, u32 r) {
  u32 ret = (1LL * ifact[n - r] * ifact[r]) % MOD;
  return (1LL * ret * fact[n]) % MOD;
}

}


int
main(int argc, char* argv[]) {

  Qr::precompute();

  u32 ntests; cin >> ntests;
  for (u32 test = 0; test < ntests; test++) {
    u32 nobjs, mplaces; cin >> nobjs >> mplaces;

    vector<u32> rr;
    rr.reserve(nobjs);
    u32 total_size = 0;

    for (u32 ni = 0; ni < nobjs; ni++) {
      u32 r; cin >> r;
      rr.push_back(r);
      total_size += r;
    }

    u64 sol = 0;

    if (nobjs >= 1 && total_size <= mplaces) {
      u32 mn = Qr::NcR(nobjs, nobjs);
      u32 nx = Qr::NcR(mplaces - total_size + nobjs, nobjs);
      sol = mn * nx;
    }
    else if (nobjs == 1) {
      sol = 1;
    }

    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
