#pragma once

namespace paiv {


typedef struct roll {
  u8 x;
  u8 y;
  s16 z;
} roll;


typedef struct fight {
  u32 health;
  vector<roll> spells;

} fight;


istream& operator >> (istream& si, roll& obj) {
  u32 x, y;
  s32 z;
  char d;

  if (si >> x >> d >> y) {
    if (d == 'd') {
      d = si.peek();
      if ((d == '+' || d == '-') && si >> z) {
        obj.x = x;
        obj.y = y;
        obj.z = z;
      }
      else {
        if (!si) si.clear(ios::eofbit);
        obj.x = x;
        obj.y = y;
        obj.z = 0;
      }
    }
    else {
      si.setstate(ios::failbit);
    }
  }
  return si;
}


istream& operator >> (istream& si, fight& obj) {
  auto line1 = parse_input_n<u32>();
  auto line2 = parse_input_n<roll>();
  if (line2.size() == line1[1]) {
    obj.health = line1[0];
    obj.spells = line2;
  }
  else {
    si.setstate(ios::failbit);
  }
  return si;
}


}
