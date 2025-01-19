import time
import numpy as np
from statistics import mean

def timeit(func):
    def wrapper(*args, **kwargs):
        start = time.time()
        result = func(*args, **kwargs)
        end = time.time()
        diff = (end - start) * 1000
        return result, diff
    return wrapper

@timeit
def calculate_sum_python(size: int) -> int:
    return sum(range(size))

@timeit
def calculate_sum_numpy(size: int) -> int:
    return np.sum(np.arange(size))

if __name__ == "__main__":
    SIZE = 10_000_000
    ITERATIONS = 10
    
    python_times = []
    numpy_times = []
    
    # Run benchmarks
    for _ in range(ITERATIONS):
        _, python_time = calculate_sum_python(SIZE)
        python_times.append(python_time)
        
        _, numpy_time = calculate_sum_numpy(SIZE)
        numpy_times.append(numpy_time)
    
    # Calculate statistics
    print("Python Implementation Results (ms):")
    print(f"Min: {min(python_times):.2f}, Max: {max(python_times):.2f}, Avg: {mean(python_times):.2f}\n")
    
    print("NumPy Implementation Results (ms):")
    print(f"Min: {min(numpy_times):.2f}, Max: {max(numpy_times):.2f}, Avg: {mean(numpy_times):.2f}")

# Python Implementation Results (ms):
# Min: 141.05, Max: 189.50, Avg: 158.68

# NumPy Implementation Results (ms):
# Min: 17.80, Max: 61.88, Avg: 23.71