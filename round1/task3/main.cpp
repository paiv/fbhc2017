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

    u32 ncities, nroads, nfamilies; cin >> ncities >> nroads >> nfamilies;

    u64 sol = 0;

    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
