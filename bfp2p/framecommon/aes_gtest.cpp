#include <framecommon/AES.h>
#include <gtest/gtest.h>

using namespace MYFRAMECOMMON;

static std::string g_orgin_string("jqaweigfqjwoietjqowtejqowefjoaw");
static std::string g_encry_string;

TEST(AESTest, Encrypt)
{
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: %s\n", g_orgin_string.c_str());
    EXPECT_EQ(0, CAES::AESEncrypt(key, key.size() * 8, g_orgin_string.c_str(),
                                  g_orgin_string.size(), g_encry_string));
    printf("g_encry_string.size = %ld\nencry_string: ", g_encry_string.size());
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
    }
    printf("\n");
}

TEST(AESTest, Decrypt)
{
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: ");
    for (std::string::size_type i = 0; i < g_encry_string.size(); ++i) {
        printf("%02x", g_encry_string[i]);
    }
    printf("\n");
    std::string out_data;
    ASSERT_EQ(0, CAES::AESDecrypt(key, key.size() * 8, g_encry_string.c_str(),
                                  g_encry_string.size(), out_data));
    printf("decrypt_string.size = %ld\ndecrypt_string: %s\n",
           out_data.size(), out_data.c_str());

    //ASSERT_STREQ(out_data.c_str(), g_orgin_string.c_str());
    //ASSERT_EQ(out_data.size(), g_orgin_string.size());
    EXPECT_EQ(out_data.size(), g_orgin_string.size());
}

class AESTestF : public testing::Test
{
public:
    AESTestF() : m_orgin_string("jqaweigfqjwoietjqowtejqowefjoaw"), m_encry_string() {}
protected:
    std::string m_orgin_string;
    std::string m_encry_string;
};

TEST_F(AESTestF, Encrypt)
{
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: %s\n", m_orgin_string.c_str());
    EXPECT_EQ(0, CAES::AESEncrypt(key, key.size() * 8, m_orgin_string.c_str(),
                                  m_orgin_string.size(), m_encry_string));
    printf("m_encry_string.size = %ld\nencry_string: ", m_encry_string.size());
    for (std::string::size_type i = 0; i < m_encry_string.size(); ++i) {
        printf("%02x", m_encry_string[i]);
    }
    printf("\n");
}

TEST_F(AESTestF, Decrypt)
{
    std::string key;
    for (int i = 0; i < 16; ++i) {
        key.append(1, char(32 + i));
    }
    printf("orgin string: ");
    for (std::string::size_type i = 0; i < m_encry_string.size(); ++i) {
        printf("%02x", m_encry_string[i]);
    }
    printf("\n");
    std::string out_data;
    ASSERT_EQ(0, CAES::AESDecrypt(key, key.size() * 8, m_encry_string.c_str(),
                                  m_encry_string.size(), out_data));
    printf("decrypt_string.size = %ld\ndecrypt_string: %s\n",
           out_data.size(), out_data.c_str());

    //ASSERT_STREQ(out_data.c_str(), m_orgin_string.c_str());
    //ASSERT_EQ(out_data.size(), m_orgin_string.size());
    ASSERT_EQ(out_data.size(), m_orgin_string.size());
}
