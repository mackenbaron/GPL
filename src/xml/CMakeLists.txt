#查找路径下面所有源文件
#AUX_SOURCE_DIRECTORY(. SRC_LIST)
SET(SRC_LIST 	buf.c 
		c14n.c 
		catalog.c
		chvalid.c
		debugXML.c
		dict.c
		DOCBparser.c
		encoding.c
		entities.c
		error.c
		globals.c
		hash.c
		HTMLparser.c
		HTMLtree.c
		legacy.c
		list.c
		nanoftp.c
		nanohttp.c
		parser.c
		parserInternals.c
		pattern.c
		relaxng.c
		SAX.c
		SAX2.c
		schematron.c
		threads.c
		tree.c
		uri.c
		valid.c
		xinclude.c
		xlink.c
		xmlcatalog.c
		xmlIO.c
		xmlmemory.c
		xmlmodule.c
		xmlreader.c
		xmlregexp.c
		xmlsave.c
		xmlschemas.c
		xmlschemastypes.c
		xmlstring.c
		xmlunicode.c
		xmlwriter.c
		xpath.c
		xpointer.c
		xzlib.c
		${CMAKE_CURRENT_SOURCE_DIR}/iconv/iconv.c
		${CMAKE_CURRENT_SOURCE_DIR}/iconv/localcharset.c
		${CMAKE_CURRENT_SOURCE_DIR}/iconv/relocatable.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/adler32.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/compress.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/crc32.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/deflate.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/gzclose.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/gzlib.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/gzread.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/gzwrite.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/infback.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/masmx64/inffas8664.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/inffast.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/inflate.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/inftrees.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/ioapi.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/trees.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/uncompr.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/unzip.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/zip.c
		${CMAKE_CURRENT_SOURCE_DIR}/zip/zutil.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/alone_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/alone_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/arm.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/armthumb.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/auto_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_buffer_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_buffer_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_header_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_header_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/block_util.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/check.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/common.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/crc32_fast.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/crc32_table.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/crc64_fast.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/crc64_table.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/delta/delta_common.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/delta/delta_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/delta/delta_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/easy_buffer_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/easy_decoder_memusage.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/easy_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/easy_encoder_memusage.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/easy_preset.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/fastpos_table.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_buffer_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_buffer_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_common.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_flags_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/filter_flags_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/hardware_cputhreads.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/hardware_physmem.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/ia64.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/index.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/index_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/index_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/index_hash.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lz/lz_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lz/lz_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lz/lz_encoder_mf.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma_encoder_optimum_fast.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma_encoder_optimum_normal.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma_encoder_presets.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma2_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma/lzma2_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/outqueue.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/powerpc.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/rangecoder/price_table.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check/sha256.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/simple_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/simple_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/sparc.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/simple_coder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_buffer_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_buffer_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_encoder_mt.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_flags_common.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_flags_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/stream_flags_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/common/tuklib_cpucores.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/common/tuklib_physmem.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/vli_decoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/vli_encoder.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common/vli_size.c
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple/x86.c
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/attribute.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/attribute_map.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/check_rules.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/child_node.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/child_node_list.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/comment.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/config_diag.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/document.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/dom_parser.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/element.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/instruction.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/libxml2_callbacks.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/libxml2_globals.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/libxml2_utility.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/node.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/node_set.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/sax_attribute_list.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/sax_error_info.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/sax_handler.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/sax_parser.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/schema.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/text.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/validity.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xml_base.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xmlns.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xpath.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xpath_context.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xpath_result.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/xtree/xpath_typed_results.cpp
		xml.cpp)
#添加引用目录
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/. 
		${CMAKE_CURRENT_SOURCE_DIR}/iconv 
		${CMAKE_CURRENT_SOURCE_DIR}/zip
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/common
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/common
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/api
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/check
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/delta
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lz
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/lzma
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/rangecoder
		${CMAKE_CURRENT_SOURCE_DIR}/lzma/liblzma/simple
		${CMAKE_CURRENT_SOURCE_DIR}/xtree)
#添加自定义预处理
ADD_DEFINITIONS(-DHAVE_CONFIG_H 
		-DENABLE_RELOCATABLE=1 
		-DIN_LIBRARY 
		-DLIBDIR=${PROJECT_SOURCE_DIR}/out/lib 
		-DINSTALLPREFIX=${PROJECT_SOURCE_DIR}/out/lib 
		-DINSTALLDIR=${PROJECT_SOURCE_DIR}/out/lib 
		-DNO_XMALLOC 
		-Dset_relocation_prefix=libiconv_set_relocation_prefix 
		-Drelocate=libiconv_relocate 
		-D_CRT_SECURE_NO_WARNINGS
		-DLZMALIB_EXPORTS
		-DCOMPRESS_MF_MT
		-DHAVE_ZLIB_H
		-DLZMALIB_EXPORTS
		-DCOMPRESS_MF_MT
		-DHAVE_CONFIG_H
		-DHAVE_LZMA_H
		-DLZMA_API_STATIC
		-DHAVE_CONFIG_H
		-DXTREE_STATIC_LIB)
#生成不同的target
if(CMAKE_CL_64)
	set(target  libxmlx64)
else()
	set(target libxml)
endif()
#设置静态库
ADD_LIBRARY(${target} STATIC ${SRC_LIST})
#设置目录
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "Util")
#设置输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib)
#复制头文件到inc
INSTALL(FILES xml.h DESTINATION ${PROJECT_SOURCE_DIR}/inc/xml)



