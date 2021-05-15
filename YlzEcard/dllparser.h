#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <functional>
#include <iostream>
using namespace std;

class DllParser
{
public:

	DllParser() :m_hMod(nullptr)
	{
	}

	~DllParser()
	{
		unLoad();
	}

	bool load(const string& dllPath)
	{
		m_hMod = LoadLibraryA(dllPath.data());
		if (nullptr == m_hMod)
		{
			auto err = GetLastError();
			printf("LoadLibrary failed\n");
			return false;
		}

		

		return true;

	}
	

	bool unLoad()
	{
		if (m_hMod == nullptr)
			return true;

		auto b = FreeLibrary(m_hMod);
		if (!b)
			return false;

		m_hMod = nullptr;
		return true;
	}	

	/*
	* 查找dll中接口,并调用
	*/
	template<typename T, typename... Args>
	typename result_of<function<T>(Args...)>::type call(const string& funcName, Args&&... args)
	{
		auto f = get_function<T>(funcName);
		if (nullptr == f)
		{
			string s = "can not find this function " + funcName;
			throw exception(s.c_str());
		}
		return f(forward<Args>(args)...);
	}
	

private:
	HMODULE m_hMod;
	map<string, FARPROC> m_map;

	/*
	* 查找dll中接口
	*/
	template<typename T>
	function<T> get_function(const string& funcName)
	{
		auto it = m_map.find(funcName);
		if (it == m_map.end())
		{
			auto addr = GetProcAddress(m_hMod, funcName.c_str());
			if (!addr)
				return nullptr;
			m_map.insert(make_pair(funcName, addr));
			it = m_map.find(funcName);
		}
		return function<T>((T*)(it->second));
	}
};