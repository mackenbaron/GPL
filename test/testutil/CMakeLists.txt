#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#引用头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc/util)
#引用库目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/out/lib)

#生成exe文件
ADD_EXECUTABLE(TestUtile ${SRC_LIST})
#生成不同的lib
if(CMAKE_CL_64)
	set(inputlib libutilx64)
else()
	set(inputlib libutil)
endif()

#添加库
TARGET_LINK_LIBRARIES(TestUtile ${inputlib})
#设置预编译
SET_TARGET_PROPERTIES(TestUtile PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(TestUtile)
#设置目录
SET_TARGET_PROPERTIES(TestUtile PROPERTIES FOLDER "Test")
#设置输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)




