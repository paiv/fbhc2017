
namespace paiv {

typedef vector<vector<u32>> problem;
typedef vector<string> solution;


problem
parse_input() {
  return parse_input_block<u32>();
}


u8
solve_point(u32 d, u32 x, u32 y) {
  r32 centerX = 50;
  r32 centerY = 50;
  r32 squareR = 2500;

  r32 dX = x - centerX;
  r32 dY = y - centerY;

  r32 angle = atan2f(dY, dX);
  if (dY < 0)
    angle += 2 * M_PI;
  angle /= 2 * M_PI;

  u8 angle_check = angle <= d / 100.0 + 1e-6;
  u8 radius_check = dX*dX + dY*dY <= squareR + 1e-6;

  return angle_check && radius_check;
}

solution
solve(const problem& prob) {
  solution sol;

  u32 count = 0;
  for (auto v : prob) {

    u8 point = solve_point(v[0], v[1], v[2]);

    stringstream so;
    so << "Case #" << ++count << ": " << (point ? "black" : "white");
    sol.push_back(so.str());
  }

  return sol;
}

}
