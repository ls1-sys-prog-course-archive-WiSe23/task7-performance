CC ?= cc
CFLAGS ?= -g -Wall -O2
CXX ?= c++
CXXFLAGS ?= -O3 -std=c++17 -Wall -g
CARGO ?= cargo
RUSTFLAGS ?= -g
LDFLAGS = -lpthread

.PHONY: all clean performance boss libmatrix.so libmandelbrot.so matrix_profiling mandelbrot_profiling map check

all: libmatrix.so libmandelbrot.so performance boss

performance: matrix_profiling mandelbrot_profiling

boss: map

clean:
	rm -f matrix_profiling mandelbrot_profiling libmatrix.so libmandelbrot.so map_baseline map

libmatrix.so: matrix.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $^ $(LDFLAGS)

libmandelbrot.so: mandelbrot.cpp
	$(CXX) $(CXXFLAGS) -shared -fPIC -o $@ $^ $(LDFLAGS)

matrix_profiling: matrix_profiling.cpp matrix.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

mandelbrot_profiling: mandelbrot_profiling.cpp mandelbrot.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

map: map_baseline.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

check: all
	$(MAKE) -C tests check
