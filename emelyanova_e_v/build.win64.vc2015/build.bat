@rem set PATH="C:\Program Files\CMake\bin\";%PATH%
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat" x86

call cmake.exe -G"Visual Studio 14 Win64" -DOpenCV_DIR="R:/opencv-3.4.0-official/build" ..
msbuild polevoy_d_v.sln /property:Configuration=Debug /m
@rem msbuild polevoy_d_v.sln /property:Configuration=Release /m