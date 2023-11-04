#include "../include/gui.h"

gui_login_window_s *gui_login_window_init() {
  Rectangle username_box = { SCREEN_WIDTH/8.0f, SCREEN_HEIGHT/4.0f + 30, 225, 50 };
  bool mouse_on_username_box = false;

  Rectangle password_box = { SCREEN_WIDTH/8.0f, SCREEN_HEIGHT/4.0f + 120, 225, 50 };
  bool mouse_on_password_box = false;

  Rectangle button_sign_in = { SCREEN_WIDTH/8.0f, SCREEN_HEIGHT/4.0f + 180, 100, 40 };
  bool mouse_on_button_sign_in = false;

  bool sign_in_failed = false;

  gui_login_window_s *gui_login_window = (gui_login_window_s*)malloc(sizeof(gui_login_window_s));
  gui_login_window->username_box = username_box;
  gui_login_window->password_box = password_box;
  gui_login_window->button_sign_in = button_sign_in;
  gui_login_window->mouse_on_username_box = mouse_on_username_box;
  gui_login_window->mouse_on_password_box = mouse_on_password_box;
  gui_login_window->mouse_on_button_sign_in = mouse_on_button_sign_in;
  gui_login_window->sign_in_failed = sign_in_failed;

  return gui_login_window;
}

void gui_login_update(gui_login_window_s *gui_login, user_data_s *user_data) {

  /* TODO: Add functionality to tab between boxes */
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    if (CheckCollisionPointRec(GetMousePosition(), gui_login->username_box)) {
      gui_login->mouse_on_username_box = true;
      gui_login->mouse_on_password_box = false;
      gui_login->mouse_on_button_sign_in = false;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), gui_login->password_box)) {
      gui_login->mouse_on_username_box = false;
      gui_login->mouse_on_password_box = true;
      gui_login->mouse_on_button_sign_in = false;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), gui_login->button_sign_in)) {
      gui_login->mouse_on_password_box = false;
      gui_login->mouse_on_username_box = false;
      gui_login->mouse_on_button_sign_in = true;
    }
    else {
      gui_login->mouse_on_password_box = false;
      gui_login->mouse_on_username_box = false;
      gui_login->mouse_on_button_sign_in = false;
    }
  }

  if (IsKeyPressed(KEY_TAB)) {
    if (gui_login->mouse_on_username_box) {
      gui_login->mouse_on_username_box = false;
      gui_login->mouse_on_password_box = true;
    } else if (gui_login->mouse_on_password_box) {
      gui_login->mouse_on_username_box = true;
      gui_login->mouse_on_password_box = false;
    }
    else {
      gui_login->mouse_on_username_box = true;
      gui_login->mouse_on_password_box = false;
    }
  }

  if (gui_login->mouse_on_username_box || gui_login->mouse_on_password_box) {
    // Set the window's cursor to the I-Beam
    SetMouseCursor(MOUSE_CURSOR_IBEAM);

    // Get char pressed (unicode character) on the queue
    int key = GetCharPressed();

    // Check if more characters have been pressed on the same frame
    while (key > 0) {

      if ((key >= 32) && (key <= 125)) {
        if (gui_login->mouse_on_username_box && user_data->username_letter_count < USERNAME_LENGTH)
          {
            user_data->username[user_data->username_letter_count] = (char)key;
            user_data->username[user_data->username_letter_count + 1] = '\0';
            user_data->username_letter_count++;
          }
        else if (gui_login->mouse_on_password_box && user_data->password_letter_count < PASSWORD_LENGTH)
          {
            user_data->password[user_data->password_letter_count] = (char)key;
            user_data->password[user_data->password_letter_count + 1] = '\0';
            user_data->password_letter_count++;
          }

      }
      key = GetCharPressed();
    }

    if (IsKeyDown(KEY_BACKSPACE) && gui_login->mouse_on_username_box) {
      user_data->username_letter_count--;
      if (user_data->username_letter_count < 0) user_data->username_letter_count = 0;
      user_data->username[user_data->username_letter_count] = '\0';
    }
    else if (IsKeyDown(KEY_BACKSPACE) && gui_login->mouse_on_password_box) {
      user_data->password_letter_count--;
      if (user_data->password_letter_count < 0) user_data->password_letter_count = 0;
      user_data->password[user_data->password_letter_count] = '\0';

    }
  } else {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
  }
}

void gui_login_draw(gui_login_window_s *gui_login, user_data_s *user_data) {

  /* -20 for vertical offset */
  DrawText("Username", (int)gui_login->username_box.x, (int)gui_login->username_box.y - 20, FONT_SIZE, GRAY);
  DrawRectangleRec(gui_login->username_box, LIGHTGRAY);

  DrawText("Password", (int)gui_login->password_box.x, (int)gui_login->password_box.y - 20, FONT_SIZE, GRAY);
  DrawRectangleRec(gui_login->password_box, LIGHTGRAY);

  DrawRectangleRec(gui_login->button_sign_in, BLUE);
  /* Hard coded to center the text in the rectangle */
  DrawText("Sign in", (int)gui_login->button_sign_in.x + 15, (int)gui_login->button_sign_in.y + 10, FONT_SIZE, WHITE);

  if (gui_login->mouse_on_username_box) {
    DrawRectangleLines((int)gui_login->username_box.x, (int)gui_login->username_box.y, (int)gui_login->username_box.width, (int)gui_login->username_box.height, RED);
  }
  else if (gui_login->mouse_on_password_box) {
    DrawRectangleLines((int)gui_login->password_box.x, (int)gui_login->password_box.y, (int)gui_login->password_box.width, (int)gui_login->password_box.height, RED);
  }
  else if (gui_login->mouse_on_button_sign_in) {
    DrawRectangleLines((int)gui_login->button_sign_in.x, (int)gui_login->button_sign_in.y, (int)gui_login->button_sign_in.width, (int)gui_login->button_sign_in.height, RED);
  }

  /* Hard coded to fit the input boxes */
  DrawText(user_data->username, (int)gui_login->username_box.x + 5, (int)gui_login->username_box.y + 8, 20, MAROON);
  DrawText(user_data->password, (int)gui_login->password_box.x + 5, (int)gui_login->password_box.y + 8, 20, MAROON);

  if (gui_login->sign_in_failed) {
    DrawText("Failed to sign in!", (int)gui_login->button_sign_in.x, (int)gui_login->button_sign_in.y + 50, FONT_SIZE, RED);
  }

}

gui_hud_s gui_hud_init() {
  // gui_hud_s *gui_hud = (gui_hud_s*)malloc(sizeof(gui_hud_s));
  gui_hud_s gui_hud = { 0 };

  // gui_hud.texture_logo = (Texture2D*)malloc(sizeof(900 * 820));
  gui_hud.texture_logo = LoadTexture("assets/caduceus_resize.png");

  Rectangle bar_top = {0, 0, SCREEN_WIDTH, gui_hud.texture_logo.height};
  gui_hud.bar_top = bar_top;

  Rectangle bar_bottom = {0, SCREEN_HEIGHT - gui_hud.texture_logo.height/1.5, SCREEN_WIDTH, gui_hud.texture_logo.height};
  gui_hud.bar_bottom = bar_bottom;

  return gui_hud;
}

void gui_hud_draw(gui_hud_s *gui_hud) {
  DrawRectangleRec(gui_hud->bar_top, BLUE);
  DrawTexture(gui_hud->texture_logo, 0, 0, WHITE);

  DrawRectangleRec(gui_hud->bar_bottom, DARKBLUE);

  DrawText("Patman is a patient management system using the Raylib library for GUI and sqlite3 as database.",
           10, SCREEN_HEIGHT - 60, 12, LIGHTGRAY);
  DrawText("Developed and maintained by Mohamad Farman.",
           10, SCREEN_HEIGHT - 48, 12, LIGHTGRAY);
  // DrawTextureRec(gui_hud->texture_logo, (Rectangle){0, 0, 100, 100}, (Vector2){10.0f, 10.0f}, WHITE);
}

void gui_hud_draw_info() {
  DrawText("Hello!!", 10, SCREEN_HEIGHT - 20, 20, LIGHTGRAY);
}

void gui_hud_free(gui_hud_s *gui_hud) {
  /* Must free texture specifically as well */
  free(gui_hud);
}

Rectangle gui_create_input_box(const char *name, float pos_x, float pos_y, float width, float height) {
  DrawText(name, pos_x, pos_y, FONT_SIZE, GRAY);
  Rectangle box = { pos_x, pos_y, width, height };

  return box;
}
