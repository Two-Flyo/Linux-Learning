#pragma once

#include <iostream>
#include <cstring>
#include <jsoncpp/json/json.h>

//定制协议的过程, 目前就是定制结构化数据的过程
//请求格式
typedef struct request
{
    int x;
    int y;
    char op; //支持 + - * / %
}request_t;

//响应格式
typedef struct response
{
    int code; //server运算完毕的计算状态: code(0:success), code(-1, div 0) ...
    int result; //计算结果: 能否区分正常计算结果还是异常的退出结果

}response_t;


// request -> strng
std::string SerializeRequest(const request_t &req)
{
    Json::Value root; //可以承装任何对象, Json是一种kv式的序列化方案
    root["datax"] = req.x;
    root["datay"] = req.y;
    root["operator"] = req.op;

    //FastWriter StyledWriter
    Json::FastWriter writer;
    std::string json_string = writer.write(root);
    return json_string;   
}

// string -> requset_t
void DeserializeRequest(std::string &json_string, request_t &out)
{
    Json::Value root;       
    Json::Reader reader;
    reader.parse(json_string, root);
    out.x = root["datax"].asInt();
    out.op = (char)root["operator"].asUInt();
    out.y = root["datay"].asInt();
}

std::string SerializeRespone(const response_t &resp)
{   
    Json::Value root;
    root["code"] = resp.code;
    root["result"] = resp.result;

    Json::FastWriter writer;
    std::string res = writer.write(root);

    return res;    
}

void DeserializeRespone(std::string &json_string, response_t &out)
{

    Json::Reader reader;
    Json::Value root;

    reader.parse(json_string, root);
    out.code = root["code"].asInt();
    out.result = root["result"].asInt();

}

