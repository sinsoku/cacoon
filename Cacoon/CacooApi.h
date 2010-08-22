#pragma once
class CacooUser
{
public:
	std::string name;
	std::string nickname;
	std::string imageUrl;
};

class CacooApi
{
public:
	CacooApi(void);
	~CacooApi(void);
	CacooUser users(const std::string &name);
};

