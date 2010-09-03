#pragma once

// STL や boost、GoogleTest などのサイズの大きな、かつ、変更されないヘッダファイルはここに追加する。
// 新しく cpp ファイルを追加する場合は必ずこのヘッダをインクルードする。(テストの有無にかかわらず)
#include "../Cacoon/stdafx.h"

#include <gtest/gtest.h>

#ifdef _DEBUG
#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )
#else
#pragma comment( lib, "gtest.lib" )
#pragma comment( lib, "gtest_main.lib" )
#endif