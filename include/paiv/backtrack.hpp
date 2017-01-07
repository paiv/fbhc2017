
#pragma once


namespace paiv {

template <typename SearchState>
u32
backtracking_solver(SearchState startState, u8 (*callback)(const SearchState& solution)) {

  queue<SearchState> fringe;
  u32 results_count = 0;

  fringe.push(startState);

  while (fringe.size() > 0) {

    auto currentState = fringe.front();
    fringe.pop();

    if (currentState.backtrack_reject())
      continue;

    if (currentState.backtrack_accept()) {
      results_count++;
      if (!callback(currentState))
        break;
    }

    for (auto nextState = currentState.backtrack_next();
      !nextState.is_none;
      nextState = nextState.backtrack_next()) {
        fringe.push(nextState);
    }
  }

  return results_count;
}

}
