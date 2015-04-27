从而实现类似java中Properties类的作用。两者生成的xml文件可以互通。

> Xml时代据说已经到来了，现在的程序流行使用xml配置文件。如果你
使用过java中的Properties类，你会发现它的方便。很多时候我们并不
需要多么庞大的类库，我们仅仅需要从xml文件中提取“key-value”形式
的配置参数或将其写入。我们需要易于使用的尽可能小的类库。我们可
能想按以下代码形式完成我们的配置文件解析工作：(见src/test/tes-
tproperties.cpp)

code
```
Properties p;
p.setProperty("sid","harite");
p.setProperty("port","1521");
p.setProperty("userpassword","12y3_aer65");
p.setProperty("host","127.0.0.1");
p.setProperty("username","system");
p.storeToXML("connectsetting.xml");
p.clear();

if(!p.loadFromXML("connectsetting.xml"))
{
	cout << "falue" << endl;
}
else
{
	for(Properties::const_iterator it = p.begin()
		; it!=p.end() ;
		++it)
	{
		cout << (*it).first << "-->" << (*it).second 
		<< endl;
	}
	cout << "use getProperty" << endl;
	cout << p.getProperty("sid", "") << endl;
	cout << p.getProperty("username", "") << endl;
	cout << p.getProperty("port", "") << endl;
	cout << p.getProperty("notexist", "defaultvalue") 
	     << endl;
	p.clear();
}
```
code
> 是不是发现这个c++类的名字和几个方法与java中的Properties类很相
似？哈哈,你是对的，使用libproperties库生成的xml文件是完全可以与
java中Properties类互通的！libproperties库可以无障碍的读取java程
序产生的xml文件（使用Properties类）。
> libproperties库会不会难于学习？不会！它对外只提供一个类和几个
公共方法。（仅有类Properties）
> libproperties库线程安全吗？不安全。底层基于tinyxml2.4.3库，这
个库线程不安全。
> 我已经有了tinyxml库，如果安装了libproperties库，会不会冲突？
如果你已经安装了tinyxml库，包括头文件和库文件，则可以将include
目录下的libproperties.h和libproperties\_tinyxml\_ext.h引入你的工
程头文件搜索路径，将src/libproperties里的libproperties.cpp和l-
ibproperties\_tinyxml\_ext.cpp源文件引入你的工程即可。libproper-
tis源文件没有修改任何tinyxml源文件，只是衍生出几个类。