#include <mysql/my_global.h>
#include <mysql/mysql.h>

int main(int argc, char **argv)
{
    MYSQL *conn;

    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "Szj0306", "testdb", 0, NULL, 0);

    mysql_query(conn, "CREATE TABLE writers(name VARCHAR(25))");
    mysql_query(conn, "CREATE TABLE friends(id int not null primary key auto_increment,"
                " name varchar(20), age int)");

    mysql_query(conn, "INSERT INTO writers VALUES('Leo Tolstoy')");
    mysql_query(conn, "INSERT INTO writers VALUES('Jack London')");
    mysql_query(conn, "INSERT INTO writers VALUES('Honore de Balzac')");
    mysql_query(conn, "INSERT INTO writers VALUES('Lion Feuchtwanger')");
    mysql_query(conn, "INSERT INTO writers VALUES('Emile Zola')");

    mysql_query(conn, "INSERT INTO friends(name, age) values('Tom', 25)");
    mysql_query(conn, "INSERT INTO friends(name, age) values('Elisabeth', 32)");
    mysql_query(conn, "INSERT INTO friends(name, age) values('Jane', 22)");
    mysql_query(conn, "INSERT INTO friends(name, age) values('Luke', 28)");

    mysql_query(conn, "create table images(id int not null primary key, data mediumblob);");

    int len, size;
    char data[1000*1024];
    char chunk[2*1000*1024+1];
    char query[1024*5000];

    FILE *fp;
    fp = fopen("image.png", "rb");
    size = fread(data, 1, 1024*1000, fp);

    mysql_real_escape_string(conn, chunk, data, size);

    char *stat = "INSERT INTO images(id, data) VALUES('1', '%s')";
    len = snprintf(query, sizeof(stat) + sizeof(chunk), stat, chunk);

    mysql_real_query(conn, query, len);

    fclose(fp);

    mysql_close(conn);
}
