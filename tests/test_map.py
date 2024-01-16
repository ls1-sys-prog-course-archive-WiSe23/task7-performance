#!/usr/bin/env python3
from testsupport import (
    subtest,
    test_root,
    run,
    ensure_library,
    warn,
    fail,
    info,
    project_root,
)
import filecmp
import tempfile
import sys

def main() -> None:
    with subtest("Testing map performance"):
        map_solution = test_root().joinpath("../map")
        map_optimized = test_root().joinpath("../map_optimized")

        if not map_solution.exists():
            fail("No map!")

        if not map_optimized.exists():
            fail("No optimized map, please rebase your repository from the remote!")

        run_count = 10
        optimized_time = 0
        solution_time = 0
        for _ in range(run_count):
            result = run([str(map_solution)], shell=True, capture_output=True)
            solution_time = solution_time + float(result.stdout.strip())

            result_optimized = run([str(map_optimized)], shell=True, capture_output=True)
            optimized_time = optimized_time + float(result_optimized.stdout.strip())

            # Correctness
            output = test_root().joinpath("../output")
            expected_output = test_root().joinpath("./expected_output")

            are_outputs_equal = filecmp.cmp(output, expected_output)

            if are_outputs_equal == False:
                fail("The outputs have different contents.")

        # Compute averages
        optimized_time = optimized_time / run_count
        solution_time = solution_time / run_count

        # Fraction
        fraction = optimized_time / solution_time

        info(
            f"Optimized: {optimized_time}, Solution: {solution_time}, Fraction: {fraction}"
        )

        needed_fraction = float(sys.argv[1])
        if fraction < needed_fraction:
            warn(f"Not fast enough: {fraction} < {needed_fraction}")
            sys.exit(1)

if __name__ == "__main__":
    main()
