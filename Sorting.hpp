#pragma once
#include <vector>
#include <random>
#include <algorithm>

inline std::vector<int> rand_array(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
    return arr;
}
