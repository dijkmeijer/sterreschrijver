cmake_minimum_required (VERSION 2.8.11)
project (novasextra)
include_directories(../Novas_C3.1)
add_library(novasextra STATIC Novasextra.c)
