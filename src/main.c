#include "../include/main.h"
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

  // Raylib Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Patman login screen");

  SetTargetFPS(10);               // Set our program to run at 10 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main program loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      //----------------------------------------------------------------------------------
      // TODO: Update your variables here
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(RAYWHITE);

      DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
      DrawText(sqlite_version, 190, 250, 20, LIGHTGRAY);

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
