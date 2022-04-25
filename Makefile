CFLAGS = -Wall -Wextra -Werror
CCFLAGS = -Wall -Wextra -Wconversion -Wredundant-decls -Wshadow -Wno-unused-parameter

all: geometry

geometry: bin/geometry

test-functions.o: test/test-functions.c
	gcc -c $(CCFLAGS) -o $@ $< -lm

test-geometry.o: test/test-geometry.c
	gcc -c $(CCFLAGS) -o $@ $< -lm

test: test-functions.o test-geometry.o
	gcc $(LDFLAGS) test-functions.o test-geometry.o -o tests -lm

bin/geometry: obj/src/geometry/geometry.o obj/src/libgeometry/libgeometry.a
	gcc $(CFLAGS) -o $@ $^ -lm

obj/src/geometry/geometry.o: src/geometry/geometry.c
	gcc -c -I src $(CFLAGS) -o $@ $< -lm

obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/functions.o 
	ar rcs $@ $^

obj/src/libgeometry/functions.o: src/libgeometry/functions.c
	gcc -c -I src $(CFLAGS) -o $@ $< -lm

run:
	bin/geometry

.PHONY: clean

clean:
	rm obj/src/libgeometry/*.a obj/src/libgeometry/*.o obj/src/geometry/*.o bin/geometry
	rm -f tests *.o