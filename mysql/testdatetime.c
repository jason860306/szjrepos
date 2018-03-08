#include <mysql/my_global.h>
#include <mysql/mysql.h>

int main(void)
{
	MYSQL *conn;
	conn = mysql_init(NULL);
	mysql_real_connect(conn, "localhost", "root", "Szj0306", "test", 0, NULL, 0);
	mysql_query(conn, "create table testnull(`time` datetime not null default '0000-00-00 00:00:00');");
	mysql_close(conn);

	return 0;
}
