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

//�����Ҫ�����dll��ʹ��ʱ��Ҫһ��������lib
//������dll��ʱ����˺�
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
* ����java�е���Properties����xml�ļ���ʽһ�¡�
* libproperties�����ʹ�õ�ֻ��Properties��.��ˣ�����Ժܼ򵥵�ʹ������
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
*        1.��ϵͳ����win32��ʱ���޸ĺ�LIBPROPERTIES_DLLIMPORTΪ��
*        2.����Ҫ����ʵ�ַ���cppԴ�ļ��У���ͷ�ļ�ֻ������򵥵Ľӿ�������
*/

class LIBPROPERTIES_DLLIMPORT Properties
{
public:

	typedef map<string, string>::iterator iterator;
	typedef map<string, string>::const_iterator const_iterator;

	Properties(void){}

	virtual ~Properties(void){}

	/**
	* ����һ��������ֵ����,�����Ѿ����������滻����ֵ
	* set a "key-value" pair, if the key exist, update its value
	* @param key Ҫ���õļ� the key to set
	* @param value Ҫ���õ�ֵ the value to set
	*/
	inline void setProperty(string key, string value);

	/**
	* ��ȡһ������ֵ����������ڣ�����Ĭ��ֵdefaultvalue
	* get value of a key, if the key is inexistence then return default value
	* @param key ��Ҫ���ֵ�ļ� the key of you want value
	* @param defaultvalue ������������򷵻ش˲��� the defaultvalue
	* @return �������ڣ��������Ӧ��ֵ���������ڣ�����defaultvalue
	*/
	inline string getProperty(string key, string defaultvalue) const;

	/**
	* ��xml�ļ��ж�ȡ������ֵ���� load "key-value" from xml file
	* @param filename ��ȡ��xml�ļ��������ǰ��չ涨�ĸ�ʽ
	* @return ����ֵ ��ȡ�ɹ����
	*/
	inline bool loadFromXML(const string filename);

	/**
	* ����ֵ�԰�������java��Properties���xml��ʽ�洢 store "key-value" to xml file
	* @param filename Ҫ�����xml�ļ���
	* @return ����ֵ,�������ִ�гɹ����
	*/
	inline bool storeToXML(const string filename) const;

	/**
	* ��ռ�ֵ�� clear "key-value"
	*/
	inline void clear() { key_value.clear(); }

	/**
	* ����ָ���һ�Լ�ֵ��const_iterator
	* return the const_iterator of first "key-value" pair
	*/
	inline const_iterator begin() const { return key_value.begin(); }
    
    /**
	* ����ָ���һ�Լ�ֵ��iterator
	* return the const_iterator of first "key-value" pair
	*/
    // Modified by harite Date:2007/10/07
    // ��Ȼ�����ṩ���㣬Ϊʲô����
	inline iterator begin() { return key_value.begin(); }

	/**
	* ����ָ�����һ�Լ�ֵ֮���const_iterator
	* return the next const_iterator of end "key-value" pair
	*/
	inline const_iterator end() const { return key_value.end(); }
    
    /**
	* ����ָ�����һ�Լ�ֵ֮���iterator
	* return the next const_iterator of end "key-value" pair
	*/
    // Modified by harite Date:2007/10/07
    // ��Ȼ�����ṩ���㣬Ϊʲô����
	inline iterator end() { return key_value.end(); }

private:
	/**
	* stl�е�map��ʢ�ż�ֵ��
	*/
	map<string, string> key_value;

};

#endif

