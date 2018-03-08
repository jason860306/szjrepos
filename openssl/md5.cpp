#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>

int main(int argc, char* argv[])
{
    MD5_CTX ctx;
    const char* data = (argc == 2 ? argv[1] : "123");
    unsigned char md[16];
    char buf[33] = {'\0'};
    char tmp[3] = {'\0'};
    int i;

    MD5_Init(&ctx);
    MD5_Update(&ctx, data, strlen(data));
    MD5_Final(md, &ctx);

    printf("orgin:\t");
    for (i = 0; i < 16; ++i) {
        printf("%d", md[i]);
        sprintf(tmp, "%d", md[i]);
        strcat(buf, tmp);
    }
    printf("\nformat:\t%s\n", buf);

    return 0;
}
