
class Encoding
{
public:
	static std::wstring ShiftJisToUtf16( const std::string & source );
	static std::string Utf16ToShiftJis( const std::wstring & source );
	static std::wstring Utf8ToUtf16( const std::string & source );
	static std::string Utf16ToUtf8( const std::wstring & source );
};