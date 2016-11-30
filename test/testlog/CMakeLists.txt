#查找路径下面所有源文件
#AUX_SOURCE_DIRECTORY(. SRC_LIST)
SET(SRC_LIST main.cpp stdafx.cpp)
#引用头文件目录
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/inc/util ${PROJECT_SOURCE_DIR}/inc/log)

#引用库目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/out/lib)
#添加自定义预处理
ADD_DEFINITIONS(-DGOOGLE_GLOG_DLL_DECL=)
#生成exe文件
ADD_EXECUTABLE(TestLog ${SRC_LIST})
#生成不同的lib
if(CMAKE_CL_64)
	set(inputlib  liblogx64 libutilx64)
else()
	set(inputlib liblog libutil)
endif()

#添加库
TARGET_LINK_LIBRARIES(TestLog ${inputlib})
#设置预编译
SET_TARGET_PROPERTIES(TestLog PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(TestLog)
#设置目录
SET_TARGET_PROPERTIES(TestLog PROPERTIES FOLDER "Test")
#设置输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)




