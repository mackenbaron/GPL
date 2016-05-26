#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#设置c++编译器
#ADD_DEFINITIONS(-TP)
#设置静态库
ADD_LIBRARY(libjson STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(libjson PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inchhvi
INSTALL(FILES json.h debug.h linkhash.h arraylist.h json_util.h json_object.h json_tokener.h json_object_iterator.h json_c_version.h json_inttypes.h json_config.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/json)



