#include "../include/db.h"

// Initialization
//--------------------------------------------------------------------------------------
db_data_s *db_init() {
  db_data_s *db_data = (db_data_s*)malloc(sizeof(db_data_s));

  db_data->name = malloc(strlen(DATABASE_NAME) + 1);

  strcpy(db_data->name, DATABASE_NAME);

  /* Opens database */
  sqlite3 *db;
  // sqlite3_stmt *res;
  // char *err_msg;

  int rc = sqlite3_open(db_data->name, &db);

  if (rc != SQLITE_OK) {

    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);

    db_data->status = 1;
    return db_data;
  }

  /* Check if credentials table exists */

  db_data->status = 0;
  return db_data;
}
//--------------------------------------------------------------------------------------

// Printing
//--------------------------------------------------------------------------------------
char *db_print_sqlite3_version() {
  char *text = "database sqlite3 version: ";

  size_t length = strlen(text) + strlen(sqlite3_libversion()) + 1;

  char *result = malloc(length);
  strcpy(result, text);
  strcat(result, sqlite3_libversion());

  return result;
}
//--------------------------------------------------------------------------------------

// Manipulation
//--------------------------------------------------------------------------------------
// TODO int db_table_exists()
//--------------------------------------------------------------------------------------

// De-Initialization
//--------------------------------------------------------------------------------------
void db_free(db_data_s *db_data) {
  if (db_data != NULL) {
    /* Free members */
    free(db_data->name);

    /* Free the struct */
    free(db_data);
  }
}
//--------------------------------------------------------------------------------------
