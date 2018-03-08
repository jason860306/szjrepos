#include <framecommon/AES.h>
#include "aes_cppunit.h"
using namespace MYFRAMECOMMON;

/// @brief a very important macros, it is used for registe a test case in test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(AESCppUnitTest);

static std::string g_orgin_string("jqaweigfqjwoietjqowtejqowefjoaw");
static std::string g_encry_string;

/// 1. AESSimpleTest
void AESSimpleTest::runTest()
{
    /// generate a key.
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }

    /// encrypt
    printf("orgin string: %s\n", g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESEncrypt(key, key.size() * 8, g_orgin_string.c_str(),
                                             g_orgin_string.size(), g_encry_string));
    printf("g_encry_string.size = %ld\nencry_string: ", g_encry_string.size());
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
        fflush(stdout);
    }
    printf("\n");

    /// decrypt
    std::string out_data;
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESDecrypt(key, key.size() * 8, g_encry_string.c_str(),
                                             g_encry_string.size(), out_data));
    printf("decrypt_string.size = %ld\ndecrypt_string: %s\n",
           out_data.size(), out_data.c_str());

    CPPUNIT_ASSERT_EQUAL(out_data.c_str(), g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(out_data.size(), g_orgin_string.size());
}

/// 2. TestFixture和TestCaller组合使用
void AESTest::setUp()
{
}

void AESTest::tearDown()
{
}

/// encrypt.
void AESTest::testEncrypt()
{
    /// generate a key.
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: %s\n", g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESEncrypt(key, key.size() * 8, g_orgin_string.c_str(),
                                             g_orgin_string.size(), g_encry_string));
    printf("g_encry_string.size = %ld\nencry_string: ", g_encry_string.size());
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
        fflush(stdout);
    }
    printf("\n");
}

/// decrypt.
void AESTest::testDecrypt()
{
    /// generate a key.
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: ");
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
        fflush(stdout);
    }
    printf("\n");
    std::string out_data;
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESDecrypt(key, key.size() * 8, g_encry_string.c_str(),
                                             g_encry_string.size(), out_data));
    printf("decrypt_string.size = %ld\ndecrypt_string: %s\n",
           out_data.size(), out_data.c_str());

    CPPUNIT_ASSERT_EQUAL(out_data.c_str(), g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(out_data.size(), g_orgin_string.size());
}

/// 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
void AESCppUnitTest::setUp()
{
}

void AESCppUnitTest::tearDown()
{
}

/// encrypt.
void AESCppUnitTest::testEncrypt()
{
    /// generate a key.
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: %s\n", g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESEncrypt(key, key.size() * 8, g_orgin_string.c_str(),
                                             g_orgin_string.size(), g_encry_string));
    printf("g_encry_string.size = %ld\nencry_string: ", g_encry_string.size());
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
        fflush(stdout);
    }
    printf("\n");
}

/// decrypt.
void AESCppUnitTest::testDecrypt()
{
    /// generate a aes key.
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: ");
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
        fflush(stdout);
    }
    printf("\n");
    std::string out_data;
    CPPUNIT_ASSERT_EQUAL(0, CAES::AESDecrypt(key, key.size() * 8, g_encry_string.c_str(),
                                             g_encry_string.size(), out_data));
    printf("decrypt_string.size = %ld\ndecrypt_string: %s\n",
           out_data.size(), out_data.c_str());

    CPPUNIT_ASSERT_EQUAL(out_data.c_str(), g_orgin_string.c_str());
    CPPUNIT_ASSERT_EQUAL(out_data.size(), g_orgin_string.size());
}
