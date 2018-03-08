#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <cppunit/CompilerOutputter.h>
#include <cppunit/TextOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>

#include <framecommon/BufferHelper.h>
#include "BufferHelperCppUnitTest.h"
using namespace MYFRAMECOMMON;

/// @brief a very important macros, it is used for registe a test case in test suite.
CPPUNIT_TEST_SUITE_REGISTRATION(BufferHelperCppUnitTest);

/**
 * @brief prepair some value for test.
 * @return no.
 *
 * @detail 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
 */
void BufferHelperCppUnitTest::setUp()
{
    /// initialization.
    m_NumLen = 20;
    {

        char *TmpBuf = new char[m_NumLen + 1];
        memset(TmpBuf, 0, m_NumLen + 1);
        do {
            srand((unsigned)time(NULL));
            for (char i = 0; i < (char)m_NumLen; ++i) {
                TmpBuf[i] = (char)(rand() % CHAR_MAX);
            }
            std::vector<char> buf;
            buf.insert(buf.end(), (char*)TmpBuf, (char*)TmpBuf + m_NumLen + 1);
            m_BufVec.push_back(buf);
            memset(TmpBuf, 0, m_NumLen + 1);
        } while (m_BufVec.size() != m_NumLen);
        delete TmpBuf;
        TmpBuf = NULL;
    }

    {
        srand((unsigned)time(NULL));
        for (short i = 0; i < (short)m_NumLen; ++i) {
            m_ShortVec.push_back((short)rand() % SHRT_MAX);
        }
    }

    {
        srand((unsigned)time(NULL));
        for (int i = 0; i < (int)m_NumLen; ++i) {
            m_IntVec.push_back(rand() % INT_MAX);
        }
    }

    {
        srand((unsigned)time(NULL));
        for (long long i = 0; i < (long long)m_NumLen; ++i) {
            m_LongLongVec.push_back((long long)rand() % LLONG_MAX);
        }
    }

    {
        char *TmpBuf = new char[m_NumLen + 1];
        memset(TmpBuf, 0, m_NumLen + 1);
        do {
            srand((unsigned)time(NULL));
            for (char i = 0; i < (char)m_NumLen; ++i) {
                TmpBuf[i] = (char)(rand() % CHAR_MAX);
            }
            m_StringVec.push_back(std::string(TmpBuf));
            memset(TmpBuf, 0, m_NumLen + 1);
        } while (m_StringVec.size() != m_NumLen);
        delete TmpBuf;
        TmpBuf = NULL;
    }
}

/**
 * @brief release resource.
 * @return no.
 */
void BufferHelperCppUnitTest::tearDown()
{
    /// release.
    m_BufVec.clear();
    m_ShortVec.clear();
    m_IntVec.clear();
    m_LongLongVec.clear();
    m_StringVec.clear();
}

/**
 * @brief test the function of PutGetInTemplate.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetInTemplate()
{
    {
        CBufferHelper cbh;
        srand((unsigned)time(NULL));
        short InValue = m_ShortVec[(rand() % m_NumLen)];
        cbh.Put(InValue);
        short OutValue = 0;
        cbh.Get(OutValue);
        CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
    }

    {
        CBufferHelper cbh;
        srand((unsigned)time(NULL));
        int InValue = m_IntVec[(rand() % m_NumLen)];
        cbh.Put(InValue);
        int OutValue = 0;
        cbh.Get(OutValue);
        CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
    }

    {
        CBufferHelper cbh;
        srand((unsigned)time(NULL));
        long long InValue = m_LongLongVec[(rand() % m_NumLen)];
        cbh.Put(InValue);
        long long OutValue = 0;
        cbh.Get(OutValue);
        CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
    }
}

/**
 * @brief test the function of PutGetShort
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetShort()
{
    CBufferHelper cbh;
    srand((unsigned)time(NULL));
    short InValue = m_ShortVec[(rand() % m_NumLen)];
    cbh.Put(InValue);
    short OutValue = 0;
    cbh.Get(OutValue);
    CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
}

/**
 * @brief test the function of PutGetInt.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetInt()
{
    CBufferHelper cbh;
    srand((unsigned)time(NULL));
    int InValue = m_IntVec[(rand() % m_NumLen)];
    cbh.Put(InValue);
    int OutValue = 0;
    cbh.Get(OutValue);
    CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
}

/**
 * @brief test the funtion of PutGetLongLong.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetLongLong()
{
    CBufferHelper cbh;
    srand((unsigned)time(NULL));
    long long InValue = m_LongLongVec[(rand() % m_NumLen)];
    cbh.Put(InValue);
    long long OutValue = 0;
    cbh.Get(OutValue);
    CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
}

/**
 * @brief test the function of PutGetString.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetString()
{
    {
        CBufferHelper cbh;
        srand((unsigned)time(NULL));
        std::string& InValue = m_StringVec[(rand() % m_NumLen)];
        cbh.Put(InValue);
        std::string OutValue;
        cbh.Get(OutValue);
        CPPUNIT_ASSERT_EQUAL(InValue, OutValue);
    }

    {
        CBufferHelper cbh;
        srand((unsigned)time(NULL));
        std::string& InValue = m_StringVec[(rand() % m_NumLen)];
        cbh.Put(InValue);
        std::string OutValue;
        srand((unsigned)time(NULL));
        int OutValueLen = rand() % m_NumLen;
        cbh.Get(OutValue, OutValueLen);
        if (OutValueLen > sizeof(int)) {
            std::string::const_iterator citer = OutValue.begin() + sizeof(int);
            const char* pBuf = &*citer;
            CPPUNIT_ASSERT(0 == strncmp(&*InValue.begin(), pBuf, OutValueLen - sizeof(int)));
        }
    }
}


/**
 * @brief test the function of PutGetCharPtr.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetCharPtr()
{
    CBufferHelper cbh;
    srand((unsigned)time(NULL));
    const std::vector<char>& InValue = m_BufVec[(rand() % m_NumLen)];
    cbh.Put(&*InValue.begin());
    const char* pBuf = cbh.GetBuffer();
    int BufLen = cbh.GetLen() - sizeof(int);
    CPPUNIT_ASSERT(0 == strncmp(pBuf + sizeof(int), &*InValue.begin(), BufLen));
}

/**
 * @brief test the function of PutGetCharPtrWithLenInTemplate.
 * @return no.
 */
void BufferHelperCppUnitTest::testPutGetCharPtrWithLenInTemplate()
{
    CBufferHelper cbh;
    srand((unsigned)time(NULL));
    const std::vector<char>& InValue = m_BufVec[(rand() % m_NumLen)];
    cbh.Put(&*InValue.begin(), InValue.size());
    const char* pBuf = cbh.GetBuffer();
    int BufLen = cbh.GetLen() - sizeof(int);
    CPPUNIT_ASSERT(0 == strncmp(pBuf, &*InValue.begin(), BufLen));
}

/**
 * @brief main function.
 * @return int.
 */
int main(int /*argc*/, char* /*argv*/[])
{
    bool wasSucessful = true;

    /// 2. Fixture和TestCaller组合
    {
        CppUnit::TestResult r;
        CppUnit::TestResultCollector rc;
        r.addListener(&rc);

        CppUnit::TestRunner runner;
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetInTemplate",
                           &BufferHelperCppUnitTest::testPutGetInTemplate));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetShort", &BufferHelperCppUnitTest::testPutGetShort));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetInt", &BufferHelperCppUnitTest::testPutGetInt));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetLongLong", &BufferHelperCppUnitTest::testPutGetLongLong));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetString", &BufferHelperCppUnitTest::testPutGetString));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetCharPtr", &BufferHelperCppUnitTest::testPutGetCharPtr));
        runner.addTest(new CppUnit::TestCaller<BufferHelperCppUnitTest>(
                           "testPutGetCharPtrWithLenInTemplate",
                           &BufferHelperCppUnitTest::testPutGetCharPtrWithLenInTemplate));
        runner.run(r);

        CppUnit::TextOutputter o(&rc, std::cout);
        o.write();

        wasSucessful =  rc.wasSuccessful();
    }

    printf("======================================================\n");

    /// 3. 借助CppUnit定义的一套辅助宏，将测试用命的定义和注册变得自动化
    {
        /// Get the top level suite from the registry
        CppUnit::Test* suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

        /// Adds the test to the list of test to run
        CppUnit::TextUi::TestRunner runner;
        runner.addTest(suite);

        /// Change the default outputter to a compiiler error format outputter
        runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));

        /// Run the tests.
        wasSucessful = runner.run();
    }

    /// Return error code 1 if the one of test failed.
    return wasSucessful ? 0 : 1;
}
