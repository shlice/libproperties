# Microsoft Developer Studio Project File - Name="vc6_static_lib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=vc6_static_lib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "vc6_static_lib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "vc6_static_lib.mak" CFG="vc6_static_lib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "vc6_static_lib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "vc6_static_lib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "vc6_static_lib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include ..\..\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "TIXML_USE_STL" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\vc6_static_lib_release\libproperties.lib"

!ELSEIF  "$(CFG)" == "vc6_static_lib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include ..\..\include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "TIXML_USE_STL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\vc6_static_lib_debug\libproperties.lib"

!ENDIF 

# Begin Target

# Name "vc6_static_lib - Win32 Release"
# Name "vc6_static_lib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\libproperties\libproperties.cpp
# End Source File
# Begin Source File

SOURCE=..\src\libproperties\libproperties_tinyxml_ext.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tinyxml\tinystr.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tinyxml\tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tinyxml\tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=..\src\tinyxml\tinyxmlparser.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\libproperties.h
# End Source File
# Begin Source File

SOURCE=..\include\libproperties_tinyxml_ext.h
# End Source File
# Begin Source File

SOURCE=..\include\tinystr.h
# End Source File
# Begin Source File

SOURCE=..\include\tinyxml.h
# End Source File
# End Group
# End Target
# End Project
