#include "stdafx.h"
#include "Encoding.h"

std::wstring Encoding::ShiftJisToUtf16( const std::string & cstring )
{
	int len = MultiByteToWideChar( CP_ACP, 0, cstring.c_str(), cstring.length(), NULL, 0 );
	boost::scoped_array<wchar_t> utf16( new wchar_t[len+1] );
	int ret = MultiByteToWideChar( CP_ACP, 0, cstring.c_str(), cstring.length(), &utf16[0], len * sizeof( wchar_t ) );
	if( ret == 0 )
	{
		throw CACOON_EXCEPTION( "SHIFT-JIS -> UTF-16 ‚Ì•ÏŠ·‚ÉŽ¸”s" );
	}
	utf16[len] = L'\0';

	return std::wstring( &utf16[0] );
}


std::string Encoding::Utf16ToShiftJis( const std::wstring & utf16 )
{
	int len = WideCharToMultiByte( CP_ACP, 0, utf16.c_str(), utf16.length(), NULL, 0, NULL, NULL );
	boost::scoped_array<char> cstring( new char[len+1] );
	int ret = WideCharToMultiByte( CP_ACP, 0, utf16.c_str(), utf16.length(), &cstring[0], len * sizeof( char ), NULL, NULL );
	if( ret == 0 )
	{
		throw CACOON_EXCEPTION( "UTF-16 -> SHIFT-JIS ‚Ì•ÏŠ·‚ÉŽ¸”s" );
	}
	cstring[len] = '\0';

	return std::string( &cstring[0] );
}

std::wstring Encoding::Utf8ToUtf16( const std::string & utf8 )
{
	int len = MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), utf8.length(), NULL, 0 );
	boost::scoped_array<wchar_t> utf16( new wchar_t[len+1] );
	int ret = MultiByteToWideChar( CP_UTF8, 0, utf8.c_str(), utf8.length(), &utf16[0], len * sizeof( wchar_t ) );
	if( ret == 0 )
	{
		throw CACOON_EXCEPTION( "UTF-8 -> UTF-16 ‚Ì•ÏŠ·‚ÉŽ¸”s" );
	}
	utf16[len] = L'\0';

	return std::wstring( &utf16[0] );
}

std::string Encoding::Utf16ToUtf8( const std::wstring & utf16 )
{
	int len = WideCharToMultiByte( CP_UTF8, 0, utf16.c_str(), utf16.length(), NULL, 0, NULL, NULL );
	boost::scoped_array<char> utf8( new char[len+1] );
	int ret = WideCharToMultiByte( CP_UTF8, 0, utf16.c_str(), utf16.length(), &utf8[0], len * sizeof( wchar_t ), NULL, NULL );
	if( ret == 0 )
	{
		throw CACOON_EXCEPTION( "UTF-16 -> UTF-8 ‚Ì•ÏŠ·‚ÉŽ¸”s" );
	}
	utf8[len] = '\0';

	return std::string( &utf8[0] );
}