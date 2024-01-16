CXX ?= g++
CXXFLAGS ?= -O3 -std=c++17 -Wall -g
LDFLAGS ?= -lpthread

.PHONY: all check

all: matrix_driver mandelbrot_driver

optimized: libmatrix_optimized.so libmandelbrot_optimized.so

libmandelbrot_optimized.so: mandelbrot_optimized.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -s -o $@ $^ $(LDFLAGS)

libmatrix_optimized.so: matrix_optimized.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -s -o $@ $^ $(LDFLAGS)

matrix_driver: matrix_driver.cpp
	$(CXX) $(CXXFLAGS) -I.. -o $@ $< -L. -lmatrix_optimized -L.. -lmatrix  $(LDFLAGS)

mandelbrot_driver: mandelbrot_driver.cpp
	$(CXX) $(CXXFLAGS) -I.. -o $@ $< -L. -lmandelbrot_optimized -L.. -lmandelbrot  $(LDFLAGS) 

clean:
	rm -f matrix_driver matrix_driver_output
	rm -f mandelbrot_driver mandelbrot_driver_output

check: all	
	rm -f matrix_driver_output
	python3 ./test_matrix_multiplication.py 0.98
	rm -f mandelbrot_driver_output
	python3 ./test_mandelbrot.py 0.98
	python3 test_existence_perf.py
	python3 test_matrix_stat.py 0.5 0.2 0.4 0.1 0.2
	python3 test_mandelbrot_stat.py 0.4 0.4 0.4 0.4
	python3 ./test_map.py 0.98
