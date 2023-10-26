#include "../include/main.h"
#include "../include/user.h"
#include "../include/db.h"

#include <stdio.h>
#include <raylib.h>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // Sqlite Initialization
  //--------------------------------------------------------------------------------------
  db_data_s *db_data = db_init();
  if (db_data->status == false) {
    fprintf(stderr, "Failed database initialization. Terminating program.\n");
    return 1;
  }

  char *sqlite_version = db_print_sqlite3_version();
  //--------------------------------------------------------------------------------------

  // Program Initialization
  //--------------------------------------------------------------------------------------
  user_data_s *user_data = user_init();
  int username_letter_count = 0;
  int password_letter_count = 0;
  program_state_s *program_state = program_state_init();
  (void)program_state;
  //--------------------------------------------------------------------------------------

  // Raylib Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Patman login screen");

  Rectangle username_box = { screenWidth/4, screenHeight/4 + 30, 225, 50 };
  Rectangle password_box = { screenWidth/2.0f - 100, 200, 225, 50 };
  bool mouse_on_username_box = false;
  bool mouse_on_password_box = false;

  int frames_counter = 0;

  SetTargetFPS(10);               // Set our program to run at 10 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main program loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      //----------------------------------------------------------------------------------
      // TODO: Update your variables here
      if (CheckCollisionPointRec(GetMousePosition(), username_box)) {
        mouse_on_username_box = true;
        mouse_on_password_box = false;
      } else if (CheckCollisionPointRec(GetMousePosition(), password_box)) {
        mouse_on_password_box = true;
        mouse_on_username_box = false;
      } else {
        mouse_on_username_box = false;
        mouse_on_password_box = false;
      }

      if (mouse_on_username_box || mouse_on_password_box) {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0) {
          // NOTE: Only allow keys in range [32..125]
          if ((key >= 32) && (key <= 125)) {
            if (mouse_on_username_box && username_letter_count < USERNAME_LENGTH)
              {
                user_data->username[username_letter_count] = (char)key;
                user_data->username[username_letter_count + 1] = '\0';
                username_letter_count++;
              }
            else if (mouse_on_password_box && password_letter_count < PASSWORD_LENGTH)
              {
                user_data->password[password_letter_count] = (char)key;
                user_data->password[password_letter_count + 1] = '\0';
                password_letter_count++;
              }

          }
          key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && mouse_on_username_box) {
          username_letter_count--;
          if (username_letter_count < 0) username_letter_count = 0;
          user_data->username[username_letter_count] = '\0';
        }
        else if (IsKeyPressed(KEY_BACKSPACE) && mouse_on_password_box) {
          password_letter_count--;
          if (password_letter_count < 0) password_letter_count = 0;
          user_data->password[password_letter_count] = '\0';

        }
      } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
      }

      if (mouse_on_username_box || mouse_on_password_box) {
        frames_counter++;
        fprintf(stdout, "Username: %s\n", user_data->username);
      } else {
        frames_counter = 0;
      }

      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(RAYWHITE);

      /* Information */
      // DrawText(sqlite_version, 2, 2, 10, LIGHTGRAY);

      DrawText("Username", screenWidth/4, screenHeight/4, 20, GRAY);

      DrawRectangleRec(username_box, LIGHTGRAY);

      if (mouse_on_username_box) {
        DrawRectangleLines((int)username_box.x, (int)username_box.y, (int)username_box.width, (int)username_box.height, RED);
      } else {
        DrawRectangleLines((int)username_box.x, (int)username_box.y, (int)username_box.width, (int)username_box.height, DARKGRAY);
      }

      DrawText(user_data->username, (int)username_box.x + 5, (int)username_box.y + 8, 20, MAROON);

      if (mouse_on_username_box) {
        if (username_letter_count < USERNAME_LENGTH) {
          // Draw blinking underscore char
          // if (((frames_counter/20)%2) == 0) DrawText("_", (int)username_box.x + 8 + MeasureText(user_data->username, 20), (int)username_box.y + 12, 20, MAROON);
        }
        else {
          DrawText("Press BACKSPACE to delete chars...", 230, 200, 20, GRAY);
        }
      }

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // Raylib De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  // Sqlite De-Initialization
  //--------------------------------------------------------------------------------------
  db_free(db_data);
  free(sqlite_version);
  //--------------------------------------------------------------------------------------

  return 0;
}

program_state_s *program_state_init() {
  program_state_s *program_state = (program_state_s*)malloc(sizeof(program_state_s));
  program_state->signed_in = false;

  return program_state;
}
