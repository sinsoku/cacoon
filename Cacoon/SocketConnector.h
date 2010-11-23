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

	// コピー禁止
	SocketConnector( const SocketConnector & );
	SocketConnector & operator = ( const SocketConnector & );

	SOCKET sock;
	SOCKADDR_IN addr;

	void makeSocket();
	void makeAddressFamily( const std::string & hostname, int port );
};

