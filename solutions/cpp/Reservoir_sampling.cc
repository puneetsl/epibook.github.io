// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::default_random_engine;
using std::endl;
using std::istringstream;
using std::random_device;
using std::string;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

// @include
vector<int> OnlineRandomSample(istringstream* sin, int k) {
  int x;
  vector<int> running_sample;
  // Stores the first k elements.
  // @exclude
  // clang-format off
  // @include
  for (int i = 0; i < k && *sin >> x; ++i) {
    // @exclude
    // clang-format on
    // @include
    running_sample.emplace_back(x);
  }

  // After the first k elements.
  int num_seen_so_far = k;
  while (*sin >> x) {
    default_random_engine seed((random_device())());  // Random num generator.
    // Generate a random number in [0, num_seen_so_far], and if this number is
    // in [0, k - 1], we replace that element from the sample with x.
    uniform_int_distribution<int> rand_idx_gen(0, num_seen_so_far);
    int idx_to_replace = rand_idx_gen(seed);
    if (idx_to_replace < k) {
      running_sample[idx_to_replace] = x;
    }
    ++num_seen_so_far;
  }
  return running_sample;
}
// @exclude

int main(int argc, char* argv[]) {
  int n, k;
  default_random_engine gen((random_device())());
  if (argc == 2) {
    n = atoi(argv[1]);
    uniform_int_distribution<int> dis(1, n);
    k = dis(gen);
  } else if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  } else {
    uniform_int_distribution<int> n_dis(0, 99999);
    n = n_dis(gen);
    uniform_int_distribution<int> k_dis(1, n);
    k = k_dis(gen);
  }
  vector<int> A(n);
  iota(A.begin(), A.end(), 0);
  string s;
  for (int i = 0; i < A.size(); ++i) {
    stringstream ss;
    ss << A[i];
    s += ss.str();
    s += ' ';
  }
  cout << n << ' ' << k << endl;
  istringstream sin(s);
  vector<int> ans = OnlineRandomSample(&sin, k);
  assert(ans.size() == k);
  /*
  copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " "));
  cout << endl;
  */
  return 0;
}
