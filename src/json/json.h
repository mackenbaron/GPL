#pragma once
/**
	*  Copyright (c) 2016, DayBreak(https://github.com/DayBreakZhang)
	*  All rights reserved.
	*
	*  @file        json.h
	*  @author      DayBreakZhang(a365316465@gmail.com)
	*  @date        2016/06/17 15:30
	*
	*  @brief       c++分析json库
	*  @note        对json的操作，读，写，校验，序列化等操作
	*
	*  @version
	*    - v1.0    2016/06/17 15:30    DayBreakZhang    0.1
	*  @todo	    无
	*/
namespace gpl
{
	/**
		*  @author      DayBreakZhang(a365316465@gmail.com)
		*  @date        2016/06/17 15:35
		*  @class       json
		*  @brief       对josn操作的封装
		*  @note		json的格式详解
		- json的详解地址：
		- 1. http://www.json.org/json-zh.html json详解
		- 2. https://www.reddit.com/  json网站
		- 3. https://api.reddit.com/ json测试数据\n
		json格式详解
		*  @code
		JSON(JavaScript Object Notation) 是一种轻量级的数据交换格式。 易于人阅读和编写。同时也易于机器解析和生成。 它基于JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999的一个子集。 JSON采用完全独立于语言的文本格式，但是也使用了类似于C语言家族的习惯（包括C, C++, C#, Java, JavaScript, Perl, Python等）。 这些特性使JSON成为理想的数据交换语言。
		JSON建构于两种结构：
		- 名称/值”对的集合（A collection of name/value pairs）。不同的语言中，它被理解为对象（object），纪录（record），结构（struct），字典（dictionary），哈希表（hash table），有键列表（keyed list），或者关联数组 （associative array）。
		- 值的有序列表（An ordered list of values）。在大部分语言中，它被理解为数组（array）。
		这些都是常见的数据结构。事实上大部分现代计算机语言都以某种形式支持它们。这使得一种数据格式在同样基于这些结构的编程语言之间交换成为可能。
		*  @endcode
		json常用的格式
		*  @code
		- 对象是一个无序的“‘名称/值’对”集合。一个对象以“{”（左括号）开始，“}”（右括号）结束。每个“名称”后跟一个“:”（冒号）；“‘名称/值’ 对”之间使用“,”（逗号）分隔。e.g{"hello":"word","hello1":"word1"}
		- 数组是值（value）的有序集合。一个数组以“[”（左中括号）开始，“]”（右中括号）结束。值之间使用“,”（逗号）分隔。 e.g["a":1,"b":2]
		- 值（value）可以是双引号括起来的字符串（string）、数值(number)、true、false、 null、对象（object）或者数组（array）。这些结构可以嵌套。
		- 字符串（string）是由双引号包围的任意数量Unicode字符的集合，使用反斜线转义。一个字符（character）即一个单独的字符串（character string）。
		- 字符串（string）与C或者Java的字符串非常相似。
		- 数值（number）也与C或者Java的数值非常相似。除去未曾使用的八进制与十六进制格式。除去一些编码细节。
		- 空白可以加入到任何符号之间
		*  @endcode
		*  @attention   注意
		*  @bug
		*  @warning     警告
		*/
	class json
	{
	public:
		/**
			*  @date        2016/06/17 15:51
			*  @brief       构造函数
			*/
		json();
		/**
		*  @date        2016/06/17 15:51
		*  @brief       析构函数
		*/
		virtual ~json();
		/**
			*  @date        2016/06/21 18:01
			*  @brief       解析json
			*  @param[in]   filename[string]json文件路径
			*  @param[in]   encoded[int]编码方式 - 1为Unicode编码 - 0为utf-8编码（默认）
			*  @return      成功返回true，否则为false
			*  @pre         段落
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
			*/
		bool parseJson(std::string filename,int encoded);
		/**
		*  @date        2016/06/21 18:01
		*  @brief       解析json
		*  @param[in]   jsonbuf[char*]json内存
		*  @param[in]   encoded[int]编码方式 - 1为Unicode编码 - 0为utf-8编码（默认）
		*  @return      成功返回true，否则为false
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		bool parseJson(char* jsonbuf, int encoded);
		/**
			*  @date        2016/06/21 18:02
			*  @brief       获取json数组对像的大小
			*  @param[in]   par[string]要解析数据从root开始的路径
			*  @return      返回数组大小
			*  @pre         段落
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
			*/
		int getArraySize(std::string par);
		/**
			*  @date        2016/06/21 18:04
			*  @brief       返回指定路径下面的数据
			*  @param[in]   par[string]要解析数据从root开始的路径
			*  @param[out]  date[int]返回int的数据
			*  @return      void
			*  @pre         段落
			*  @remarks     评论
			*  @see         参考内容
			*  @test        测试
			*/
		void getItemDate(int& date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       返回指定路径下面的数据
		*  @param[in]   par[string]要解析数据从root开始的路径
		*  @param[out]  date[string]返回string的数据
		*  @return      void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void getItemDate(std::string &date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       返回指定路径下面的数据
		*  @param[in]   par[string]要解析数据从root开始的路径
		*  @param[out]  date[bool]返回bool的数据
		*  @return      void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void getItemDate(bool &date, std::string par);
		/**
		*  @date        2016/06/21 18:04
		*  @brief       返回指定路径下面的数据
		*  @param[in]   par[string]要解析数据从root开始的路径
		*  @param[out]  date[double]返回double的数据
		*  @return      void
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		void getItemDate(double &date, std::string par);
	private:
		/**
		*  @date        2016/06/21 18:04
		*  @brief       读取文件数据
		*  @param[in]   filename[string]文件路径
		*  @return      文件内容，为字符类型（经过转码的)
		*  @pre         段落
		*  @remarks     评论
		*  @see         参考内容
		*  @test        测试
		*/
		std::string readFile(std::string filename);
	private:
		class LibJson;
		LibJson* m_json;
	};

}
