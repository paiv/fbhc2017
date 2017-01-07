#include "unity.cpp"


int
main(int argc, char* argv[]) {

  auto prob = parse_input();
  auto solved = solve(prob);

  for (auto s : solved)
    cout << s << endl;

  return 0;
}
