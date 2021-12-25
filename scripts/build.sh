#! /bin/sh

cmake \
    -DGLFW_BUILD_DOCS=OFF \
    -B ./_build

cd ./_build
make
