#pragma once

#include <string>

//临时
template<typename T>
class Singleton {

public:

	//
	static T& Instance() {   //
		static T t;
		return t;
	}

	Singleton(const Singleton &another) = delete;

private:
	Singleton();
};


struct  SystemUtil
{
    //utf8 转 gbk
    static std::string utf8_to_string(const std::string & str);

    //gbk 转 utf8
    static std::string string_to_utf8(const std::string & str);
   

    //获得dll所在路径
    static std::string get_module_path();

    //获得当前日期
    static std::string get_date();
};
