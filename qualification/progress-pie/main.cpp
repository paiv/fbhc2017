#if 1
#include <cmath>
#include <iostream>
using namespace std;
typedef uint8_t u8;
typedef uint32_t u32;
typedef int32_t s32;
typedef double_t r64;

int
main(int argc, char* argv[]) {
  u32 ntests; cin >> ntests;

  for (u32 test = 0; test < ntests; test++) {
    u32 p; cin >> p;
    s32 x, y; cin >> x >> y;
    u8 sol = 0;

    if (p > 0) {
      x -= 50;
      y -= 50;
      if (x*x + y*y <= 2500) {
        r64 ang = atan2(y, x);
        if (ang < 0) ang += M_PI * 2;
        sol = (ang / (M_PI * 2) * 100) <= p;
      }
    }

    cout << "Case #" << (test + 1) << ": " << (sol ? "black" : "white") << endl;
  }

  return 0;
}

#else
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <utility>
#include <vector>

#define F first
#define S second
#define pb push_back
#define forn(i, n) for(int i = 0 ; (i) < (n) ; ++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define pw(x) (1LL<<(x))

using namespace std;

typedef long long ll;
typedef double dbl;
typedef vector<int> vi;
typedef pair<int, int> pi;

const int inf = 1.01e9;
const dbl eps = 1e-9;

/* --- main part --- */

const int N = 1e5 + 10;

int a[N];



int main()
{
    #ifdef home
        assert(freopen("1.in", "r", stdin));
        assert(freopen("1.out", "w", stdout));
    #endif
    int tn;
    scanf("%d", &tn);
    forn(tt, tn)
    {
        printf("Case #%d: ", tt + 1);
        dbl p, x, y;
        scanf("%lf%lf%lf", &p, &x, &y);
        p = p / 100 * 360;
        dbl d = sqrt((x - 50) * (x - 50) + (y - 50) * (y - 50));
        int ok = 0;
        if (p > 0 && d < 50 + eps)
        {
            dbl alp = atan2(x - 50, y - 50) / acos(-1) * 180;
            while (alp < -eps) alp += 360;
            if (alp < p + eps) ok = 1;
        }
        if (ok) printf("black\n");
        else printf("white\n");
    }


    #ifdef home
        eprintf("time = %d ms\n", (int)(clock() * 1000. / CLOCKS_PER_SEC));
    #endif
    return 0;
}
#endif
