#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

using namespace std;


typedef struct request
{
    int x;
    int y;
    char op; //支持 + - * / %
}request_t;


int main()
{
    //反序列化

    C


    // 序列化的过程

    // request_t req = {1, 2, '+'};
    // Json::Value root; //可以承装任何对象, Json是一种kv式的序列化方案
    // root["datax"] = req.x;
    // root["datay"] = req.y;
    // root["operator"] = req.op;

    // //FastWriter StyledWriter
    // Json::FastWriter writer;
    // string json_string = writer.write(root);

    // cout << json_string << endl;
    
    return 0;

}