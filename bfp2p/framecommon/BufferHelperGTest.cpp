#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <framecommon/BufferHelper.h>
#include <gtest/gtest.h>

using namespace MYFRAMECOMMON;

class BufferHelperGTestInt : public ::testing::TestWithParam<int>
{

};

TEST_P(BufferHelperGTestInt, TestGetPutInt)
{
    int ivalue = GetParam();
    CBufferHelper cbh;
    cbh.Put(ivalue);
    int ovalue = 0;
    ASSERT_TRUE(0 == cbh.Get(ovalue));
    EXPECT_EQ(ivalue, ovalue);
}

INSTANTIATE_TEST_CASE_P(GetPutInt, BufferHelperGTestInt,
//                        ::testing::Range((int)INT_MIN, (int)INT_MAX));
                        ::testing::Range((int)0, (int)30));

class BufferHelperGTestShort : public ::testing::TestWithParam<short>
{

};

TEST_P(BufferHelperGTestShort, TestGetPutShort)
{
    short ivalue = GetParam();
    CBufferHelper cbh;
    cbh.Put(ivalue);
    short ovalue = 0;
    ASSERT_TRUE(0 == cbh.Get(ovalue));
    EXPECT_EQ(ivalue, ovalue);
}

INSTANTIATE_TEST_CASE_P(GetPutShort, BufferHelperGTestShort,
//                        ::testing::Range((short)SHRT_MIN, (short)SHRT_MAX));
                        ::testing::Range((short)20, (short)50));


class BufferHelperGTestString : public ::testing::TestWithParam<std::string>
{
public:
    virtual void SetUp() {
        std::size_t len = 20;
        char *TmpBuf = new char[len + 1];
        memset(TmpBuf, 0, len + 1);
        do {
            srand((unsigned)time(NULL));
            for (char i = 0; i < (char)len; ++i) {
                TmpBuf[i] = (char)(rand() % CHAR_MAX);
            }
            m_StringVec.push_back(std::string(TmpBuf));
            memset(TmpBuf, 0, len + 1);
        } while (m_StringVec.size() != len);
        delete TmpBuf;
        TmpBuf = NULL;
    }

    virtual void TearDown() {
        m_StringVec.clear();
    }
public:
    static std::vector<std::string> m_StringVec;
};

std::vector<std::string> BufferHelperGTestString::m_StringVec;
const char *pBuf[] = { "qajwoegfqjwegoqjweogf", "jwogjqowegjqowegj" };
std::string pStr[] = {
    std::string("sjfawejgfawe"),
    std::string("jsweofjweog"),
    std::string("jwoqigjowegfj"),
    std::string("fjwoqargejqowegjqow"),
    std::string("wsjegfoqwjegoqweg"),
    std::string("egjoqwjegoqwjegoqwe"),
    std::string("sjgfoqawgjeoqiwgjeo")
};

TEST_P(BufferHelperGTestString, TestGetPutString)
{
    std::string ivalue = GetParam();
    CBufferHelper cbh;
    cbh.Put(ivalue);
    std::string ovalue;
    ASSERT_TRUE(0 == cbh.Get(ovalue));
    EXPECT_EQ(ivalue, ovalue);
}

INSTANTIATE_TEST_CASE_P(GetPutString, BufferHelperGTestString, ::testing::ValuesIn(
//                            BufferHelperGTestString::m_StringVec.begin(),
//                            BufferHelperGTestString::m_StringVec.end()));
                            pStr));
