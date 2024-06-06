#include <cstddef>
#include <fstream>
#include <raylib.h>
#include <raygui.h>
#include <array>


#include <fmt/core.h>
#include <unordered_map>


class Notes{
    public:
        Rectangle bounds;
        std::string text;
};




void test();

int main() {


    InitWindow(800, 800, "Sticky Notest");


    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        initMenu(menu_bar_items,2);
        // GuiListView(listState.bounds,listState.text,listState.scrollIndex,listState.active);
        // GuiDropdownBox(listState.bounds,listState.text,listState.active, true);

        EndDrawing();

    }

}
