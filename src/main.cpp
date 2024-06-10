#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_TEXTBOX_AUTO_CURSOR_DELAY 40
#define RAYGUI_TEXTBOX_AUTO_CURSOR_COOLDOWN 400
#include <raygui.h>
#include <iostream>

#include <Notes.hpp>
#include <Menu.hpp>




void test();
void test2();

int main(int argv, char ** argc) {

    /* test2();
return 0; */
    NoteManger nm;
    if (argv > 1){
        std::cout << "File: " << *(argc + 1) << std::endl;
        nm.load(*(argc + 1));
    }

    InitWindow(800, 800, "Sticky Notes");


    while(!WindowShouldClose()){
        nm.update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        nm.draw();
        Menu::GuiMenu(Menu::menu_bar_items,5,nm);
        EndDrawing();
    }

    
}
