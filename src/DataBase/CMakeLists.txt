#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#设置c++编译器
#ADD_DEFINITIONS(-TP)
#引入目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/inc/util)
#生成不同的target
if(CMAKE_CL_64)
	set(target  libDBx64)
else()
	set(target libDB)
endif()

#设置静态库
ADD_LIBRARY(${target} STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inchhvi
INSTALL(FILES DB.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/DB)



