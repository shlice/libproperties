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

/**
*
* ����java�е���Properties����xml�ļ���ʽһ�¡�
* we give a c++ class as is class "Properties" in java
* And they can use the xml file each other.
* The lib have only one class, so You can use the lib
* very simple.
*
* Authors: harite  Harite.K@gmail.com
* DataTime: 2007/10/03
* Project: http://code.google.com/p/libproperties
*/

#include <map>
#include <string>

using std::map;
using std::string;

/*
 * ʵ����tinyxml2.4.3���߳��ǲ���ȫ��
*/
// tinyxml2.4.3 is NOT thread safe in fact, so ...
//#define WIN32_THREAD_SAFE
/*
#ifdef WIN32_THREAD_SAFE
#include <windows.h>
#endif
*/

//�����Ҫ�����dll��ʹ��ʱ��Ҫһ��������lib
/*
 if you want a dll in win32, this macro can help you.
 it will create a dll and its export lib.
*/
#ifdef LIBPROPERTIES_BUILDING_DLL

#include <windows.h>
#define LIBPROPERTIES_DLLIMPORT __declspec (dllexport)

#else /* Not DLL */

#define LIBPROPERTIES_DLLIMPORT __declspec (dllimport)

#endif

// ʹ��stl
// use the stl for tinyxml
#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif

#include "tinyxml.h"
#include "libproperties_tinyxml_ext.h"

// ����
// just for debug
//#define DEBUG_PROPERTIES_H

#ifdef DEBUG_PROPERTIES_H
#include <iostream>
#endif

using namespace std;

/*
 libproperties�����ʹ�õ�ֻ��Properties��
 ��ˣ�����Ժܼ򵥵�ʹ������
 The libproperties has only one class, so You can use the lib
 very simple.
*/
class LIBPROPERTIES_DLLIMPORT Properties
{
public:

	typedef map<string, string>::iterator iterator;
	typedef map<string, string>::const_iterator const_iterator;

	Properties(void)
	{
		/*
		#ifdef WIN32_THREAD_SAFE
	    InitializeCriticalSection(&CriticalSection);
        #endif
		*/
	}

	virtual ~Properties(void)
	{
		/*
		#ifdef WIN32_THREAD_SAFE
	    DeleteCriticalSection(&CriticalSection);
        #endif
		*/
	}

	/**
	* ����һ��������ֵ����,�����Ѿ����������滻����ֵ
	* set a "key-value" pair, if the key exist, update its value
	* @param key Ҫ���õļ� the key to set
	* @param value Ҫ���õ�ֵ the value to set
	*/
	inline void setProperty(string key, string value)
	{
		iterator it = key_value.find(key);
		/*
		#ifdef WIN32_THREAD_SAFE
		EnterCriticalSection(&CriticalSection);
        #endif
		*/
		if(it!=key_value.end())//�����Ѿ����ڵ�
		{
			(*it).second = value;
		}
		else
		{
			key_value[key] = value;
		}
		/*
		#ifdef WIN32_THREAD_SAFE
		LeaveCriticalSection(&CriticalSection);
        #endif
		*/
	}

	/**
	* ��ȡһ������ֵ����������ڣ�����Ĭ��ֵdefaultvalue
	* get value of a key, if the key is inexistence then return default value
	* @param key ��Ҫ���ֵ�ļ� the key of you want value
	* @param defaultvalue ������������򷵻ش˲��� the defaultvalue
	* @return �������ڣ��������Ӧ��ֵ���������ڣ�����defaultvalue
	*/
	inline string getProperty(string key, string defaultvalue) const
	{
		const_iterator it = key_value.find(key);
		if(it==key_value.end())
		{
			return defaultvalue;
		}
		else
		{
			return (*it).second;
		}
	}

	/**
	* ��xml�ļ��ж�ȡ������ֵ���� load "key-value" from xml file
	* @param filename ��ȡ��xml�ļ��������ǰ��չ涨�ĸ�ʽ
	* @return ����ֵ ��ȡ�ɹ����
	*/
	inline bool loadFromXML(const string filename)
	{
		TiXmlDocument doc(filename.c_str());
		bool loadOkay = doc.LoadFile();//��utf-8��ʽ��ȡxml�ļ�
		if (!loadOkay)
		{
			return false;
		}
		TiXmlNode *node = doc.FirstChild("properties");
        #ifdef DEBUG_PROPERTIES_H
		node->Print(stdout, 1);
		cout << endl;
        #endif
		TiXmlElement* propertiesElement = node->ToElement();
		for(TiXmlElement *it = propertiesElement->FirstChildElement("entry")
			; it!=NULL ;
			it = it->NextSiblingElement("entry")
			)
		{
			TiXmlAttribute *att = it->FirstAttribute();
			this->setProperty(att->Value(), it->GetText());
			#ifdef DEBUG_PROPERTIES_H
			cout << "[" << att->Name() << ":" << att->Value() << "->" << it->GetText() << "]" << endl;
            #endif
		}
		return true;
	}

	/**
	* ����ֵ�԰�������java��Properties���xml��ʽ�洢 store "key-value" to xml file
	* @param filename Ҫ�����xml�ļ���
	* @return ����ֵ,�������ִ�гɹ����
	*/
	inline bool storeToXML(const string filename) const
	{
		TiXmlDocument doc;
		
		TiXmlDeclarationWithoutStandalone *decl = 
			new TiXmlDeclarationWithoutStandalone("1.0", "UTF-8");
		doc.LinkEndChild(decl);

		TiXmlDoctype *doctype = new TiXmlDoctype();
		doctype->SetValue("properties SYSTEM \"http://java.sun.com/dtd/properties.dtd\"");
		doc.LinkEndChild(doctype);
		
		TiXmlComment *comment1 = new TiXmlComment();
		comment1->SetValue("This file is created by libproperties");
		doc.LinkEndChild(comment1);
		
		TiXmlComment *comment2 = new TiXmlComment();
		comment2->SetValue("read more from http://code.google.com/p/libproperties");
		doc.LinkEndChild(comment2);

		TiXmlElement *propertiesElement = new TiXmlElement("properties");
		doc.LinkEndChild(propertiesElement);
 
		for (Properties::const_iterator it = key_value.begin()
			; it!=key_value.end() ;
			++it
			)
		{
			TiXmlElement *entryElement = new TiXmlElement("entry");
			entryElement->LinkEndChild(new TiXmlText((*it).second));
			#ifdef DEBUG_PROPERTIES_H
		    propertiesElement->Print(stdout, 1);
		    cout << endl;
            #endif
			propertiesElement->LinkEndChild(entryElement);
			entryElement->SetAttribute("key", (*it).first);
		}
		
		bool result = doc.SaveFile(filename);
		doc.Clear();
		return result;
	}

	/**
	* ��ռ�ֵ�� clear "key-value"
	*/
	inline void clear()
	{
		/*
		#ifdef WIN32_THREAD_SAFE
		EnterCriticalSection(&CriticalSection);
        #endif
		*/
		key_value.clear();
		/*
		#ifdef WIN32_THREAD_SAFE
		LeaveCriticalSection(&CriticalSection);
        #endif
		*/
	}

	/**
	* ����ָ���һ�Լ�ֵ��iterator
	* return the const_iterator of first "key-value" pair
	*/
	inline const_iterator begin() const
	{
		return key_value.begin();
	}

	/**
	* ����ָ�����һ�Լ�ֵ֮���iterator
	* return the next const_iterator of end "key-value" pair
	*/
	inline const_iterator end() const
	{
		return key_value.end();
	}

private:
	/**
	* stl�е�map��ʢ�ż�ֵ��
	*/
	map<string, string> key_value;

	/**
	* �ٽ���
	*/
	/*
	#ifdef WIN32_THREAD_SAFE
	CRITICAL_SECTION CriticalSection;
    #endif
	*/
};

#endif

