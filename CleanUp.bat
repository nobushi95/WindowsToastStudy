@echo off
echo delete obj
for /R %%d in (obj) do ( if exist "%%d" (rmdir /S /Q "%%d" ) )

echo delete bin
for /R %%d in (bin) do ( if exist "%%d" (rmdir /S /Q "%%d" ) )

echo delete Debug
for /R %%d in (Debug) do ( if exist "%%d" (rmdir /S /Q "%%d" ) )

echo delete Release
for /R %%d in (Release) do ( if exist "%%d" (rmdir /S /Q "%%d" ) )

@REM echo delete .vs
@REM for /R %%d in (.vs) do ( if exist "%%d" ( rmdir /S /Q "%%d" ) )

pause
