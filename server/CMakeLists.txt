set(SRCS	SRC/mlserver.cpp 
		SRC/gameserver.cpp 
		SRC/gs_players.cpp 
		SRC/gs_commands.cpp 
		SRC/gs_messages.cpp 
		SRC/gs_mhandler.cpp 
		SRC/script_commands.cpp 
		SRC/script_system.cpp 
		SRC/mysql_db.cpp 
		SRC/net.cpp 
		SRC/md5.cpp 
		SRC/utils.cpp
		SRC/consoleport.cpp
		SRC/sqlite3.c
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
	)

set(SERVER Server)

add_executable(${SERVER} ${SRCS})
target_link_libraries(${SERVER} ${LIBS})
install(TARGETS ${SERVER} RUNTIME DESTINATION ${bindir})
