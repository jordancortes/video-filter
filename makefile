all:
	icc -o video-filter Jzon.cpp filters.cpp lodepng.cpp video-filter.cpp
