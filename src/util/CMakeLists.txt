#查找路径下面所有源文件
AUX_SOURCE_DIRECTORY(. SRC_LIST)
#设置静态库
ADD_LIBRARY(util_static STATIC ${SRC_LIST})
#设置预编译
set_target_properties(util_static PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(util_static)
#设置目录
SET_TARGET_PROPERTIES(util_static PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)



