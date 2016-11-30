#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#添加引用目录
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/Algorithms)
#添加自定义预处理
ADD_DEFINITIONS(-DLIB_FILE_VERIFY)
#生成不同的target
if(CMAKE_CL_64)
	set(target  libutilx64)
else()
	set(target libutil)
endif()
#设置静态库
ADD_LIBRARY(${target} STATIC ${SRC_LIST})
#设置预编译
SET_TARGET_PROPERTIES(${target} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(${target})
#设置目录
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inchhvi
INSTALL(FILES util.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/util)



