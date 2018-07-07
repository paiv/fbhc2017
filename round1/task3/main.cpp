#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_set>
#include <vector>
using namespace std;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t s32;
typedef int64_t s64;

static const u32 MAXN = 100;

// from - to - gas
static u16 roads[MAXN][MAXN];
static s32 routes[MAXN][MAXN];


s32
testdrive(u8 from, u8 goal, const vector<unordered_set<u8>>& links) {

  auto known = routes[from][goal];
  if (known > 0)
    return known;

  typedef struct state {
    u32 total_gas;
    u8 pos;
    unordered_set<u8> visited;
    vector<u8> path;
    vector<u16> pays;

    bool operator < (const state& other) const {
      return total_gas > other.total_gas;
    }
  } state;

  priority_queue<state> fringe;
  fringe.push({0, from, {from}, {from}, {0}});

  while (fringe.size() > 0) {
    auto s = fringe.top();
    fringe.pop();

    if (s.pos == goal) {
#if 0
      auto gas = s.total_gas;
      while (s.path.size() > 0) {
        routes[from][s.path.back()] = gas;
        gas -= s.pays.back();
        s.path.pop_back();
        s.pays.pop_back();
      }
#else
      routes[from][goal] = s.total_gas;
#endif
      return s.total_gas;
    }

    for (auto link : links[s.pos]) {
      if (s.visited.find(link) != end(s.visited))
        continue;

      auto nextState = s;

      auto gas = roads[s.pos][link];
      nextState.total_gas += gas;
      nextState.pos = link;
      nextState.visited.insert(link);
      nextState.path.push_back(link);
      nextState.pays.push_back(gas);

      auto known = routes[nextState.pos][goal];
      if (known > 0) {
        nextState.total_gas += known;
        nextState.pos = goal;
        nextState.path.push_back(goal);
        nextState.pays.push_back(known);
      }

      fringe.push(nextState);
    }
  }

  return -1;
}


int
main(int argc, char* argv[]) {

  u32 ntests; cin >> ntests;
  for (u32 test = 0; test < ntests; test++) {

    u32 ncities, mroads, kppl; cin >> ncities >> mroads >> kppl;

    // order a ride: from - to
    queue<tuple<u8,u8>> orders;
    vector<unordered_set<u8>> links(ncities);

    memset(&roads, -1, sizeof(roads));
    memset(&routes, -1, sizeof(routes));

    for (u32 mi = 0; mi < mroads; mi++) {
      u16 from, to, gas; cin >> from >> to >> gas;
      from--; to--;
      roads[from][to] = min(roads[from][to], gas);
      roads[to][from] = min(roads[to][from], gas);
      links[from].emplace(to);
      links[to].emplace(from);
    }

    for (u32 ki = 0; ki < kppl; ki++) {
      u32 from, to; cin >> from >> to;
      from--; to--;
      orders.emplace(from, to);
    }

#if 0
    for (u32 from = 0; from < ncities; from++) {
      for (u32 to = 0; to < ncities; to++) {
        routes[from][to] = testdrive(from, to, links);
      }
    }
#endif

    s64 sol = -1;

    typedef struct state {
      s64 total_gas;
      u8 pos;
      queue<tuple<u8,u8>> orders;
      queue<tuple<u8,u8>> rides;

      u8 is_terminal() const {
        return orders.size() == 0 && rides.size() == 0;
      }

      bool operator < (const state& other) const {
        return total_gas + orders.size() + rides.size() >
          other.total_gas + other.orders.size() + other.rides.size();
      }
    } state;

    priority_queue<state> fringe;
    fringe.push({0, 0, orders, {}});

    while (fringe.size() > 0) {
      auto s = fringe.top();
      fringe.pop();

      while (s.rides.size() > 0
        && get<1>(s.rides.front()) == s.pos) {

        s.rides.pop();
      }

      if (s.is_terminal()) {
        sol = s.total_gas;
        break;
      }

      while (s.orders.size() > 0 && s.rides.size() < 2
        && get<0>(s.orders.front()) == s.pos) {

        s.rides.push(s.orders.front());
        s.orders.pop();
      }

      if ((s.rides.size() == 0 || s.rides.size() == 1) && s.orders.size() > 0) {
        auto to = get<0>(s.orders.front());
        auto gas = testdrive(s.pos, to, links);
        if (gas <= 0) break;
        auto nextState = s;
        nextState.total_gas += gas;
        nextState.pos = to;
        nextState.rides.push(s.orders.front());
        nextState.orders.pop();
        fringe.push(nextState);
      }

      if (s.rides.size() == 2 || s.rides.size() == 1) {
        auto to = get<1>(s.rides.front());
        auto gas = testdrive(s.pos, to, links);
        if (gas <= 0) break;
        auto nextState = s;
        nextState.total_gas += gas;
        nextState.pos = to;
        nextState.rides.pop();
        fringe.push(nextState);
      }
    }


    cout << "Case #" << (test + 1) << ": " << sol << endl;
  }

  return 0;
}
