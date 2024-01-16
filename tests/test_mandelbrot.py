#!/usr/bin/env python3

from testsupport import (
    subtest,
    test_root,
    run,
    ensure_library,
    warn,
    info,
    project_root,
)
import tempfile
import sys


def main() -> None:
    with subtest("Testing mandelbrot performance"):
        mandelbrot_driver = test_root().joinpath("mandelbrot_driver")
        mandelbrot_driver_output = test_root().joinpath("mandelbrot_driver_output")

        if not mandelbrot_driver.exists():
            run(["make", "-C", str(test_root()), "mandelbrot_driver"])

        libmandelbrot_dir = str(project_root())
        libmandelbrot_optimized_dir = str(test_root())
        library_path = ":".join([libmandelbrot_dir, libmandelbrot_optimized_dir])
        extra_env = {"LD_LIBRARY_PATH": library_path}
        
        run_count = 10
        optimized_time = 0
        solution_time = 0
        with open(str(mandelbrot_driver_output), mode="w+") as output:
            for _ in range(run_count):
                run([str(mandelbrot_driver)], extra_env=extra_env, stdout=output)

                output.seek(0)
                lines = output.read().splitlines()

                times = [float(x) for x in lines]
                optimized_time = optimized_time + times[0]
                solution_time = solution_time + times[1]

                output.truncate(0)
                output.seek(0)

        # Compute average
        optimized_time = optimized_time / run_count
        solution_time = solution_time / run_count

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
