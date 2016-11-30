#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#设置c++编译器
ADD_DEFINITIONS(-DUNICODE -D_UNICODE)
#添加引用目录
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} $ENV{OPENSSL_ROOT_DIR}/include ${PROJECT_SOURCE_DIR}/src/xml ${PROJECT_SOURCE_DIR}/src/xml/iconv)
#生成不同的target
if(CMAKE_CL_64)
	set(target  libSocketsx64)
else()
	set(target libSockets)
endif()
#设置静态库
ADD_LIBRARY(${target} STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inc/sockets
file(GLOB sockets_hdrs "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${sockets_hdrs} DESTINATION ${PROJECT_SOURCE_DIR}/inc/sockets)



