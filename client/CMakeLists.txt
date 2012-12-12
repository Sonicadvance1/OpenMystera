set(SRCS	SRC/client.cpp
		SRC/Graphics/SDL_OGL.cpp
		SRC/Input/SDL.cpp
)
#Don't have any of these yet


include(FindOpenGL)
include(FindPNG)
include_directories(${OPENGL_INCLUDE_DIR}, ${PNG_INCLUDE_DIR}, "INCLUDE", "../common/Include")

set(LIBS
	common
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
