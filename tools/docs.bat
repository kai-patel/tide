cd %~dp0
cd ..

if exist build\ (
    cd build
    make docs
)
