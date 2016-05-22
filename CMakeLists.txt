# CMake 最低版本号要求
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
#设置项目名字
PROJECT(GPL)
#设置配置
set(VERSION "0.1")
#设置项目目录化
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")
#设置if
set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
#设置模块化路径
if (POLICY CMP0058)
	# Ninja requires custom command byproducts to be explicit
	cmake_policy(SET CMP0058 NEW)
endif()
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
#设置预处理器
include(cotire)
#加入src目录
add_subdirectory(src)
#加入test目录
add_subdirectory(test)



