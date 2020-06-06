## Note: prerequisites - install libgd

cd ..
mkdir gd
cd gd
git clone https://github.com/libgd/libgd.git
cd ./libgd
./bootstrap.sh
./configure
make
sudo make install

## my code

## possible needs adjust Makefile LIB  INCLUDE

cd ..
cd ./world3d
./configure
make

## how to use - check ./www
