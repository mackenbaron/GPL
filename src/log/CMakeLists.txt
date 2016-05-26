#查找路径下面所有源文件
#AUX_SOURCE_DIRECTORY(. SRC_LIST)
SET(SRC_LIST logging.cc raw_logging.cc utilities.cc vlog_is_on.cc ${CMAKE_CURRENT_SOURCE_DIR}/windows/port.cc)
#添加引用目录
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/base ${CMAKE_CURRENT_SOURCE_DIR}/glog ${CMAKE_CURRENT_SOURCE_DIR}/windows)
#添加自定义预处理
ADD_DEFINITIONS(-DGOOGLE_GLOG_DLL_DECL=)
#设置静态库
ADD_LIBRARY(liblog STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(liblog PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inchhvi
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/windows/glog/log_severity.h ${CMAKE_CURRENT_SOURCE_DIR}/windows/glog/logging.h ${CMAKE_CURRENT_SOURCE_DIR}/windows/glog/raw_logging.h ${CMAKE_CURRENT_SOURCE_DIR}/windows/glog/stl_logging.h ${CMAKE_CURRENT_SOURCE_DIR}/windows/glog/vlog_is_on.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/glog)



