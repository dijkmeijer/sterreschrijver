cmake_minimum_required (VERSION 2.8.11)
project (novas)

add_library(novas STATIC novas.c readeph0.c solsys1.c nutation.c novascon.c eph_manager.c cio_file.c)