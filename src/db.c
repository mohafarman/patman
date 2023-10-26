#include "../include/db.h"

// Initialization
//--------------------------------------------------------------------------------------
db_data_s *db_init() {
  db_data_s *db_data = (db_data_s*)malloc(sizeof(db_data_s));

  db_data->name = malloc(strlen(DATABASE_NAME) + 1);

  strcpy(db_data->name, DATABASE_NAME);

  /* Opens database */
  /* If no database exists, it will be created */
  int rc = sqlite3_open(db_data->name, &db_data->db);

  if (rc != SQLITE_OK) {

    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db_data->db));
    sqlite3_close(db_data->db);

    db_data->status = 0;
    return db_data;
  }

  const char* table_credentials = "credentials";

  /* Check if credentials table exists */
  if (db_table_exists(db_data->db, table_credentials) == 1) {
    /* If not then create one */
    if (db_table_create(db_data->db, table_credentials) == 0) {
      db_data->status = true;
      return db_data;
    }
  }

  /* Table credentials exists */
  db_data->status = true;
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
int db_table_exists(sqlite3 *db, const char *table_name) {
  char query[100];
  sqlite3_stmt *stmt;
  int result;

  snprintf(query, sizeof(query), "SELECT name FROM sqlite_master WHERE type='table' AND name='%s';", table_name);

  result = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
  if (result != SQLITE_OK) {
    fprintf(stderr, "Error preparing query: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  /* Check results of the query */
  result = sqlite3_step(stmt);
  if (result == SQLITE_ROW) {
    /* Table exists */
    sqlite3_finalize(stmt);
    return 0;
  }

  /* Table does not exist */
  sqlite3_finalize(stmt);
  return 1;
}

int db_table_create(sqlite3 *db, const char *table_name) {
  char query[100];
  // sqlite3_stmt *stmt;
  char *err_msg = 0;
  int result;

  snprintf(query, sizeof(query), "CREATE TABLE '%s'(Id INTEGER PRIMARY KEY, Username TEXT, Password TEXT);", table_name);

  result = sqlite3_exec(db, query, 0, 0, &err_msg);

    if (result != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return 1;

    } else {
        fprintf(stdout, "Table %s created successfully\n", table_name);
        return 0;
    }
}
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
