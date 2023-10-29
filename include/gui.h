#ifndef GUI_H_
#define GUI_H_

#include "../include/user.h"

#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FONT_SIZE 20

typedef enum {
  STATE_LOGIN,
  STATE_REGISTER,
  STATE_MAIN_MENU
} GUI_STATE;

typedef struct {
  Rectangle username_box;
  Rectangle password_box;
  bool mouse_on_username_box;
  bool mouse_on_password_box;
} gui_login_window_s;

gui_login_window_s gui_login_window();

void gui_login_update(gui_login_window_s gui_login, user_data_s *user_data);

void gui_login_draw(gui_login_window_s gui_login, user_data_s *user_data);

// user_data_s *gui_login_update(gui_login_window_s gui_login, user_data_s *user_data);
// char *gui_login_update(gui_login_window_s gui_login, user_data_s *user_data);

Rectangle gui_create_input_box(const char *name, float pos_x, float pos_y, float width, float height);

#endif // GUI_H_
