#include "mysql/my_global.h"
#include "mysql/mysql.h"

int main(int argc, char **argv)
{
    printf("MySQL client version: %s\n", mysql_get_client_info());
}
