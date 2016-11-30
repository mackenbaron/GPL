#查找路径下面所有源文件
SET(SRC_LIST log.cpp logging.cc raw_logging.cc utilities.cc vlog_is_on.cc ${CMAKE_CURRENT_SOURCE_DIR}/windows/port.cc)
#添加引用目录
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/base ${CMAKE_CURRENT_SOURCE_DIR}/glog ${CMAKE_CURRENT_SOURCE_DIR}/windows)
#添加自定义预处理
ADD_DEFINITIONS(-DGOOGLE_GLOG_DLL_DECL=)
#生成不同的target
if(CMAKE_CL_64)
	set(target  liblogx64)
else()
	set(target liblog)
endif()
#设置静态库
ADD_LIBRARY(${target} STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inc
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/log.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/log)



