cd %~dp0
cd ..

if exist build\ (
    rmdir /S /Q "build"
)

mkdir build
cmake -S . -B build -G"Unix Makefiles" -DBUILD_TESTS=1 -DBOOST_ROOT="C:/Program Files/boost/boost_1_82_0"
cmake --build build

