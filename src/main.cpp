#include <fmt/core.h>
#include <raylib.h>
#include <Notes.hpp>
#include <Menu.hpp>




void test();
void test2();

int main() {
    /* test2();
return 0; */
    InitWindow(800, 800, "Sticky Notes");
    NoteManger nm;

    while(!WindowShouldClose()){
        nm.update();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        nm.draw();
        Menu::GuiMenu(Menu::menu_bar_items,3,nm);
        EndDrawing();
    }

    
}
