#pragma once
#include "HttpSocket.h"
#include "HttpClient.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpServerHandler.h"
#include "config.h"

class HttpServer
{
private:
	USHORT m_port;
	SOCKET m_socket;
	
public:
	HttpServer(USHORT port=PORT_NUM);
	~HttpServer();
	SOCKET get_socket();
	//初始化
	int start(int backlog=BACKLOG_SIZE);
	//关闭服务端
	int close();
	bool is_close();
	//开始运行（包含初始化）
	void run();
protected:
	HttpClient* accept();

};


