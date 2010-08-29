#pragma once

// ソケットコネクションを確立するためのクラス
// SOCKET と SOCKADDR_IN 構造体をラッピングします。
class SocketConnector
{
public:
	SocketConnector( const std::string & hostname, int port );
	~SocketConnector();

	// 接続の開始。リクエストを送る前に呼ばれる。
	void Connect();

	// ソケットのゲッター
	SOCKET Socket();

private:
	SOCKET sock;
	SOCKADDR_IN addr;

	void makeSocket();
	void makeAddressFamily( const std::string & hostname, int port );
};

