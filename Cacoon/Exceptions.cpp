#include "StdAfx.h"
#include "Exceptions.h"

#include <sstream>

CacoonException::CacoonException( const char * message, const char * __file__, int line )
	: std::exception( message )
{
	std::ostringstream oss;
	oss << message << std::endl << __file__ << " “àF" << line << " s–Ú";
	this->info = oss.str();
}

std::string CacoonException::Info() const
{
	return std::string( this->info );
}