#pragma once
class CacooServer
{
public:
	CacooServer(void);
	virtual ~CacooServer(void);
	virtual std::string get(const std::string& url);
};

