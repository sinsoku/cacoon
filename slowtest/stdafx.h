#pragma once
#include "../Cacoon/stdafx.h"

#include <gtest/gtest.h>

#ifdef _DEBUG
#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )
#else
#pragma comment( lib, "gtest.lib" )
#pragma comment( lib, "gtest_main.lib" )
#endif
