#include <mysql/my_global.h>
#include <mysql/mysql.h>

int main(int argc, char **argv)
{
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    int num_fields;
    int i;

    conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "Szj0306", "testdb", 0, NULL, 0);

    mysql_query(conn, "SELECT * FROM writers");
    result = mysql_store_result(conn);
    num_fields = mysql_num_fields(result);
/*    while ((row = mysql_fetch_row(result))) {
        for (i = 0; i < num_fields; ++i) {
            printf("%s ", row[i] ? row[i] : "NULL");
            fflush(stdout);
        }
        printf("\n");
    }
    printf("\n");
*/
    mysql_query(conn, "SELECT * FROM friends");
    mysql_free_result(result);
    result = mysql_store_result(conn);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result))) {
        for (i = 0; i < num_fields; ++i) {
            if (i == 0) {
                while (field = mysql_fetch_field(result)) {
                    printf("%s ", field->name);
                    fflush(stdout);
                }
                printf("\n");
            }
            printf("%s | ", row[i] ? row[i] : "NULL");
            fflush(stdout);
        }
    }
    printf("\n");

    FILE *fp;
    unsigned long *lengths;
    fp = fopen("image_db.png", "wb");
    
    mysql_query(conn, "SELECT data FROM images WHERE id = 1");
    mysql_free_result(result);
    result = mysql_store_result(conn);

    row = mysql_fetch_row(result);
    lengths = mysql_fetch_lengths(result);

    fwrite(row[0], lengths[0], 1, fp);
    fclose(fp);

    mysql_free_result(result);
    mysql_close(conn);
}
