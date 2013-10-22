all: objs/Fractal.o objs/Buddhabrot.o objs/Mandelbrot.o objs/fractalgen.o objs/lodepng.o
	g++ -fopenmp -g -o fractalgen objs/Fractal.o objs/Buddhabrot.o objs/Mandelbrot.o objs/fractalgen.o objs/lodepng.o

objs/Fractal.o: src/Fractal.cpp
	g++ -fopenmp -g -c -o objs/Fractal.o src/Fractal.cpp -ansi -pedantic -Wall -Wextra -O3

objs/Mandelbrot.o: src/Mandelbrot.cpp 
	g++ -fopenmp -g -c -o objs/Mandelbrot.o src/Mandelbrot.cpp -ansi -pedantic -Wall -Wextra -O3

objs/fractalgen.o: src/fractalgen.cpp
	g++ -fopenmp -g -c -o objs/fractalgen.o src/fractalgen.cpp -ansi -pedantic -Wall -Wextra -O3

objs/Buddhabrot.o: src/Buddhabrot.cpp
	g++ -fopenmp -g -c -o objs/Buddhabrot.o src/Buddhabrot.cpp -ansi -pedantic -Wall -Wextra -O3

objs/lodepng.o: src/lodepng.cpp
	g++ -fopenmp -g -c -o objs/lodepng.o src/lodepng.cpp -ansi -pedantic -Wall -Wextra -O3

clean:
	rm objs/*.o fractalgen
