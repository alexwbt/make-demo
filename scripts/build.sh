#! /bin/sh

# configure
cmake \
    -DGLFW_BUILD_DOCS=OFF \
    -B ./_build

# build
cd ./_build
make
