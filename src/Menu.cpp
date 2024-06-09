#include <Menu.hpp>

#include <fmt/core.h>
#include <raylib.h>

#undef  RAYGUI_IMPLEMENTATION
#include <raygui.h>


void Menu::initMenu(std::array<const char *, 3> &items,size_t n,NoteManger &nm){
     listView.bounds = Rectangle{0,30,40,60};
     listView.text = "Save \n Load \n Exit";
     listView.active = false;

    for (size_t i = 0; i < n; i ++){

        if (GuiButton(Rectangle{40.0f*i,0,40,30}, items[i])){
            MENU_ITEM menuItem = menuItems[items[i]];
            switch (menuItem) {
                case MENU_ITEM::SAVE : {
                                           auto path = exec("zenity --file-selection --save");
                                           fmt::println("Saving to: {}",path);
                                           nm.save(path);

                                           break;
                                       };
                case MENU_ITEM::LOAD : {
                                           auto path = exec("zenity --file-selection");
                                           fmt::println("Loading from: {}",path);
                                           nm.load(path);

                                           break;
                                       };
                case MENU_ITEM::EXIT:{
                                         CloseWindow();
                                         break;
                                     };
                default:{
                            break;
                        };
            }

        }
    }

}
