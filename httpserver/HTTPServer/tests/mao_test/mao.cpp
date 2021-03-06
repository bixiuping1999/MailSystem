#include "../test.h"
#include "mao.h"

void start_mao() {

	//json_test();
	server_start();
}
void server_start() {
	HttpSocket socketInit;
	HttpServer server;

	server.run();
	server.close();
}

void json_test()
{
	const char* json_str = "{\n\t\"name\":\"13\",\n\t\"type\":\"pop\"\n}";
	const char* json_arr = "{\"arr\":[\"1\",\"2\"]}";
	Json::Value object;
	Json::String err;
	Tools::json_read(json_str, strlen(json_str), object, err);
	std::cout << object["type"].asString() << std::endl;

	Tools::json_read(json_arr, strlen(json_arr), object, err);
	Json::Value arr = Json::Value(Json::ValueType::arrayValue);
	arr = object["arr"];
	for (int i = 0; i < arr.size(); i++)
	{
		Tools::report(arr[i].asString());
	}


	rstring write_res;
	Json::Value root;
	Json::Value ro;
	ro["new_obj"] = "new";
	root["null"] = NULL;			//注意此处在输出是显示为0，而非null
	root["message"] = "OK";
	root["age"] = 52;
	root["array"].append("arr");	// 新建一个key为array，类型为数组，对第一个元素赋值为字符串“arr”
	root["array"].append(123);		// 为数组 key_array 赋值，对第二个元素赋值为：123
	root["array"].append(ro);

	Tools::json_write(root, write_res);
	std::cout << write_res << std::endl;
}