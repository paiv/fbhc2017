
namespace paiv {

typedef vector<vector<u32>> problem;
typedef vector<string> solution;


problem
parse_input() {
  return parse_input_block_expanded<u32>();
}


u32
solve_day(const vector<u32>& day) {
  auto sorted = day;
  sort(begin(sorted), end(sorted));

  u32 res = 0;
  auto tail = list<u32>(begin(sorted), end(sorted));

  while (tail.size() > 0) {
    auto wei = tail.back();
    tail.pop_back();

    u32 k = ceil(50.0 / wei) - 1;
    if (tail.size() >= k) {
      while (k-- > 0)
        tail.pop_front();
    }
    else {
      break;
    }

    res++;
  }

  return res;
}


solution
solve(const problem& prob) {
  solution sol;

  u32 count = 0;
  for (auto day : prob) {

    auto n = solve_day(day);

    stringstream so;
    so << "Case #" << ++count << ": " << n;
    sol.push_back(so.str());
  }

  return sol;
}

}
