#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

int main(int argc, char* argv[])
{
    const char* data = (argc == 2 ? argv[1] : "123");
    unsigned char md[16];
    int i;
    unsigned char tmp[3] = {'\0'};
    unsigned char buf[33] = {'\0'};
    MD5((const unsigned char*)data, strlen(data), md);
    for (i = 0; i < 16; ++i) {
        sprintf(tmp, "%2.2x", md[i]);
        strcat(buf, tmp);
    }
    printf("%s\n", buf);
    return 0;
}
