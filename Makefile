CFLAGS = -Wall -Wextra -Werror

bin/geometry: obj/src/geometry/geometry.o obj/src/libgeometry/libgeometry.a
	$(CC) $(CFLAGS) -o $@ $^
bin/test-geometry: obj/src/libgeometry/libgeometry.a ctest.h obj/src/libgeometry/test-geometry.o
	$(CC) $(CFLAGS) -o $@ $^
obj/src/geometry/test-geometry.o: ctest.h obj/src/geometry/test-geometry.c
	$(CC) -c $(CFLAGS) -o $@ $<
obj/src/geometry/geometry.o: obj/src/geometry/geometry.c
	$(CC) -c $(CFLAGS) -o $@ $<
obj/src/libgeometry/libgeometry.a: obj/src/libgeometry/functions.o
	ar rcs $@ $^
obj/src/libgeometry/functions.o: obj/src/libgeometry/functions.c
	$(CC) -c $(CFLAGS) -o $@ $<
run: 
	./*geometry
test:
	./*geometry-test
clean:
	rm -f bin/* obj/src/geometry*.o obj/src/libgeometry*.o obj/src/test-geometry*.o obj/src/functions*.o
-include geometry.d functions.d