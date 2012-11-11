# Microsoft Developer Studio Project File - Name="mlserver" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=mlserver - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mlserver.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mlserver.mak" CFG="mlserver - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mlserver - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mlserver - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mlserver - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "BUILD\INCLUDE" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"BUILD\LIB"

!ELSEIF  "$(CFG)" == "mlserver - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "BUILD\INCLUDE" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"BUILD\LIB"

!ENDIF 

# Begin Target

# Name "mlserver - Win32 Release"
# Name "mlserver - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BUILD\SRC\consoleport.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\gameserver.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\gs_commands.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\gs_messages.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\gs_mhandler.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\gs_players.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\mlserver.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\mysql_db.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\net.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\script_system.cpp
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\SDLnet.c
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\SDLnetselect.c
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\SDLnetTCP.c
# End Source File
# Begin Source File

SOURCE=.\BUILD\SRC\SDLnetUDP.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BUILD\INCLUDE\begin_code.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\censor.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\close_code.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\console.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\consoleport.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\gamedefs.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\gameserver.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\list.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\md5.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\mysql_db.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\net.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\nethandler_unused.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\netstructs.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\portdir.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\resource.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\script_commands.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\script_system.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_active.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_audio.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_byteorder.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_cdrom.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_endian.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_error.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_events.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_getenv.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_joystick.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_keyboard.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_keysym.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_main.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_mixer.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_mouse.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_mutex.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_net.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_net_new.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_quit.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_rwops.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_thread.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_timer.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_types.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_version.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDL_video.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\SDLnetsys.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\utils.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\zconf.h
# End Source File
# Begin Source File

SOURCE=.\BUILD\INCLUDE\zlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
