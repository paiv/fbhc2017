#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;


int
main(int argc, char* argv[]) {

  u32 ntests; cin >> ntests;
  for (u32 test = 0; test < ntests; test++) {
    u32 ndays, mpies; cin >> ndays >> mpies;

    vector<vector<u32>> pies;
    vector<vector<u32>> sums;

    for (u32 day = 0; day < ndays; day++) {
      pies.push_back({});

      for (u32 mi = 0; mi < mpies; mi++) {
        u32 price; cin >> price;

        pies[day].push_back(price);
      }
    }

    for (auto& v : pies) {
      sort(begin(v), end(v));

      u32 price = 0;
      u32 count = 0;
      vector<u32> yy(mpies);
      u32 last = 0;

      for (u32 i = 0; i < mpies; i++) {
        u32 x = v[i];
        price += x;
        count++;
        v[i] = x = price + count * count;
        yy[i] = x - last;
        last = x;
      }
      sums.push_back(yy);
    }

    vector<u32> xx(ndays);

    for (u32 needPies = 0; needPies < ndays; needPies++) {
      u32 bestPrice = -1;
      u32 bestDay = 0;
      u32 bestPie = 0;
      for (u32 day = 0; day < ndays; day++) {
        for (u32 i = xx[day]; i < mpies; i++) {
          u32 x = sums[day][i];
          if (x < bestPrice) {
            bestDay = day;
            bestPrice = x;
            bestPie = i;
            break;
          }
        }
      }
      xx[bestDay] = bestPie + 1;
    }

    u64 sol = 0;
    for (u32 day = 0; day < ndays; day++) {
      u32 i = xx[day];
      if (i > 0)
        sol += pies[day][i - 1];
    }


    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
