#!/usr/bin/env python3
import os
import sys

def main() -> None:
    # Define the paths of expected performance data
    perf_reports_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../perf_reports")
    basic_matrix_stat_path = os.path.join(perf_reports_dir, "matrix_basic_stat")
    optimized_matrix_stat_path = os.path.join(perf_reports_dir, "matrix_optimized_stat")
    basic_mand_stat_path = os.path.join(perf_reports_dir, "mandelbrot_basic_stat")
    optimized_mand_stat_path = os.path.join(perf_reports_dir, "mandelbrot_optimized_stat")
    
    # Check existence of profiling data
    if not (os.path.isfile(basic_matrix_stat_path) and os.path.isfile(optimized_matrix_stat_path)):
        print("ERROR: no matrix perf stat",file=sys.stderr)
        sys.exit(1)
    
    if not (os.path.isfile(basic_mand_stat_path) and os.path.isfile(optimized_mand_stat_path)):
        print("ERROR: no mandelbrot perf stat",file=sys.stderr)
        sys.exit(1)
    
    events = ["instructions", "cycles", "cache-misses", "L1-dcache-misses", "cpu-clock"]
    paths = [basic_matrix_stat_path, optimized_matrix_stat_path]
    iterations = "5 runs"
    
    found = True
    iteration = True
    for file in paths:
        with open(file, "r") as f:
            content = f.read()
            for event in events:
                if event not in content:
                    found = False
                    break
            if iterations not in content:
                iteration = False
        if not iteration:
            break
    
    if not found:
        print("One of the events required is not found in the matrix files",file=sys.stderr)
        sys.exit(1)
    
    if not iteration:
        print("The number of iterations of the matrix program is not correct",file=sys.stderr)
        sys.exit(1)
    
    events = ["instructions", "cycles", "branch-misses", "cpu-clock"]
    paths = [basic_mand_stat_path, optimized_mand_stat_path]
    
    for file in paths:
        with open(file, "r") as f:
            content = f.read()
            for event in events:
                if event not in content:
                    found = False
                    break
            if iterations not in content:
                iteration = False
        if not iteration:
            break
    
    if not iteration:
        print("The number of iterations of the mandelbrot program is not correct",file=sys.stderr)
        sys.exit(1)
    
    if not found:
        print("One of the events required is not found in the mandelbrot files",file=sys.stderr)
        sys.exit(1)
    
    sys.exit(0)

if __name__ == "__main__":
    main()
