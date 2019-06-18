#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <random>
#include <queue>
#include <deque>
#include <sstream>
#include <fstream>
#include <istream>
#include <map>
#include <atomic>

using namespace std::chrono_literals;

namespace rnd {
  template <typename T> auto get_random(T lower_bound, T upper_bound) {
    static std::mt19937_64 mersenne_twister {std::random_device{}()};
    std::uniform_int_distribution<T> distribution (lower_bound, upper_bound);
    return distribution (mersenne_twister);
  }
}

using prefix_t = std::deque<std::string>;

namespace {
  static constexpr auto NPREF = 3;
  static constexpr auto MAXGEN = 350;
  std::map<prefix_t, std::vector<std::string>> states;
}

int main() {

  auto add_state = [&](prefix_t& prefix, std::string const& string) -> void {
    if (prefix.size() == NPREF) {
      states[prefix].push_back(string);
      prefix.pop_front();
    }
    prefix.push_back(string);
    return;
  };

  auto build_state = [&](prefix_t& prefix, std::istream& istream) -> void {
    std::string buffer;
    while (istream >> buffer) add_state(prefix, buffer);
    return;
  };

  auto generate = [&](std::size_t number, std::string const& output_filename) {
    std::ofstream ofstream {output_filename, std::ios::trunc};
    prefix_t prefix;
    for (std::size_t index = 0; index < NPREF; ++index) add_state(prefix, "\n");
    for (std::size_t index = 0; index < number; ++index) {
      auto& suffix = states[prefix];
      std::string const& ref = suffix[rnd::get_random(0UL, suffix.size() - 1)];
      if (ref == "\n") break;
      ofstream << ref << " ";
      prefix.pop_front();
      prefix.push_back(ref);
    }
    ofstream << "..." << "\n";
    std::cout << "Finished the generation." << std::endl;
  };

  std::ifstream file_handler ("text.txt");
  std::string word;
  prefix_t prefix;

  for (std::size_t index = 0; index < NPREF; ++index) add_state(prefix, "\n");
  build_state(prefix, file_handler);
  add_state(prefix, "\n");
  generate(MAXGEN, "output.txt");
  return 0;
}
