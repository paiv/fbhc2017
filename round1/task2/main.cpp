#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_set>
#include <vector>
#include <paiv/hash_tuple.hpp>
using namespace std;
typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;


int
main(int argc, char* argv[]) {

  u32 ntests; cin >> ntests;
  for (u32 test = 0; test < ntests; test++) {
    u32 nzombies, destR; cin >> nzombies >> destR;

    vector<s32> xx(nzombies);
    vector<s32> yy(nzombies);

    for (u32 ni = 0; ni < nzombies; ni++) {
      u32 x, y; cin >> x >> y;
      xx[ni] = x;
      yy[ni] = y;
    }

    vector<tuple<s32,s32>> rects;

    for (u32 i = 0; i < nzombies; i++) {
      s32 x = xx[i];
      s32 y = yy[i];
      rects.emplace_back(x, y);
      rects.emplace_back(x - destR, y);
      rects.emplace_back(x, y - destR);
      rects.emplace_back(x - destR, y - destR);

      for (u32 j = i + 1; j < nzombies; j++) {
        s32 u = xx[j];
        s32 v = yy[j];
        if (x != u && y != v && abs(u - x) <= destR && abs(v - y) <= destR) {
          rects.emplace_back(min(x,u), min(y,v));
          rects.emplace_back(max(x,u) - destR, max(y,v) - destR);
        }
      }
    }

    // clog << rects.size() << endl;

    typedef unordered_set<tuple<s32,s32>> group_t;
    vector<group_t> groups(rects.size());

    for (u32 g = 0; g < rects.size(); g++) {
      auto& rect = rects[g];
      for (u32 i = 0; i < nzombies; i++) {
        s32 x = xx[i];
        s32 y = yy[i];
        if (x >= get<0>(rect) && x <= get<0>(rect) + destR &&
          y >= get<1>(rect) && y <= get<1>(rect) + destR) {

            groups[g].emplace(x, y);
        }
      }
    }

    sort(begin(groups), end(groups), [](group_t& a, group_t& b){ return a.size() > b.size(); });

    u64 best = 0;
    for (u32 i = 0; i < groups.size(); i++) {
      for (u32 j = i + 1; j < groups.size(); j++) {
        auto t = groups[i];
        auto& q = groups[j];
        t.insert(begin(q), end(q));
        best = max(best, u64(t.size()));
      }
    }

    u64 sol = best;

    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
