#ifndef GUI_H_
#define GUI_H_

#include "../include/user.h"

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define INPUT_BOX_OFFSET_Y 90
#define FONT_SIZE 20

typedef enum {
  STATE_LOGIN,
  STATE_REGISTER,
  STATE_MAIN_MENU
} GUI_STATE;

typedef struct {
  Texture2D texture_logo_alive;
  Texture2D texture_logo_dead;
  Rectangle bar_top;
  Rectangle bar_bottom;
} gui_hud_s;

typedef struct {
  Rectangle username_box;
  Rectangle password_box;
  Rectangle first_name_box;
  Rectangle last_name_box;
  Rectangle button_sign_in;
  Rectangle button_register;
  bool mouse_on_username_box;
  bool mouse_on_password_box;
  bool mouse_on_first_name_box;
  bool mouse_on_last_name_box;
  bool mouse_on_button_sign_in;
  bool mouse_on_button_register;
  bool sign_in_failed;
} gui_login_window_s;

// gui_hud_s *gui_hud_init();
gui_hud_s gui_hud_init();

void gui_hud_draw(gui_hud_s *gui_hud);

gui_login_window_s *gui_login_window_init();

void gui_login_update(gui_login_window_s *gui_login, user_data_s *user_data);

void gui_login_draw(gui_login_window_s *gui_login, user_data_s *user_data);
void gui_login_sign_in_draw(gui_login_window_s *gui_login, user_data_s *user_data);
void gui_login_register_draw(gui_login_window_s *gui_login, user_data_s *user_data);

void gui_hud_free(gui_hud_s *gui_hud);

Rectangle gui_create_input_box(const char *name, float pos_x, float pos_y, float width, float height);

#endif // GUI_H_
