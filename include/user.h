#ifndef USER_H_
#define USER_H_

#define USERNAME_LENGTH 32
#define PASSWORD_LENGTH 32
#define FIRST_NAME_LENGTH 32
#define LAST_NAME_LENGTH 32

typedef struct {
  char *username;
  char *password;
  char *first_name;
  char *last_name;
  int username_letter_count;
  int password_letter_count;
  int first_name_letter_count;
  int last_name_letter_count;
} user_data_s;

user_data_s *user_init();

void user_free(user_data_s *user_data);

#endif // USER_H_
