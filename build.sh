#!/bin/sh

NAME="$1"

set -xe

CFLAGS="-Wall -Wextra"
LIBS="/usr/src/glad.c ./inc/shader/shader.c ./inc/object/object.c -ldl -lglfw -lGL"

gcc $CFLAGS -o $NAME $NAME.c $LIBS
