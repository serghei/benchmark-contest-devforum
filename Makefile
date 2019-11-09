all: generator benchmark

generator: generator.c
	gcc -O2 generator.c -o generator

benchmark: benchmark.c
	gcc -O2 benchmark.c -o benchmark

clean:
	-rm -f generator benchmark

distclean: clean
	-rm -f random_numbers.txt
	-rm -f result.txt
