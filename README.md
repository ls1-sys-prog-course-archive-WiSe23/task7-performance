# Task 7 - Performance

This week's exercise involves gathering performance data from programs using `perf` and then optimizing them to achieve faster execution.

## Environment and Language

The assignment requires working on a Linux system, and the language choice for this task is limited to C++.

## Task 7.1 - Matrix Multiplication

### Task 7.1.1 - Performance Before Optimization

- Use the `perf` tool to analyze the `matrix_profiling` executable and collect its profiling metrics.
- Store the performance statistics in the `perf_reports` folder as `matrix_basic_stat`.
- Requirements:
    - Maintain the format of the provided `example_stat` file.
    - Include the following event metrics: 
        number of instructions executed, CPU cycles, l1 data cache misses, data misses over all caches, an overall measure of CPU time consumed.
    - The program should be executed and monitored for 5 iterations. 

### Task 7.1.2 - Code Optimization

- Optimize the code in `matrix.cpp` for improved performance.
- Your goal is to approach or even exceed the performance of our optimized code provided as binaries.
- Deliver `libmatrix.so` in the project root directory, exporting symbols from `matrix.h`.

### Task 7.1.3 - Performance After Optimization

- Re-build the `matrix_profiling` executable with the optimized code(`make performance`).
- Use the `perf` tool to analyze its performance profiling.
- Store the performance statistics in the `matrix_optimized_stat` file within the `perf_reports` folder.
- Same requirements as Task 7.1.1.

## Task 7.2 - Mandelbrot Set Calculation

### Task 7.2.1 - Performance Before Optimization

- Use `perf` to analyze the profiling data of the `mandelbrot_profiling` executable.
- Store the performance statistics in the `mandelbrot_basic_stat` file within the `perf_reports` folder.
- Requirements:
    - Maintain the format of the provided `example_stat` file.
    - Include the following event metrics:
        number of instructions executed, CPU cycles, number of branch mispredictions, an overall measure of CPU time consumed.
    - The program should be executed and monitored for 5 iterations. 

### Task 7.2.2 - Code Optimization

- Optimize the code in `mandelbrot.cpp` for improved performance.
- Your goal is to approach or exceed the performance of our optimized code provided as binaries.
- Deliver `libmandelbrot.so` in the project root directory, exporting symbols from `mandelbrot.h`.

### Task 7.2.3 - Performance After Optimization

- Re-build the `mandelbrot_profiling` executable using your optimized `mandelbrot.cpp`.
- Gather performance profiling metrics.
- Store the performance statistics in the `mandelbrot_optimized_stat` file within the `perf_reports` folder.
- Same requirements as Task 7.2.1.

## Task 7.3 - Advanced Profiling and Optimization

In this task, you are provided with an application named `map_baseline.cpp` that contains unoptimized code. 
Your objective is to optimize this code to improve its performance. The application performs specific interactions based on commands read from a file called `records.txt`, which contains 2,000,000 commands. 
The commands can be categorized into three types: `set`, `value`, and `params`. 
- The `set` command adds a key-value pair to a map created by the application.
- The `value` command retrieves the hashed value corresponding to a given key.
- The `params` command replaces certain symbols with fixed parameters. 

The application generates the output into a file named `output`, and the execution time is displayed on the screen. 
To compare the performance of your optimized code with the given optimized executable `map_optimized`, you can use `make check`.

Here are the requirements for this task:
- Utilize `perf` to analyze the hot spots and identify the major performance bottlenecks in the provided code.
- Focus your optimization efforts on the identified bottlenecks, ensuring that you **DO NOT MODIFY** the main function.
- Concentrate on performance analysis and code review **rather than** multi-threaded programming or SIMD optimization techniques.
- Provide a modified/optimized version of the code in the `map_baseline.cpp` file. 
- Please ensure that your code can be compiled using the given `Makefile` and that executing it generates the expected output(which you don't need to push it).

Hints:
- You are allowed to use C++17 standard library.
- Because of the lackness of the data owernship, `std::string_view` is not recommended in this task.
- Compiler optimizations can help uncover performance bottlenecks and allow the code to benefit from various optimizations. However, keep in mind that higher optimization 
levels may make the code harder to analyze and interpret in the profiling results. The generated machine code can be more complex, and the relationships between source code and assembly instructions may become less straightforward.
Therefore, it's essential to consider the trade-off between optimization and ease of analysis when interpreting the `perf report` output.

## Notes

- If you want to multi-thread your code(not for task7.3), use **a maximum of 4 (four)** threads. You can expect all inputs of your code to be a multiple of 4 in size.
- If you want to use SIMD in your code(not for task7.3), use **only SSE and SSE2** intrinsics. You can filter the instructions sets on the "Intel Intrinsics Guide" (see references).
- You could verify the performance by executing the provided tests.
- We know that there are faster algorithms for matrix multiplication such as the [Strassen Algorithm](https://en.wikipedia.org/wiki/Strassen_algorithm). We **do not** want you to implement that. We want you to **optimize the naive version** given in `matrix.cpp`. The same goes for mandelbrot if you find a faster algorithm.
- For mandelbrot, you're required to use the parameters given in `tests/mandelbrot_params.h`. Do not change them.

## References

- [Matrix multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication)
- [Mandelbrot Set](https://en.wikipedia.org/wiki/Mandelbrot_set)
- [Intel Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html)
- [Perf Usage](https://perf.wiki.kernel.org/index.php/Tutorial)
