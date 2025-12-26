#! /bin/sh

gcc main.c -o ui_app $(pkg-config --cflags --libs gtk+-3.0)

./ui_app

