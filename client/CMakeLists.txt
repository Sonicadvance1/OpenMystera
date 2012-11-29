set(SRCS	SRC/client.cpp
		SRC/net.cpp
		SRC/Graphics/SDL_OGL.cpp
)
#Don't have any of these yet


include(FindOpenGL)
include(FindPNG)
include_directories(${OPENGL_INCLUDE_DIR}, ${PNG_INCLUDE_DIR}, "INCLUDE")

set(LIBS
	SDL 
	SDL_mixer
	SDL_net	
	png	
	GL
	)

set(CLIENT Client)

add_executable(${CLIENT} ${SRCS})
target_link_libraries(${CLIENT} ${LIBS})
install(TARGETS ${CLIENT} RUNTIME DESTINATION ${bindir})
