# README

## Qt5 instalation

```bash
wget wget http://download.qt.io/official_releases/qt/5.7/5.7.0/qt-opensource-linux-x64-5.7.0.run

chmod +x qt-opensource-linux-x64-5.7.0.run

./qt-opensource-linux-x64-5.7.0.run

sudo apt-get install \
    build-essential \
    libfontconfig1 \
    mesa-common-dev \
    libglu1-mesa-dev
```

## Qt Configure

1. Set path to Qt source in .env file like `CMAKE_PREFIX_PATH=/opt/Qt5.7.0/5.7/gcc_64`
