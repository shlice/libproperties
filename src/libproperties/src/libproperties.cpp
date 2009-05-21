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


   Modified by harite  Date:2007/10/06
         1.将一些Properties类的函数实现从头文件中移动到此处。
*/

// 让tinyxml使用stl
// use the stl for tinyxml
#ifndef TIXML_USE_STL
#define TIXML_USE_STL
#endif

#include "libproperties.h"
#include "tinyxml.h"


// 调试
// just for debug
//#define DEBUG_PROPERTIES_H

#ifdef DEBUG_PROPERTIES_H
#include <iostream>
#endif



#ifdef LIBPROPERTIES_BUILDING_DLL

BOOL APIENTRY DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{
    switch (reason)
    {
      case DLL_PROCESS_ATTACH:
        break;

      case DLL_PROCESS_DETACH:
        break;

      case DLL_THREAD_ATTACH:
        break;

      case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}

#endif


/*
 除非你想使用libproperties源码，否则不要在你的工程中引用此文件。
为了使用libproperties的库，你只需要libproperties.h头文件。
*/

/*
  
  1.add a class TiXmlDoctype extend TiXmlComment date:2007/10/04
  2.add a class TiXmlDeclarationWithoutStandalone extend TiXmlDeclaration date:2007/10/04

	Because the class "Properties" in java need
	   <!DOCTYPE properties SYSTEM "http://java.sun.com/dtd/properties.dtd">
	   in xml file, its dtd is:

	   <?xml version="1.0" encoding="UTF-8"?>
             <!-- DTD for properties -->
             <!ELEMENT properties ( comment?, entry* ) >
             <!ATTLIST properties version CDATA #FIXED "1.0">
             <!ELEMENT comment (#PCDATA) >
             <!ELEMENT entry (#PCDATA) >
             <!ATTLIST entry key CDATA #REQUIRED>

	so if i want java class Properties can use the xml file which is created by libproperties,
	i must modify tinyxml.

!!!!!!!NOTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	1.The two class is JUST written for libproperties's interface class "Properties"! 
	  If you don't know what you will do, please don't use them!
	
	2.The two class do NOT modify tinyxml src files.
	  So you can use tinyxml in your wise.

	thank tinyxml :-)

*/

/*
for libproperties
added by harite Harite.K@gmail.com
for libproperties project's debug
*/
// not used
//#define LIBPROPERTIES_DEBUG

//c++, ~~~
// not used
//class TiXmlParsingData;

/** 
    Class: TiXmlDeclarationWithoutStandalone
    Written by harite
    mailto:Harite.K@gmail.com
    date:2007/10/04
    for project libproperties on http://code.google.com/p/libproperties

    In correct XML,the declaration which is used by class Properties
    in java is the first entry in the file.
		<?xml version="1.0" encoding="UTF-8"?>

	In TinyXml, class TiXmlDeclaration has 3 possible attributes to 
	the declaration:version, encoding, and standalone.
	If i want tinyxml create a xml file with the declaration 
	"<?xml version="1.0" encoding="UTF-8"?>", i must kill god ^+^.
	So, I write a new class which is extend TiXmlDeclaration to do 
	this work.

	The implement of the class TiXmlDeclarationWithoutStandalone is simple.
	I just override some functions.

*/
class TiXmlDeclarationWithoutStandalone : public TiXmlDeclaration
{
public:
	TiXmlDeclarationWithoutStandalone()  : TiXmlDeclaration() {}

#ifdef TIXML_USE_STL
	TiXmlDeclarationWithoutStandalone(	const std::string& _version, const std::string& _encoding )
		: TiXmlDeclaration( _version, _encoding, "yes"//we don't use it
						  ){}
#endif

	TiXmlDeclarationWithoutStandalone(	const char* _version, const char* _encoding )
		: TiXmlDeclaration( _version, _encoding, "yes"//we don't use it
		                  ){}

	TiXmlDeclarationWithoutStandalone( const TiXmlDeclarationWithoutStandalone& copy )
		: TiXmlDeclaration( copy ){}

	virtual ~TiXmlDeclarationWithoutStandalone()	{}

	inline void operator=( const TiXmlDeclarationWithoutStandalone& copy )
	{
		Clear();
	    copy.CopyTo( this );
	}

	inline void Print( FILE* cfile, int /*not used*/ ) const
	{
		fprintf (cfile, "<?xml ");
		if ( this->Version()!=NULL )
		{fprintf (cfile, "version=\"%s\" ", this->Version());}
		if ( this->Encoding()!=NULL )
		{fprintf (cfile, "encoding=\"%s\"", this->Encoding());}
		fprintf (cfile, "?>");
	}
};


/** 
    Class: TiXmlDoctype
    Written by harite
    mailto:Harite.K@gmail.com
    date:2007/10/04
    for project libproperties on http://code.google.com/p/libproperties

    You can read "http://java.sun.com/dtd/properties.dtd" to know that 
	the class Properties in java need this DOCTYPE declaration
	<!DOCTYPE properties SYSTEM "http://java.sun.com/dtd/properties.dtd">
	in the xml files.
	First, i think that the class TiXmlUnknown in tinyxml can do it.But
	i am wrong, because TiXmlUnknown object can't be written into xml file.
	So, I write a new class which is extend TiXmlComment to do this work.

	The implement of the class TiXmlDoctype is simple.
	I just override some functions.

*/
/*
<!DOCTYPE value1 value2 ...>
*/
class TiXmlDoctype : public TiXmlComment
{
public:
	/// Constructs an empty comment.
	TiXmlDoctype() : TiXmlComment() {}

	TiXmlDoctype( const TiXmlDoctype& copy ) : TiXmlComment( copy ) { copy.CopyTo(this); }

	virtual ~TiXmlDoctype() {}

	inline void operator=( const TiXmlDoctype& base )
	{
		Clear();
		base.CopyTo(this);
	}

	inline void Print( FILE* cfile, int depth ) const
	{
		for ( int i=0; i<depth; i++ )
	    {
		    fputs( "    ", cfile );
	    }
	    fprintf( cfile, "<!DOCTYPE %s>", value.c_str() );
	}

	inline void StreamOut( TIXML_OSTREAM * stream ) const
	{
		(*stream) << "<!DOCTYPE ";
		(*stream) << value;
		(*stream) << ">";
	}

	/*
	  we don't use this functions.
	  Maybe they will exist in next version,but now they have errors.
	*/
	/*
	void CopyTo( TiXmlDoctype* target ) const
	{
		TiXmlNode::CopyTo( target );
	}*/

	/*
	TiXmlNode* Clone() const
	{
		TiXmlComment* clone = new TiXmlComment();

		if ( !clone )
			return 0;

		CopyTo( clone );
		return clone;
	}*/

	/*
	#ifdef TIXML_USE_STL
	void StreamIn( TIXML_ISTREAM * in, TIXML_STRING * tag )
	{
		while ( in->good() )
		{
			int c = in->get();	
			if ( c <= 0 )
			{
				TiXmlDocument* document = GetDocument();
				if ( document )
					document->SetError( TIXML_ERROR_EMBEDDED_NULL, 0, 0, TIXML_ENCODING_UNKNOWN );
				return;
			}
			
			(*tag) += (char) c;

			if ( c == '>' )//'>' in the end
			{
				// All is well.
				return;		
			}
		}
	}
    #endif
	*/

	/*
	const char* Parse( const char* p, TiXmlParsingData* data, TiXmlEncoding encoding )
	{
		TiXmlDocument* document = GetDocument();
		value = "";
		p = SkipWhiteSpace( p, encoding );
		
		if ( data )
		{
			data->Stamp( p, encoding );
			location = data->Cursor();
		}
		const char* startTag = "<!DOCTYPE";
		const char* endTag   = ">";

		if ( !StringEqual( p, startTag, false, encoding ) )
		{
			document->SetError( TIXML_ERROR_PARSING_COMMENT, p, data, encoding );
			return 0;
		}
		p += strlen( startTag );
		p = ReadText( p, &value, false, endTag, false, encoding );
		return p;
	}
	*/

};


/**
* 设置一个“键－值”对,若键已经存在则将其替换成新值
* set a "key-value" pair, if the key exist, update its value
* @param key 要设置的键 the key to set
* @param value 要设置的值 the value to set
*/
void Properties::setProperty(string key, string value)
{
	iterator it = key_value.find(key);
	if(it!=key_value.end())//对于已经存在的
	{
		(*it).second = value;
	}
	else
	{
		key_value[key] = value;
	}
}

/**
* 读取一个键的值，如果不存在，返回默认值defaultvalue
* get value of a key, if the key is inexistence then return default value
* @param key 想要获得值的键 the key of you want value
* @param defaultvalue 如果键不存在则返回此参数 the defaultvalue
* @return 若键存在，返回其对应的值；若不存在，返回defaultvalue
*/
string Properties::getProperty(string key, string defaultvalue) const
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
* 从xml文件中读取“键－值”对 load "key-value" from xml file
* @param filename 读取的xml文件，必须是按照规定的格式
* @return 布尔值 读取成功与否
*/
bool Properties::loadFromXML(const string filename)
{
	TiXmlDocument doc(filename.c_str());
	bool loadOkay = doc.LoadFile();//以utf-8格式读取xml文件
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
* 将键值对按照类似java中Properties类的xml格式存储 store "key-value" to xml file
* @param filename 要保存的xml文件名
* @return 布尔值,代表操作执行成功与否
*/
bool Properties::storeToXML(const string filename) const
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

	for (const_iterator it = key_value.begin()
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


