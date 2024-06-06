#include <fmt/core.h>
#include <raylib.h>
#include <raygui.h>
#include <Notes.hpp>
#include <Menu.hpp>




void test();

int main() {

    InitWindow(800, 800, "Sticky Notes");
    NoteManger nm;

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
        Menu::initMenu(Menu::menu_bar_items,2,nm);
        nm.draw();
        EndDrawing();
    }
}
