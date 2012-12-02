SET(SRCS	Src/Timing.cpp
	)

include_directories("Include")

add_library(common STATIC ${SRCS})
target_link_libraries(common)
