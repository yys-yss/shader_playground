call vcvarsall.bat x64
set arg1=%1
cd cmake_files
cmake -DCMAKE_BUILD_TYPE=%arg1% .. 
cmake --build . -j8
cd ..