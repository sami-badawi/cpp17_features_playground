#include <iostream>
#include <set>
#include <vector>
#include <tuple>
#include "speech.hpp"

std::tuple<int, int> no_result = {-1, -1};

auto inside_vector(int index, std::size_t vector_lenght) -> bool {
    return 0 <= index && index < vector_lenght;
}

/**
 * set::contains is in C++20 not in C++17
 */
auto set_contains(const std::set<int> & int_set, int element) -> bool {
    return int_set.find(element) != int_set.end();
}

auto find_first_jump_to_0(const std::vector<int>& input, int start_index) -> std::tuple<int, int> {
    int level = 1;
    auto vector_lenght = input.size();
    if (!inside_vector(start_index, vector_lenght))
        return no_result;
    std::set<int> visited;
    // Check now
    std::vector<int> active = {start_index};
    // Check next time
    std::vector<int> next_active;
    while (!active.empty()) {
        for (auto index: active) {
            auto index_value = input.at(index);
            if (index_value == 0)
                return {index, level};
            auto low = index - index_value;
            auto high = index + index_value;
            if (inside_vector(low, vector_lenght) && !set_contains(visited, low))
                next_active.push_back(low);
            if (inside_vector(high, vector_lenght) && !set_contains(visited, high))
                next_active.push_back(high);
        }
        active = next_active;
        next_active.clear();
        level++;
    }
    return no_result;
};

auto main(int argc, const char * argv[]) -> int {
    greeter_string_view("Dude bro");
    std::vector<int> input = {1, 0};
    auto [index, level] = find_first_jump_to_0(input, 0);
    std::cout << "Hello Result found 0 at index " << index << " at level " << level << "\n\n";
    return 0;
}