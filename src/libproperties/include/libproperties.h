/*
  Project: libproperties
  Written by harite
  mailto:Harite.K@gmail.com
  date:2007/10/05
  libproperties's homepage:
    http://code.google.com/p/libproperties

  libproperties is released under the zlib license:

This software is provided 'as-is', without any express or implied 
warranty. In no event will the authors be held liable for any 
damages arising from the use of this software.

Permission is granted to anyone to use this software for any 
purpose, including commercial applications, and to alter it and 
redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must 
not claim that you wrote the original software. If you use this 
software in a product, an acknowledgment in the product documentation 
would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and 
must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source 
distribution.

*/

#ifndef LIBPROPERTIES_H
#define LIBPROPERTIES_H

#include <map>
#include <string>

using std::map;
using std::string;

//如果想要编译成dll，使用时需要一个导出库lib
//当生成dll库时定义此宏
/*
 if you want a dll in win32, this macro can help you.
 it will create a dll and its export lib.
*/
#ifdef LIBPROPERTIES_BUILDING_DLL

#include <windows.h>
#define LIBPROPERTIES_DLLIMPORT __declspec (dllexport)

#else /* Not DLL */

#define LIBPROPERTIES_DLLIMPORT
//Unix-like OS don't know this
//__declspec (dllimport)

#endif

class TiXmlDeclaration;
class TiXmlComment;
class TiXmlDoctype;
class TiXmlDeclarationWithoutStandalone;

/**
*
* 类似java中的类Properties，其xml文件格式一致。
* libproperties供外界使用的只有Properties类.因此，你可以很简单的使用它。
* we give a c++ class as is class "Properties" in java
* And they can use the xml file each other.
* The lib have only one class, so You can use the lib
* very simple.
*
* Authors: harite  Harite.K@gmail.com
* Date: 2007/10/05
* Project: http://code.google.com/p/libproperties
*
*   Date:2007/10/06   Modified by harite
*        1.当系统不在win32下时，修改宏LIBPROPERTIES_DLLIMPORT为空
*        2.将主要函数实现放入cpp源文件中，此头文件只留下最简单的接口声明。
*/

class LIBPROPERTIES_DLLIMPORT Properties
{
public:

	typedef map<string, string>::iterator iterator;
	typedef map<string, string>::const_iterator const_iterator;

	Properties(void){}

	virtual ~Properties(void){}

	/**
	* 设置一个“键－值”对,若键已经存在则将其替换成新值
	* set a "key-value" pair, if the key exist, update its value
	* @param key 要设置的键 the key to set
	* @param value 要设置的值 the value to set
	*/
	inline void setProperty(string key, string value);

	/**
	* 读取一个键的值，如果不存在，返回默认值defaultvalue
	* get value of a key, if the key is inexistence then return default value
	* @param key 想要获得值的键 the key of you want value
	* @param defaultvalue 如果键不存在则返回此参数 the defaultvalue
	* @return 若键存在，返回其对应的值；若不存在，返回defaultvalue
	*/
	inline string getProperty(string key, string defaultvalue) const;

	/**
	* 从xml文件中读取“键－值”对 load "key-value" from xml file
	* @param filename 读取的xml文件，必须是按照规定的格式
	* @return 布尔值 读取成功与否
	*/
	inline bool loadFromXML(const string filename);

	/**
	* 将键值对按照类似java中Properties类的xml格式存储 store "key-value" to xml file
	* @param filename 要保存的xml文件名
	* @return 布尔值,代表操作执行成功与否
	*/
	inline bool storeToXML(const string filename) const;

	/**
	* 清空键值对 clear "key-value"
	*/
	inline void clear() { key_value.clear(); }

	/**
	* 返回指向第一对键值的const_iterator
	* return the const_iterator of first "key-value" pair
	*/
	inline const_iterator begin() const { return key_value.begin(); }
    
    /**
	* 返回指向第一对键值的iterator
	* return the const_iterator of first "key-value" pair
	*/
    // Modified by harite Date:2007/10/07
    // 既然可以提供方便，为什么不！
	inline iterator begin() { return key_value.begin(); }

	/**
	* 返回指向最后一对键值之后的const_iterator
	* return the next const_iterator of end "key-value" pair
	*/
	inline const_iterator end() const { return key_value.end(); }
    
    /**
	* 返回指向最后一对键值之后的iterator
	* return the next const_iterator of end "key-value" pair
	*/
    // Modified by harite Date:2007/10/07
    // 既然可以提供方便，为什么不！
	inline iterator end() { return key_value.end(); }

private:
	/**
	* stl中的map，盛放键值对
	*/
	map<string, string> key_value;

};

#endif

