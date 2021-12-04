# Microsoft Developer Studio Project File - Name="src_from_PNG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Generic Project" 0x010a

CFG=src_from_PNG - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "src_from_PNG.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "src_from_PNG.mak" CFG="src_from_PNG - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "src_from_PNG - Win32 Release" (based on "Win32 (x86) Generic Project")
!MESSAGE "src_from_PNG - Win32 Debug" (based on "Win32 (x86) Generic Project")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
MTL=midl.exe

!IF  "$(CFG)" == "src_from_PNG - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "src_from_PNG___Win32_Release"
# PROP BASE Intermediate_Dir "src_from_PNG___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release\obj"
# PROP Intermediate_Dir "Release\obj\src_from_png"
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "src_from_PNG - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "src_from_PNG___Win32_Debug"
# PROP BASE Intermediate_Dir "src_from_PNG___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "src_from_PNG - Win32 Release"
# Name "src_from_PNG - Win32 Debug"
# Begin Source File

SOURCE=..\abi\src\wp\ap\xp\sidebar.png

!IF  "$(CFG)" == "src_from_PNG - Win32 Release"

# PROP Intermediate_Dir "Release"
# Begin Custom Build - Creating src file from $(InputPath)
InputPath=..\abi\src\wp\ap\xp\sidebar.png

".\ap_wp_sidebar.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	.\Release\tools_cdump\cdump.exe $(InputPath) g_pngSidebar > ./ap_wp_sidebar.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "src_from_PNG - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# Begin Custom Build - Creating src file from $(InputPath)
InputPath=..\abi\src\wp\ap\xp\sidebar.png

".\ap_wp_sidebar.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	.\Debug\tools_cdump\cdump.exe $(InputPath) g_pngSidebar > .\ap_wp_sidebar.cpp

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\abi\src\wp\ap\xp\splash.png

!IF  "$(CFG)" == "src_from_PNG - Win32 Release"

# PROP Intermediate_Dir "Release"
# Begin Custom Build - Creating src file from $(InputPath)
InputPath=..\abi\src\wp\ap\xp\splash.png

".\ap_wp_splash.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	.\Release\tools_cdump\cdump.exe $(InputPath) g_pngSplash > ./ap_wp_splash.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "src_from_PNG - Win32 Debug"

# PROP Intermediate_Dir "Debug"
# Begin Custom Build - Creating src file from $(InputPath)
InputPath=..\abi\src\wp\ap\xp\splash.png

".\ap_wp_splash.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	.\Debug\tools_cdump\cdump.exe $(InputPath) g_pngSplash > .\ap_wp_splash.cpp

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
