#pragma once

// STL �� boost�AGoogleTest �Ȃǂ̃T�C�Y�̑傫�ȁA���A�ύX����Ȃ��w�b�_�t�@�C���͂����ɒǉ�����B
// �V���� cpp �t�@�C����ǉ�����ꍇ�͕K�����̃w�b�_���C���N���[�h����B(�e�X�g�̗L���ɂ�����炸)
#include "../Cacoon/stdafx.h"

#include <gtest/gtest.h>

#ifdef _DEBUG
#pragma comment( lib, "gtestd.lib" )
#pragma comment( lib, "gtest_maind.lib" )
#else
#pragma comment( lib, "gtest.lib" )
#pragma comment( lib, "gtest_main.lib" )
#endif