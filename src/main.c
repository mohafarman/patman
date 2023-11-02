#include "../include/main.h"
#include "../include/user.h"
#include "../include/gui.h"
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
  db_data_s *db= db_init();
  if (db->status == false) {
    fprintf(stderr, "Failed database initialization. Terminating program.\n");
    return 1;
  }

  char *sqlite_version = db_print_sqlite3_version();
  //--------------------------------------------------------------------------------------

  // Program Initialization
  //--------------------------------------------------------------------------------------
  user_data_s *user_data = user_init();
  user_data->username_letter_count = 0;
  user_data->password_letter_count = 0;
  program_state_s *program_state = program_state_init();
  (void)program_state;
  //--------------------------------------------------------------------------------------

  // Raylib/GUI Initialization
  //--------------------------------------------------------------------------------------
  GUI_STATE gui_state = STATE_LOGIN;
  gui_login_window_s *gui_login = gui_login_window_init();

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Patman");

  SetTargetFPS(20);               // Set our program to run at 10 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main program loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      switch(gui_state) {
      case STATE_LOGIN:
        /* Check if user is logged in, if true set state to MAIN_MENU */
        if (program_state->signed_in == true) {
          gui_state = STATE_MAIN_MENU;
        }

        gui_login_update(gui_login, user_data);

        /* Sign in button Or ENTER */
        if (IsKeyPressed(KEY_ENTER) || gui_login->mouse_on_button_sign_in) {
          gui_login->mouse_on_button_sign_in = false;
          gui_login->sign_in_failed = false;
          /* Check credentials with sqlite3 */
          if (db_table_query_sign_in(db->db, user_data->username, user_data->password) == 1) {
            /* Failed to sign in */
            program_state->signed_in = false;
            gui_login->sign_in_failed = true;
            printf("Failed to sign in!\n");
            break;
          }

          program_state->signed_in = true;
          gui_state = STATE_LOGIN;
          printf("Signed in!\n");
        }

        break;
      case STATE_MAIN_MENU:
        break;
      case STATE_REGISTER:
        break;
      }

      // Update
      //----------------------------------------------------------------------------------
      // TODO: Update your variables here

      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(RAYWHITE);

      switch(gui_state) {
      case STATE_LOGIN:
        /* Draw login screen */
        gui_login_draw(gui_login, user_data);
        break;
      case STATE_MAIN_MENU:
        /* Draw main menu screen */
        break;
      case STATE_REGISTER:
        /* Draw register screen */
        break;
      }

      /* Information */
      // DrawText(sqlite_version, 2, 2, 10, LIGHTGRAY);

      // DrawText("Username", screenWidth/4, screenHeight/4, 20, GRAY);

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // Raylib De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  // Debugging
  fprintf(stdout, "username: %s\npassword: %s\n", user_data->username, user_data->password);

  // Sqlite De-Initialization
  //--------------------------------------------------------------------------------------
  db_free(db);
  free(sqlite_version);
  //--------------------------------------------------------------------------------------

  user_free(user_data);

  return 0;
}

program_state_s *program_state_init() {
  program_state_s *program_state = (program_state_s*)malloc(sizeof(program_state_s));
  program_state->signed_in = false;

  return program_state;
}
