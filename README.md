# GTK3 Tutorial
在 Linux 上用 GTK3 創建 GUI app
* Why GTK3 ? 
    * GTK3 (適合 Embedded) 
    * GTK4 (GPU 加速（GSK Renderer）

# 設定環境
## Clone GTK3
```
$ git clone git@github.com:GNOME/gtk.git gtk3
$ cd gtk3
$ git checkout gtk-3-24

$ git branch
* gtk-3-24
```
## Install packages
```
$ sudo apt install libgtk-3-dev
# Test pkg-config
pkg-config --cflags gtk+-3.0
pkg-config --libs gtk+-3.0
```
## For  Makefile application
```
$ cd application1
$ make -f Makefile.example

# execute 
$ ./exampleapp
```
## For Meson application
### Install meson
```
$ sudo apt install meson
```
### Fix meson.build
```
project('exampleapp', 'c')
libgtk_dep = dependency('gtk4')
libgtk_dep = dependency('gtk+-3.0')
```
### Compile meson
```
$ meson setup build
# meson compile -C build
$ ./build/exampleapp
```
# Tutorial 
[Lessons](./GTK3-Tutorial.md) 

# desktop reference
[Desktop](./KB-desktop.md)

# Resources
[Getting Start](https://docs.gtk.org/gtk3/getting_started.html)

