/**
 * @file aes_cppunit.h
 * @brief a test framework for framecommon with cppunit
 * @detail three kinds of writing.
 * @author szj0306
 * @version 1.0
 * @date 2012-10-31
 * @bug no.
 * @warning no.
 * @copyright GNU license
 */

#ifndef __AES_CPPUNIT_H__
#define __AES_CPPUNIT_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

/// 1. a simple test
class AESSimpleTest : public CppUnit::TestCase
{
public:
    void runTest();
};

/// 2. TestFixture and TestCaller used in combination.
class AESTest : public CppUnit::TestFixture
{
public:
    void setUp();
    void tearDown();

    /**
     * @brief test aes's encrypt
     * @return no.
     */
    void testEncrypt();
    /**
     * @brief test aes's decrypt
     * @return no.
     */
    void testDecrypt();
};

/**
 * 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
 * 3. With CppUnit defined a set of auxiliary macros to automate test
 *    case definition and registration.
 */
class AESCppUnitTest : public CppUnit::TestFixture
{
    /**
     * @brief Important macros
     */
    CPPUNIT_TEST_SUITE(AESCppUnitTest);
    CPPUNIT_TEST(testEncrypt);
    CPPUNIT_TEST(testDecrypt);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    /**
     * @brief test aes's encrypt
     * @return no.
     */
    void testEncrypt();
    /**
     * @brief test aes's decrypt
     * @return no.
     */
    void testDecrypt();
};

#endif //__AES_CPPUNIT_H__
