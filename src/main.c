#include "../include/main.h"
#include "../include/user.h"
#include "../include/gui.h"
#include "../include/db.h"

#include <stdio.h>
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

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
  /* Load font */

  gui_hud_s gui_hud = gui_hud_init();

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

            /* Empty the input boxes and reset input */
            user_data->username[0] = '\0';
            user_data->password[0] = '\0';
            user_data->username_letter_count = 0;
            user_data->password_letter_count = 0;

            fprintf(stderr, "Failed to sign in!\n");
            break;
          }

          program_state->signed_in = true;
          gui_state = STATE_LOGIN;
          fprintf(stderr, "Signed in!\n");
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

      /* Draw the HUD */
      gui_hud_draw(&gui_hud);

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

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  UnloadTexture(gui_hud.texture_logo_alive);
  UnloadTexture(gui_hud.texture_logo_dead);

  // Raylib De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  // Debugging
  fprintf(stdout, "username: %s\npassword: %s\nfirst name: %s\nlast name: %s\n",
          user_data->username, user_data->password, user_data->first_name, user_data->last_name);

  // Sqlite De-Initialization
  //--------------------------------------------------------------------------------------
  db_free(db);
  free(sqlite_version);
  //--------------------------------------------------------------------------------------

  // gui_hud_free(&gui_hud);
  user_free(user_data);

  return 0;
}

program_state_s *program_state_init() {
  program_state_s *program_state = (program_state_s*)malloc(sizeof(program_state_s));
  program_state->signed_in = false;

  return program_state;
}
