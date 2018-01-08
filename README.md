# README (Ubuntu)

Prepare environment

* Install CLion IDE
* Install dependence libraries

Qt Create with Qt libraries

```
sudo apt-get install \
    qtcreator \
    qtbase5-dev
```

Tested on qt 5.5.1

* Install cmake 3.10

```
cd /tmp
wget https://cmake.org/files/v3.10/cmake-3.10.1.tar.gz
tar -xvzf cmake-3.10.1.tar.gz
cd cmake-3.10.1/
sudo ./bootstrap
sudo make
sudo make install

```

* Install OpenGL

```
sudo apt-get install \
    libgl1-mesa-dev \
    libglu1-mesa \
    libglu1-mesa-dev \
    freeglut3-dev \
    binutils-gold \
    libglu1-mesa:i386
```