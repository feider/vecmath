examples: examples/add examples/dprod examples/cprod examples/norm

examples/add: examples/add.c vecmath/vecmath.c vecmath/vecmath.h
	gcc examples/add.c vecmath/vecmath.c -O3 -lm -o examples/add

examples/dprod: examples/dprod.c vecmath/vecmath.c vecmath/vecmath.h
	gcc examples/dprod.c vecmath/vecmath.c -O3 -lm -o examples/dprod

examples/cprod: examples/cprod.c vecmath/vecmath.c vecmath/vecmath.h
	gcc examples/cprod.c vecmath/vecmath.c -O3 -lm -o examples/cprod

examples/norm: examples/norm.c vecmath/vecmath.c vecmath/vecmath.h
	gcc examples/norm.c vecmath/vecmath.c -O3 -lm -o examples/norm

install_headers:
	cp vecmath/vecmath.h /usr/include/

