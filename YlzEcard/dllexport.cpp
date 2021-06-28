#include "pch.h"
#include "dllparser.h"
#include "systemutil.h"
#include "json.h"
#include <map>
#include "pugixml/pugixml.hpp"
#include <chrono>
#include <io.h>
#include <Windows.h>
#include <direct.h>

using namespace nlohmann;
using std::string;
using std::map;



/// <summary>
/// 去空行数
/// </summary>
/// <param name="s">要去空的字符串</param>
/// <returns></returns>
string & trim(string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(std::remove_if(s.begin(), s.end(), iswspace), s.end());

    return s;
}

//请求的xml转成json
string xml2json(const pugi::xml_document& req_doc, const string& fid) {
    string funid = fid;
    string usr = req_doc.child("request").child("Body").child_value("usr");
    string pwd = req_doc.child("request").child("Body").child_value("pwd");
    string aac058 = req_doc.child("request").child("Body").child_value("aac058");
    string bkc006 = req_doc.child("request").child("Body").child_value("bkc006");
    string bkc007 = req_doc.child("request").child("Body").child_value("bkc007");
    string bkc541 = req_doc.child("request").child("Body").child_value("bkc541");
    string bkef34 = req_doc.child("request").child("Body").child_value("bkef34");
    string bke284 = "06";

    string json = "{";
    json += "\"usr\":\"" + usr + "\",";
    json += "\"pwd\":\"" + pwd + "\",";
    json += "\"funid\":\"" + funid + "\",";
    json += "\"data\":{";
    json += "\"usr\":\"" + usr + "\",";
    json += "\"pwd\":\"" + pwd + "\",";
    json += "\"aac058\":\"" + aac058 + "\",";
    json += "\"bkc006\":\"" + bkc006 + "\",";
    json += "\"bkc007\":\"" + bkc007 + "\",";
    json += "\"bkc541\":\"" + bkc541 + "\",";
    json += "\"bkef34\":\"" + bkef34 + "\",";
    json += "\"bke284\":\"" + bke284 + "\"";
    json += "}";
    json += "}";
    return json;
}

//错误xml生成
string err(const string& msg) 
{
    string xml = "<response>";
    xml += "<Header>";
    xml += "<result>1</result>";
    xml += "<funcid>yb04.10.01.16</funcid>";
    xml +="</Header>";
    xml += "<Body>";    
    xml += "<msg>" + msg + "</msg>";
    xml += "</Body>";
    xml += "</response>";
    return xml;
}

//成功返回值的处理
string json2xml(const string& res) {
    string utf8_res = SystemUtil::string_to_utf8(res);
    auto json = json::parse(utf8_res);
    std::string flag = json["flag"];
    if (flag != "1") {
        string cause = json["cause"];
        return err(cause);
    }

    auto data = json["data"];

    string xming0 = SystemUtil::utf8_to_string(data["aac003"]);
    string cardno = SystemUtil::utf8_to_string(data["aaz500"]);
    string zjlx00 = SystemUtil::utf8_to_string(data["aac058"]);
    string zjhm00 = SystemUtil::utf8_to_string(data["aac002"]);
    string token = SystemUtil::utf8_to_string(data["acsign"]);
    string idcode = SystemUtil::utf8_to_string(data["idcode"]);
    //string userName = SystemUtil::utf8_to_string(data["userName"]);
    //string idNo = SystemUtil::utf8_to_string(json["idNo"]);

    string xml = "<response>";
    xml += "<Header>";
    xml += "<result>0</result>";
    xml += "<funcid>yb04.10.01.16</funcid>";
    xml += "</Header>";
    xml += "<Body>";
    xml += "<xming0>"+ xming0 +"</xming0>";
    xml += "<cardno>" + cardno + "</cardno>";
    xml += "<zjlx00>" + zjlx00 + "</zjlx00>";
    xml += "<zjhm00>" + zjhm00 + "</zjhm00>";
    xml += "<token>" + token + "</token>";
    xml += "<idcode>" + idcode + "</idcode>";
    xml += "</Body>";
    xml += "</response>";
    return xml;
}

//在指定文件路径写入指定信息，ANSI版本
void WriteLog(const char* text)
{
    time_t tt = time(NULL);
    struct tm* t = localtime(&tt);
    char targetString[256];
    snprintf(targetString, sizeof(targetString), "log-%d-%02d-%02d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    char _szFileName[100];
    GetCurrentDirectory(256, _szFileName);//获取当前运行目录
    strcat(_szFileName, "\\ylzdlllogs");//连接后缀名
    string logDir = _szFileName;
    if (0 != _access(logDir.c_str(), 0))
    {
        _mkdir(logDir.c_str());   // 返回 0 表示创建成功，-1 表示失败
    }
    FILE* fp;
    string path = logDir + "\\" + targetString;
    fopen_s(&fp, path.c_str(), "a");
    if (fp != NULL)
    {
        SYSTEMTIME st;
        GetLocalTime(&st);
        char buf[128] = { 0 };
        sprintf_s(buf, 128, "%04d%02d%02d %02d:%02d:%02d:%03d:   ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fwrite(buf, sizeof(char), strlen(buf), fp);
        fwrite(text, sizeof(char), strlen(text), fp);
        fwrite("\n", sizeof(char), 2, fp);
        fclose(fp);
    }
}

int _stdcall YlzEcard(char* req, char* resp)
{   
    //string ss = R"({"traceid":"","flag":"1","data":{"akc087":"3100.71","aac001":"3473736","aab301_mc":"新罗区","aac002":"352601197305161028","aac004_mc":"女","aaz500":"F46536395","bka531":"N","acsign":"XS9P7v5ClurSV2WHRKIwg7ksFksrNfLYhQMlrpNIqdBnpIPt7WaXvHv0iOwB1Asbln3zrq3QsHGOZZH/1AYdj0II6m2nOGFqWDBYttUXZ3KY1j3ONxoapZKUWEExaDEQEI18MDt9TfsbRcTWp8KGwYqxYj1BOiUCtJWzTpkA3fwDZNm44+jb0jiuA94Eq0M11i0NGEJNthnwNOE5wrnvEXDxrmxHEXnO8k693b1YzG2lvTMPHYkV/HIKL/UUw63ovMGSuH/wqD6V85Gc/3nAUUNoa9mQIVRvHXBpqQuyB9A=","aac058_mc":"居民身份证（户口簿）","idcode":"4243725049008084044801350000","aab301":"350802","aab004":"龙岩人民医院","aac006":"19730516","cbxzlist":[{"aae140":"310","bkc001_mc":"在职公务员","aab050":"20051101","aab034":"350802","aab034_mc":"龙岩市医管中心新罗管理部","bkc026":"1","bkc026_mc":"有效","aae140_mc":"城镇职工基本医疗保险","bkc001":"03"},{"aae140":"320","bkc001_mc":"在职公务员","aab050":"20051101","aab034":"350802","aab034_mc":"龙岩市医管中心新罗管理部","bkc026":"1","bkc026_mc":"有效","aae140_mc":"公务员医疗补助","bkc001":"03"},{"aae140":"610","bkc001_mc":"在职公务员","aab050":"20051101","aab034":"350802","aab034_mc":"龙岩市医管中心新罗管理部","bkc026":"1","bkc026_mc":"有效","aae140_mc":"商业补充医疗保险","bkc001":"03"},{"aae140":"520","bkc001_mc":"在职公务员","aab050":"20051101","aab034":"350802","aab034_mc":"龙岩市医管中心新罗管理部","bkc026":"1","bkc026_mc":"有效","aae140_mc":"机关生育","bkc001":"03"}],"aac058":"1","aac003":"林珍红","aac004":"2","aac999":"352601730516102    ","baz551":"F46536395","sflist":[{"bkeb35":"N","bka543":"BKA531","bka543_mc":"是否扶贫对象"},{"bkeb35":"N","bka543":"BKA544","bka543_mc":"是否医疗救助对象"},{"bkeb35":"N","bka543":"BKA539","bka543_mc":"是否计划生育特殊家庭成员"},{"bkeb35":"N","bka543":"BKA545","bka543_mc":"是否出生缺陷对象"},{"bkeb35":"N","bka543":"BKA546","bka543_mc":"是否体检可报销对象"},{"bkeb35":"N","bka543":"BKA547","bka543_mc":"是否保健对象"}]},"cause":"操作成功"})";
    //json2xml(ss);
    int reslen = 1024;
    int code = -1;
    try
    {        
        //
        WriteLog("=======请求报文======");
        WriteLog(req);
        string dll_dir = SystemUtil::get_module_path() + "YlzEcard\\";

        SetCurrentDirectory(dll_dir.c_str());

        DllParser dll_parser;
        if (!dll_parser.load(dll_dir+"sieafstandard.dll")) {
            throw std::exception{ err(dll_dir+"加载保睿通动态库失败!").c_str() };
        }

        //请求转换
        pugi::xml_document req_doc;
        if (!req_doc.load_string(req)) {
            throw std::exception{ "请求报文不是合法的xml格式！" };
        }
        
        //免登录
        {
            WriteLog("=======免登录======");
            
            string json = xml2json(req_doc, "yb04.10.09.03");
            char outputdata[2048] = { 0 };
            char errmsg[2048] = { 0 };
            int ret = dll_parser.call<int __stdcall(char* inputvalue, int outputlen, char* outputdata, char* errmsg)>
                (std::string("business_handle"), (char *)json.c_str(), 2048, (char *)outputdata, (char *)errmsg);

            if (ret != 0) {
                WriteLog("=======免登录失败======");
                WriteLog(errmsg);
                throw std::exception{ errmsg };
            }

            WriteLog("=======免登录返回======");
            WriteLog(outputdata);
        }

        //登录
        {
            WriteLog("=======登录======");
            string json = xml2json(req_doc, "yb04.10.01.16");
            char outputdata[1024*10] = { 0 };
            char errmsg[1024*10] = { 0 };
            int ret = dll_parser.call<int __stdcall(char* inputvalue, int outputlen, char* outputdata, char* errmsg)>
                (std::string("business_handle"), (char*)json.c_str(), 1024*10, (char*)outputdata, (char*)errmsg);

            if (ret != 0) {
                WriteLog("=======登录失败======");
                WriteLog(errmsg);
                throw std::exception{ errmsg };
            }
            WriteLog("=======登录返回======");
            WriteLog(outputdata);
            //
            string xml = json2xml(outputdata);
            snprintf(resp, reslen, "%s", xml.c_str());
            WriteLog(xml.c_str());

            code = 0;
        }                       
    }
    catch (const std::exception& e)
    {
        code = -1;
        string xml = err(e.what());
        snprintf(resp, reslen, "%s", xml.c_str());
        WriteLog(xml.c_str());
    }    

    return code;
}
