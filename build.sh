rm -rf bin
mkdir build
mkdir bin
cd build
cmake ..
make
cd ..
cp -r res/ bin/
