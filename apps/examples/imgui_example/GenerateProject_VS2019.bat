mkdir build
pushd .\build
cmake .. -G"Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Debug -DPLUGINS_DYNAMIC=ON
popd