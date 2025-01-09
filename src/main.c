/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" // utility header for SearchAndSetResourceDir

int main()
{
    // Tell the window to use vsync and work on high DPI displays
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TOPMOST | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT | FLAG_FULLSCREEN_MODE | FLAG_WINDOW_MOUSE_PASSTHROUGH);

    // Create the window and OpenGL context
    InitWindow(1920, 1080, "Hello Raylib");

    // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
    SearchAndSetResourceDir("resources");

    // Load a texture from the resources directory
    Texture wabbit = LoadTexture("wabbit_alpha.png");

    Camera camera = { 0 };
    camera.position = (Vector3) { 0.0f, 50.0f, -120.0f }; // Camera position perspective
    camera.target = (Vector3) { 0.0f, 0.0f, 0.0f }; // Camera looking at point
    camera.up = (Vector3) { 0.0f, 1.0f, 0.0f }; // Camera up vector (rotation towards target)
    camera.fovy = 30.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera type

    Model model = LoadModel("plane.obj"); // Load model
    Texture2D texture = LoadTexture("plane_diffuse.png"); // Load model texture
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture

    float pitch = 0.0f;
    float roll = 0.0f;
    float yaw = 0.0f;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // game loop
    while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
    {
        //UpdateCamera(&camera, CAMERA_ORBITAL);
        yaw += 0.5f; // 每帧增加0.5度
        if (yaw >= 360.0f)
            yaw -= 360.0f; // 保持角度在0-360度之间
        model.transform = MatrixRotateXYZ((Vector3) { DEG2RAD * pitch, DEG2RAD * yaw, DEG2RAD * roll });
        BeginDrawing();
        //// draw some text using the default font
        //DrawText("Hello Raylib", 200, 200, 20, WHITE);

        ////// draw our texture to the screen
        //DrawTexture(wabbit, 400, 200, WHITE);
       
        // Setup the back buffer for drawing (clear color and depth buffers)
        ClearBackground(BLANK);
        BeginMode3D(camera);

        DrawModel(model, (Vector3) { 0.0f, -8.0f, 0.0f }, 1.0f, WHITE); // Draw 3d model with texture
        //DrawGrid(10, 10.0f);

        EndMode3D();
        

        // end the frame and get ready for the next one  (display frame, poll input, etc...)
        EndDrawing();
    }

    // cleanup
    // unload our texture so it can be cleaned up
    UnloadModel(model); // Unload model data
    UnloadTexture(wabbit);

    // destroy the window and cleanup the OpenGL context
    CloseWindow();
    return 0;
}
