#include "../include/user.h"


#include <stdlib.h>
#include <string.h>

user_data_s *user_init() {
  user_data_s *user_data = (user_data_s*)malloc(sizeof(user_data_s));
  user_data->username = malloc(sizeof(USERNAME_LENGTH + 1));
  user_data->password = malloc(sizeof(PASSWORD_LENGTH + 1));
  user_data->first_name = malloc(sizeof(FIRST_NAME_LENGTH + 1));
  user_data->last_name = malloc(sizeof(LAST_NAME_LENGTH + 1));

  memset(user_data->username, 0, sizeof(USERNAME_LENGTH + 1));
  memset(user_data->password, 0, sizeof(PASSWORD_LENGTH + 1));
  memset(user_data->first_name, 0, sizeof(FIRST_NAME_LENGTH + 1));
  memset(user_data->last_name, 0, sizeof(LAST_NAME_LENGTH + 1));

  return user_data;
}

void *user_free(user_data_s *user_data) {
  free(user_data->username);
  free(user_data->password);
  free(user_data->first_name);
  free(user_data->last_name);

  free(user_data);
}
