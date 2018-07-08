# IBM Developer's Workframe/2 Make File Creation run at 17:29:50 on 01/29/94

# Make File Creation run in directory:
#   D:\PROJ\DDF;

.SUFFIXES:

.SUFFIXES: .c .cpp .cxx .ipf

ALL: HELP.EXE \
     help.HLP

HELP.EXE:  \
  help.OBJ \
  helpddf.OBJ \
  HELP.MAK
   ICC.EXE @<<
 /B" /de /pmtype:pm"
 /Fe"HELP.EXE" 
help.OBJ 
helpddf.OBJ
<<

{.}.ipf.hlp:
   IPFC .\$*.IPF

{.}.c.obj:
   ICC.EXE /Ss /Q /Ti /Gs /Ft- /C   .\$*.c

{.}.cpp.obj:
   ICC.EXE /Ss /Q /Ti /Gs /Ft- /C   .\$*.cpp

{.}.cxx.obj:
   ICC.EXE /Ss /Q /Ti /Gs /Ft- /C   .\$*.cxx

!include HELP.DEP
