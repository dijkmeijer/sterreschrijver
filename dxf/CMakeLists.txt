cmake_minimum_required (VERSION 2.8.11)
project (dl_dxf)

add_library( dl_dxf STATIC dl_dxf.cpp dl_writer_ascii.cpp )
