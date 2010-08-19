#pragma once

// STL や boost、GoogleTest などのサイズの大きな、かつ、変更されないヘッダファイルはここに追加する。
// 新しく cpp ファイルを追加する場合は必ずこのヘッダをインクルードする。(テストの有無にかかわらず)
#include "../Cacoon/stdafx.h"

#include <gtest/gtest.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>

#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )

#pragma comment( lib, "ws2_32.lib" )