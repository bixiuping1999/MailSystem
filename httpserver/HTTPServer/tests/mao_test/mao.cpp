#include "../test.h"
#include "mao.h"
void json_test();
void start_mao() {
	//HttpSocket socketInit;
	//HttpServer server;
	//
	//server.run();
	//server.close();
	//delete& socketInit;
	json_test();
}

void json_test() 
{
	const char* json_str = "{\n\t\"name\":\"13\",\n\t\"type\":\"pop\"\n}";
	
	Json::Value object;
	Json::String err;
	Tools::json_read(json_str, strlen(json_str), object, err);
	std::cout << object["type"].asString() << std::endl;

	rstring write_res;
	Json::Value root;
	root["null"] = NULL;			//注意此处在输出是显示为0，而非null
	root["message"] = "OK";
	root["age"] = 52;
	root["array"].append("arr");	// 新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”
	root["array"].append(123);		// 为数组 key_array 赋值，对第二个元素赋值为：1234

	Tools::json_write(root, write_res);
	std::cout << write_res << std::endl;
}