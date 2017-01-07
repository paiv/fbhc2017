
namespace paiv {

template <typename T>
T
parse_input_1(istream& si = cin) {
  string buf;
  if (getline(si, buf)) {
    stringstream reader(buf);
    T x;
    if (reader >> x)
      return x;
  }
  return 0;
}


template <typename T>
vector<T>
parse_input_n(istream& si = cin) {
  vector<T> values;
  string buf;

  if (getline(si, buf)) {
    stringstream reader(buf);
    T x;

    while (reader >> x) {
      values.push_back(x);
    }
  }
  return values;
}


template <typename T>
vector<vector<T>>
parse_input_block() {
  vector<vector<T>> res;
  auto n = parse_input_1<u32>();
  while (n-- > 0)
    res.push_back(parse_input_n<T>());
  return res;
}


template <typename T>
vector<T>
parse_input_n_expanded() {
  vector<T> res;
  auto n = parse_input_1<u32>();
  while (n-- > 0)
    res.push_back(parse_input_1<T>());
  return res;
}


template <typename T>
vector<vector<T>>
parse_input_block_expanded() {
  vector<vector<T>> res;
  auto n = parse_input_1<u32>();
  while (n-- > 0)
    res.push_back(parse_input_n_expanded<T>());
  return res;
}


namespace parse_objects {

template <typename T>
vector<T>
parse_input_list() {
  vector<T> res;
  auto n = parse_input_1<u32>();
  while (n-- > 0) {
    T x;
    if (cin >> x) {
      res.push_back(x);
    }
    else {
      return {};
    }
  }
  return res;
}

}


}
