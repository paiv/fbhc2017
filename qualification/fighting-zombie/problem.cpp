
namespace paiv {

typedef vector<fight> problem;
typedef vector<string> solution;


problem
parse_input() {
  return parse_objects::parse_input_list<fight>();
}


typedef unordered_map<tuple<u32,u32>,u32> memoize;

u32
cast(u32 hp, const roll& dice, u32 dmg, memoize& memo) {
  if (dice.x == 0) {
    return dmg + dice.z >= hp ? 1 : 0;
  }

  auto t = make_tuple(dice.x, dmg);
  auto it = memo.find(t);
  if (it != end(memo))
    return it->second;

  u32 accum = 0;
  for (u32 x = 0; x < dice.y; x++) {
    auto inner = dice;
    inner.x -= 1;

    accum += cast(hp, inner, dmg + x + 1, memo);
  }

  memo[t] = accum;

  return accum;
}

r32
cast(u32 hp, const roll& dice) {
  memoize memo;
  auto n = cast(hp, dice, 0, memo);
  r64 total = pow(r64(dice.y), r64(dice.x));
  return n / total;
}


r32
solve_fight(const fight& play) {
  r32 best = 0;

  for (auto spell : play.spells) {
    auto dmg = cast(play.health, spell);
    best = max(best, dmg);
  }

  return best;
}


solution
solve(const problem& prob) {
  solution sol;

  u32 count = 0;
  for (auto play : prob) {

    auto n = solve_fight(play);

    stringstream so;
    so << "Case #" << ++count << ": " << fixed << setprecision(6) << n;
    sol.push_back(so.str());
  }

  return sol;
}

}
