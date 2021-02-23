includes=-I./

examples: examples/add examples/dprod examples/cprod examples/norm examples/geo_tests

examples/add: examples/add.c vecmath/vecmath.h
	gcc examples/add.c $(includes) -O3 -lm -o examples/add

examples/dprod: examples/dprod.c vecmath/vecmath.h
	gcc examples/dprod.c $(includes) -O3 -lm -o examples/dprod

examples/cprod: examples/cprod.c vecmath/vecmath.h
	gcc examples/cprod.c $(includes) -O3 -lm -o examples/cprod

examples/norm: examples/norm.c vecmath/vecmath.h
	gcc examples/norm.c $(includes) -O3 -lm -o examples/norm

examples/geo_tests: examples/geo_tests.c vecmath/geometry.h
	gcc examples/geo_tests.c $(includes) -O3 -lm -o examples/geo_tests

install_headers:
	cp vecmath/vecmath.h /usr/include/

