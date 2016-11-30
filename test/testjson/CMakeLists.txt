#查找路径下面所有源文件
#AUX_SOURCE_DIRECTORY(. SRC_LIST)
SET(SRC_LIST main.cpp stdafx.cpp)
#引用头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc/json ${PROJECT_SOURCE_DIR}/inc/util)
#引用库目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/out/lib)

#设置c++编译器
#ADD_DEFINITIONS(-TP)

#生成不同的lib
if(CMAKE_CL_64)
	set(inputlib  libjsonx64 libutilx64)
else()
	set(inputlib libjson libutil)
endif()


#生成exe文件
ADD_EXECUTABLE(TestJson ${SRC_LIST})
#添加库
TARGET_LINK_LIBRARIES(TestJson ${inputlib})
#设置预编译
SET_TARGET_PROPERTIES(TestJson PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(TestJson)
#设置目录
SET_TARGET_PROPERTIES(TestJson PROPERTIES FOLDER "Test")
#设置输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)




