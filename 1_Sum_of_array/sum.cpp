#include <iostream>
#include <chrono>
#include <numeric>
#include <vector>
#include <iomanip>
#include <algorithm>

// Decorator-like timing function template that returns duration
template<typename F, typename... Args>
auto measureTime(F func, Args... args) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(args...);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    return std::make_pair(result, duration.count());
}

// Standard C++ sum implementation
long long calculateSumCpp(int size) {
    long long sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += i;
    }
    return sum;
}

// STL algorithm implementation using std::accumulate
long long calculateSumSTL(int size) {
    std::vector<int> numbers(size);
    std::iota(numbers.begin(), numbers.end(), 0);
    return std::accumulate(numbers.begin(), numbers.end(), 0LL);
}

int main() {
    const int SIZE = 10000000;
    const int ITERATIONS = 10;
    
    std::vector<long long> cpp_times;
    std::vector<long long> stl_times;
    
    // Run benchmarks
    for (int i = 0; i < ITERATIONS; ++i) {
        auto [result_cpp, time_cpp] = measureTime(calculateSumCpp, SIZE);
        cpp_times.push_back(time_cpp);
        
        auto [result_stl, time_stl] = measureTime(calculateSumSTL, SIZE);
        stl_times.push_back(time_stl);
    }
    
    // Calculate statistics for C++ implementation
    auto cpp_min = *std::min_element(cpp_times.begin(), cpp_times.end());
    auto cpp_max = *std::max_element(cpp_times.begin(), cpp_times.end());
    auto cpp_avg = std::accumulate(cpp_times.begin(), cpp_times.end(), 0LL) / ITERATIONS;
    
    // Calculate statistics for STL implementation
    auto stl_min = *std::min_element(stl_times.begin(), stl_times.end());
    auto stl_max = *std::max_element(stl_times.begin(), stl_times.end());
    auto stl_avg = std::accumulate(stl_times.begin(), stl_times.end(), 0LL) / ITERATIONS;
    
    // Print results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "C++ Implementation Results (ms):\n";
    std::cout << "Min: " << cpp_min << ", Max: " << cpp_max << ", Avg: " << cpp_avg << "\n\n";
    
    std::cout << "STL Implementation Results (ms):\n";
    std::cout << "Min: " << stl_min << ", Max: " << stl_max << ", Avg: " << stl_avg << "\n";
    
    return 0;
}

// C++ Implementation Results (ms):
// Min: 24, Max: 26, Avg: 25

// STL Implementation Results (ms):
// Min: 219, Max: 280, Avg: 235