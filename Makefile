CFLAGS = -Wall -Wextra -Werror

bin/geometry: obj/src/geometry/geometry.o obj/src/libgeometry/functions.o
		$(CC) $(CFLAGS) -o $@ $^

obj/src/geometry/geometry.o: src/geometry/geometry.c
		$(CC) -c $(CFLAGS) -o $@ $<

obj/src/libgeometry/functions.o: src/libgeometry/functions.c
		$(CC) -c $(CFLAGS) -o $@ $<
run: 
		./*geometry
clean:
		rm -f bin/* obj/src/geometry*.o obj/src/libgeometry*.o