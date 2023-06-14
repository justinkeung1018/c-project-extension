
// #include "raylib.h"

// #define MAX_INPUT_CHARS     9

// int main(void) {
//   InitWindow(0, 0, "raylib [text] example - input box");
//   ToggleFullscreen();

//   int screenWidth = GetScreenWidth();

//   char name[MAX_INPUT_CHARS + 1] = '\0';
//   int letterCount = 0;

//   Rectangle textBox = { screenWidth/2.0f - 100, 180, 225, 50 };
//   bool mouseOnText = false;

//   int framesCounter = 0;

//   SetTargetFPS(10);      

//   while (!WindowShouldClose())  
//   {
//       // Update
//       //----------------------------------------------------------------------------------
//       if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
//       else mouseOnText = false;

//       if (mouseOnText)
//       {
//           // Set the window's cursor to the I-Beam
//           SetMouseCursor(MOUSE_CURSOR_IBEAM);

//           // Get char pressed (unicode character) on the queue
//           int key = GetCharPressed();

//           // Check if more characters have been pressed on the same frame
//           while (key > 0)
//           {
//               // NOTE: Only allow keys in range [32..125]
//               if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
//               {
//                   name[letterCount] = (char)key;
//                   name[letterCount+1] = '\0'; // Add null terminator at the end of the string.
//                   letterCount++;
//               }

//               key = GetCharPressed();  // Check next character in the queue
//           }

//           if (IsKeyPressed(KEY_BACKSPACE))
//           {
//               letterCount--;
//               if (letterCount < 0) letterCount = 0;
//               name[letterCount] = '\0';
//           }
//       }
//       else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

//       if (mouseOnText) framesCounter++;
//       else framesCounter = 0;

//       BeginDrawing();

//           ClearBackground(RAYWHITE);

//           DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, GRAY);

//           DrawRectangleRec(textBox, LIGHTGRAY);
//           if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
//           else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

//           DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

//           DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, DARKGRAY);

//           if (mouseOnText)
//           {
//               if (letterCount < MAX_INPUT_CHARS)
//               {
//                   // Draw blinking underscore char
//                   if (((framesCounter/20)%2) == 0) DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
//               }
//               else DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
//           }

//       EndDrawing();
//   }

//   CloseWindow();        
//   return 0;
// }

// // Check if any key is pressed
// // NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
// bool IsAnyKeyPressed() {
//   bool keyPressed = false;
//   int key = GetKeyPressed();

//   if ((key >= 32) && (key <= 126)) {
//     keyPressed = true;
//   }

//   return keyPressed;
// }