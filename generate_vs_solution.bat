@echo OFF

set BUILDTYPE=%1
if "%BUILDTYPE%" EQU "" (
 set BUILDTYPE=Debug
)

set "res=" 
if "%BUILDTYPE%" EQU "Debug" set res=true
if "%BUILDTYPE%" EQU "Release" set res=true

if not defined res ( 
echo There is no such build type %BUILDTYPE%  
pause
goto end
)

rd /q /s build
mkdir build
cd build
echo Build type: %BUILDTYPE%  
cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_BUILD_TYPE=%BUILDTYPE% -DCMAKE_CONFIGURATION_TYPES=%BUILDTYPE%

::call %BUILDTOOLS%
::msbuild HumanMachineInterface.sln /property:Configuration=%BUILDTYPE%

cd ..

:end
