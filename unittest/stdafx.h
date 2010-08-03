#pragma once

// STL や boost、GoogleTest などのサイズの大きな、かつ、変更されないヘッダファイルはここに追加する。

#include <gtest/gtest.h>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )