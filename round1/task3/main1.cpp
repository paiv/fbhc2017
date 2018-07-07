#include <algorithm>
#include <iostream>
#include <tuple>
#include <queue>
#include <unordered_set>
#include <vector>
#include <paiv/hash_tuple.hpp>
using namespace std;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t s32;
typedef int64_t s64;


int
main(int argc, char* argv[]) {

  u32 ntests; cin >> ntests;
  for (u32 test = 0; test < ntests; test++) {

    u32 ncities, mroads, kppl; cin >> ncities >> mroads >> kppl;

    // road: from - to - gas
    vector<vector<vector<u16>>> roads;
    vector<unordered_set<u8>> links(ncities);
    // ride: from - to
    queue<tuple<u8,u8>> orders;

    vector<vector<u16>> blank(ncities);
    roads.assign(ncities, blank);

    for (u32 mi = 0; mi < mroads; mi++) {
      u32 from, to, gas; cin >> from >> to >> gas;
      roads[from-1][to-1].emplace_back(gas);
      roads[to-1][from-1].emplace_back(gas);
      links[from-1].emplace(to-1);
      links[to-1].emplace(from-1);
    }

    for (u32 ki = 0; ki < kppl; ki++) {
      u32 from, to; cin >> from >> to;
      orders.emplace(from - 1, to - 1);
    }


    // best road: from - to - gas
    vector<vector<u16>> best_roads;
    vector<u16> blank1(ncities);
    best_roads.assign(ncities, blank1);

    for (u32 from = 0; from < ncities; from++) {
      for (u32 to = 0; to < ncities; to++) {
        auto& possible = roads[from][to];
        if (possible.size() > 0)
          best_roads[from][to] = *min_element(begin(possible), end(possible));
      }
    }


    s64 sol = -1;

    typedef struct state {
      s64 total_gas;
      u8 pos;
      unordered_set<u8> visited;
      // vector<u8> path;
      queue<tuple<u8,u8>> orders;
      queue<tuple<u8,u8>> rides;

      u8 is_terminal() const {
        return orders.size() == 0 && rides.size() == 0;
      }

      bool operator < (const state& other) const {
        #if 0
        return total_gas > other.total_gas;
        #else
        return total_gas + orders.size() > other.total_gas + other.orders.size();
        #endif
      }
    } state;

    state startState = {0, 0, {0}, orders, {}};
    while (startState.orders.size() > 0
        && startState.rides.size() < 2
        && get<0>(startState.orders.front()) == startState.pos) {
      startState.rides.push(startState.orders.front());
      startState.orders.pop();
    }

    priority_queue<state> fringe;
    fringe.push(startState);

    while (fringe.size() > 0) {
      auto currentState = fringe.top();
      fringe.pop();

      if (currentState.is_terminal()) {
        sol = currentState.total_gas;
        break;
      }

      for (auto link : links[currentState.pos]) {
        if (currentState.visited.find(link) != end(currentState.visited))
          continue;

        auto nextState = currentState;
        auto gas = best_roads[currentState.pos][link];

        if (gas > 0) {
          nextState.total_gas += gas;
          nextState.pos = link;
          nextState.visited.insert(link);
          // nextState.path.push_back(link);

          while (nextState.rides.size() > 0
              && get<1>(nextState.rides.front()) == nextState.pos) {

            nextState.rides.pop();
            nextState.visited = {link};
          }

          while (nextState.orders.size() > 0
              && nextState.rides.size() < 2
              && get<0>(nextState.orders.front()) == nextState.pos) {

            nextState.rides.push(nextState.orders.front());
            nextState.orders.pop();
            nextState.visited = {link};
          }

          fringe.push(nextState);
        }
      }
    }

    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
