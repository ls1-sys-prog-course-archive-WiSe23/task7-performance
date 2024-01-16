#!/bin/bash
set -e

# Get expected parameters
declare -A RATIOS

if (($#==5)); then
    RATIOS[0]=$1 RATIOS[1]=$2 RATIOS[2]=$3 RATIOS[3]=$4 RATIOS[4]=$5
else
  echo 'Wrong amount of arguments'
  echo "Usage: ${0##*/} ratio_instructions ratio_cycles ratio_cache_misses ratio_l1_cache ratio_cpu_clock"
  exit 1
fi

# Define the paths of expected performance data
PERF_REPORTS_DIR="$(dirname $(realpath $0))/../perf_reports"
BASIC_STAT_PATH="$PERF_REPORTS_DIR/matrix_basic_stat"
OPTIMIZED_STAT_PATH="$PERF_REPORTS_DIR/matrix_optimized_stat"

# Extract the performance metrics from the report
BASIC_INST=$(grep "instructions" $BASIC_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g' )
OPTIMIZED_INST=$(grep "instructions" $OPTIMIZED_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g' )

# Compare the extracted performance metrics (between basic ones and optimized ones)
ratio_i=${RATIOS[0]}
if [ $(echo "$BASIC_INST * $ratio_i < $OPTIMIZED_INST" | bc) -eq 1 ]; then
    echo "Error: too many instructions executed"
    exit 1
fi

BASIC_CYCLES=$(grep "cycles" $BASIC_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')
OPTIMIZED_CYCLES=$(grep "cycles" $OPTIMIZED_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')

ratio_c=${RATIOS[1]}
if [ $(echo "$BASIC_CYCLES * $ratio_c < $OPTIMIZED_CYCLES" | bc) -eq 1 ]; then
    echo "Error: too many cycles"
    exit 1
fi

BASIC_CACHE_MISS=$(grep "cache-misses" $BASIC_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')
OPTIMIZED_CACHE_MISS=$(grep "cache-misses" $OPTIMIZED_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')

ratio_cm=${RATIOS[2]}
if [ $(echo "$BASIC_CACHE_MISS * $ratio_cm < $OPTIMIZED_CACHE_MISS" | bc) -eq 1 ]; then
    echo "Error: too many cache misses"
    exit 1
fi

BASIC_L1_CACHE_MISS=$(grep "L1-dcache-misses" $BASIC_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')
OPTIMIZED_L1_CACHE_MISS=$(grep "L1-dcache-misses" $OPTIMIZED_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')

ratio_l1=${RATIOS[3]}
if [ $(echo "$BASIC_L1_CACHE_MISS * $ratio_l1 < $OPTIMIZED_L1_CACHE_MISS" | bc) -eq 1 ]; then
    echo "Error: too many l1 data cache misses"
    exit 1
fi

BASIC_TIME=$(grep "cpu-clock" $BASIC_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')
OPTIMIZED_TIME=$(grep "cpu-clock" $OPTIMIZED_STAT_PATH | awk '{print $1}' | tr -cs '0-9' ' ' | sed 's/ //g')

ratio_time=${RATIOS[4]}
if [ $(echo "$BASIC_TIME * $ratio_time < $OPTIMIZED_TIME" | bc) -eq 1 ]; then
    echo "Error: too much time consumed"
    exit 1
fi

exit 0
