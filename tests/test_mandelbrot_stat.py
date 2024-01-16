#!/usr/bin/env python3
import os
import subprocess
import sys

def main() -> None:
    # Get expected parameters
    ratios = {}
    if len(sys.argv) == 5:
        ratios["instructions"] = float(sys.argv[1])
        ratios["cycles"] = float(sys.argv[2])
        ratios["branch-misses"] = float(sys.argv[3])
        ratios["cpu-clock"] = float(sys.argv[4])
    else:
        print("Wrong amount of arguments",file=sys.stderr)
        print("Usage:", os.path.basename(sys.argv[0]), "ratio_instructions ratio_cycles ratio_branch_misses ratio_cpu_clock")
        sys.exit(1)
    
    # Define the paths of expected performance data
    perf_reports_dir = os.path.join(os.path.dirname(os.path.realpath(__file__)), "../perf_reports")
    basic_stat_path = os.path.join(perf_reports_dir, "mandelbrot_basic_stat")
    optimized_stat_path = os.path.join(perf_reports_dir, "mandelbrot_optimized_stat")
    
    if not (os.path.isfile(basic_stat_path) and os.path.isfile(optimized_stat_path)):
        print("ERROR: no mandelbrot perf stat",file=sys.stderr)
        sys.exit(1)
    
    events = ratios.keys()
    paths = [basic_stat_path, optimized_stat_path]
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
    
    if not iteration:
        print("The number of iterations of the mandelbrot program is not correct",file=sys.stderr)
        sys.exit(1)
    
    if not found:
        print("One of the required events is not found in the mandelbrot files",file=sys.stderr)
        sys.exit(1)
    
    # Extract the performance metrics from the report
    def extract_value(stat_path, event):
        with open(stat_path, "r") as f:
            for line in f:
                if (' '+ event) in line:
                    subline = line[0:line.find(event)]
                    return int(''.join(filter(str.isdigit, subline)))
        return None
    
    basic_inst = extract_value(basic_stat_path, "instructions")
    optimized_inst = extract_value(optimized_stat_path, "instructions")
    
    # Compare the extracted performance metrics
    if basic_inst * ratios["instructions"] < optimized_inst:
        print("Error: too many instructions executed",file=sys.stderr)
        sys.exit(1)
    
    basic_cycles = extract_value(basic_stat_path, "cycles")
    optimized_cycles = extract_value(optimized_stat_path, "cycles")
    
    if basic_cycles * ratios["cycles"] < optimized_cycles:
        print("Error: too many cycles",file=sys.stderr)
        sys.exit(1)
    
    basic_branch_miss = extract_value(basic_stat_path, "branch-misses")
    optimized_branch_miss = extract_value(optimized_stat_path, "branch-misses")
    
    if basic_branch_miss * ratios["branch-misses"] < optimized_branch_miss:
        print("Error: too many branch misses",file=sys.stderr)
        sys.exit(1)
    
    basic_time = extract_value(basic_stat_path, "cpu-clock")
    optimized_time = extract_value(optimized_stat_path, "cpu-clock")
    
    if basic_time * ratios["cpu-clock"] < optimized_time:
        print("Error: too much time consumed",file=sys.stderr)
        sys.exit(1)
    
    sys.exit(0)

if __name__ == "__main__":
    main()
