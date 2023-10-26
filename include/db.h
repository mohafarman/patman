#ifndef DB_H_
#define DB_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>

#define DATABASE_NAME "bin/test.db"

typedef struct {
  char *name;
  sqlite3 *db;
  bool status;    /* Status of database. false if there is an error, true if all good */
} db_data_s;

// Initialization
//--------------------------------------------------------------------------------------
db_data_s *db_init();
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
char *db_print_sqlite3_version();

int db_table_exists(sqlite3 *db, const char *table_name);
int db_table_create(sqlite3 *db, const char *table_name);
//--------------------------------------------------------------------------------------

// De-Initialization
//--------------------------------------------------------------------------------------
void db_free(db_data_s *db_data);
//--------------------------------------------------------------------------------------

#endif // DB_H_
