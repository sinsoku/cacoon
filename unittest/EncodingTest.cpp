#include "stdafx.h"
#include "Encoding.h"

TEST( EncodingTest, ShiftJisToUtf16 )
{
	std::string shift_jis = "AbcŠ¿Žš123";
	std::wstring utf_16 = L"AbcŠ¿Žš123";

	std::wstring converted = Encoding::ShiftJisToUtf16( shift_jis );

	EXPECT_EQ( utf_16, converted );
}

TEST( EncodingTest, Utf16ToShiftJis )
{
	std::string shift_jis = "AbcŠ¿Žš123";
	std::wstring utf_16 = L"AbcŠ¿Žš123";

	std::string converted = Encoding::Utf16ToShiftJis( utf_16 );

	EXPECT_EQ( shift_jis, converted );
}

TEST( EncodingTest, Utf8ToUtf16 )
{
	char utf_8_asArray[] = { 'A', 'b', 'c', (char)0xe6, (char)0xbc, (char)0xa2, (char)0xe5, (char)0xad, (char)0x97, (char)0xe3, (char)0x81, (char)0xb2, (char)0xe3, (char)0x82, (char)0x89, (char)0xe3, (char)0x81, (char)0x8c, (char)0xe3, (char)0x81, (char)0xaa, '1', '2', '3', '\0' };

	std::string utf_8( utf_8_asArray );
	std::wstring utf_16 = L"AbcŠ¿Žš‚Ð‚ç‚ª‚È123";

	std::wstring converted = Encoding::Utf8ToUtf16( utf_8 );

	EXPECT_EQ( utf_16, converted );
}

TEST( EncodingTest, Utf16ToUtf8 )
{
	std::wstring utf_16 = L"AbcŠ¿Žš‚Ð‚ç‚ª‚È123";
	char utf_8_asArray[] = { 'A', 'b', 'c', (char)0xe6, (char)0xbc, (char)0xa2, (char)0xe5, (char)0xad, (char)0x97, (char)0xe3, (char)0x81, (char)0xb2, (char)0xe3, (char)0x82, (char)0x89, (char)0xe3, (char)0x81, (char)0x8c, (char)0xe3, (char)0x81, (char)0xaa, '1', '2', '3', '\0' };
	std::string utf_8( utf_8_asArray );

	std::string converted = Encoding::Utf16ToUtf8( utf_16 );

	EXPECT_EQ( utf_8, converted );
}