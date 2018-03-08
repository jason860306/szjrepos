/**
 * @file BufferHelperCppUnitTest.h
 * @brief a test framework for framecommon with cppunit
 * @detail just use the third kind of writing.
 * @author szj0306
 * @version 1.0
 * @date 2012-10-31
 * @bug no.
 * @warning no.
 * @copyright GNU license
 */


#ifndef BUFFERHELPERTEST_H
#define BUFFERHELPERTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

/// 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
class BufferHelperCppUnitTest : public CppUnit::TestFixture
{
    /// very important.
    CPPUNIT_TEST_SUITE(BufferHelperCppUnitTest);
    CPPUNIT_TEST(testPutGetInTemplate);
    CPPUNIT_TEST(testPutGetShort);
    CPPUNIT_TEST(testPutGetInt);
    CPPUNIT_TEST(testPutGetLongLong);
    CPPUNIT_TEST(testPutGetString);
    CPPUNIT_TEST(testPutGetCharPtr);
    CPPUNIT_TEST(testPutGetCharPtrWithLenInTemplate);
    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();

    void testPutGetInTemplate();
    void testPutGetShort();
    void testPutGetInt();
    void testPutGetLongLong();
    void testPutGetString();
    void testPutGetCharPtr();
    void testPutGetCharPtrWithLenInTemplate();

private:
    std::size_t m_NumLen;
    std::vector<std::vector<char> > m_BufVec;
    std::vector<short> m_ShortVec;
    std::vector<int> m_IntVec;
    std::vector<long long> m_LongLongVec;
    std::vector<std::string> m_StringVec;
};

#endif
