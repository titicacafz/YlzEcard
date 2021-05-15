#pragma once

#include <string>

//��ʱ
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
    //utf8 ת gbk
    static std::string utf8_to_string(const std::string & str);

    //gbk ת utf8
    static std::string string_to_utf8(const std::string & str);
   

    //���dll����·��
    static std::string get_module_path();

    //��õ�ǰ����
    static std::string get_date();
};
