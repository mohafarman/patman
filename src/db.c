#include "../include/db.h"

char *print_sqlite3_version() {
  char *text = "database sqlite3 version: ";

  size_t length = strlen(text) + strlen(sqlite3_libversion()) + 1;

  char *result = malloc(length);
  strcpy(result, text);
  strcat(result, sqlite3_libversion());

  return result;
}
