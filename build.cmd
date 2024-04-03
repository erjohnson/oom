@echo off

cls

set ROOT_DIR=%cd%
if not exist _build mkdir _build

rem set COMMON_COMPILER_FLAGS=/nologo /EHa- /GR- /fp:fast /Oi /W4 /Fm

set COMMON_FLAGS=/nologo /Oi /W4 /std:c17 /GR- /EHs- /D_CRT_SECURE_NO_WARNINGS
set DEBUG_FLAGS=/D_DEBUG /DDEBUG_BUILD /Od /MTd /Zi
set RELEASE_FLAGS =/O2

set COMPILE_FLAGS=%COMMON_FLAGS% %DEBUG_FLAGS%
REM set COMPILER_FLAGS=%COMMON_COMPILER_FLAGS% %RELEASE_FLAGS%

set LINK_FLAGS=/DEBUG:FULL /INCREMENTAL:NO /OPT:REF
rem set SYSTEM_LIBS=user32.lib gdi32.lib winmm.lib d3d11.lib d3dcompiler.lib

pushd _build
	cl %COMPILE_FLAGS% %ROOT_DIR%\main_windows.c /link %LINK_FLAGS%
popd
