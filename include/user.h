#ifndef USER_H_
#define USER_H_

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define FIRST_NAME_LENGTH 32
#define LAST_NAME_LENGTH 32

typedef struct {
  char *username;
  char *password;
  int username_letter_count;
  int password_letter_count;
  char *first_name;
  char *last_name;
} user_data_s;

user_data_s *user_init();

void *user_free(user_data_s *user_data);

#endif // USER_H_
