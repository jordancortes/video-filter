CC=icc
CGFLAGS=-c

# For dev, to avoid recompiling everything delete 'clean'
CGOPTION=

all: video-filter $(CGOPTION)

video-filter: Jzon.o filters.o lodepng.o video-filter.cpp
	$(CC) $^ -o $@

Jzon.o: Jzon.cpp
	$(CC) $(CGFLAGS) $^

filters.o: filters.cpp
	$(CC) $(CGFLAGS) $^

lodepng.o: lodepng.h lodepng.cpp
	$(CC) $(CGFLAGS) $^

clean:
	rm Jzon.o
	rm filters.o
	rm lodepng.o