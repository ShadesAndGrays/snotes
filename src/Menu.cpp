#include <Notes.hpp>

#include <raylib.h>

#include <raygui.h>

#include <Menu.hpp>



#include <fmt/core.h>



void Menu::GuiMenu(std::array<const char *, 5> &items,size_t n,NoteManger &nm){
     listView.bounds = Rectangle{0,30,40,60};
     listView.text = "Save \n Load \n Exit";
     listView.active = false;

    DrawRectangle(0, 0, GetScreenWidth(), 30, (Color){50,50,50,255});
    for (size_t i = 0; i < n; i ++){

        
        if (GuiButton(Rectangle{40.0f*i,0,40,30}, items[i])){
            MENU_ITEM menuItem = menuItems[items[i]];
            switch (menuItem) {
                case MENU_ITEM::SAVE : {
                                           auto path = exec("zenity --file-selection --save");
                                           if(path.size() == 0) return;
                                           fmt::println("Saving to: {}",path);
                                           nm.save(path);

                                           break;
                                       };
                case MENU_ITEM::LOAD : {
                                           auto path = exec("zenity --file-selection");
                                           if(path.size() == 0) return;
                                           fmt::println("Loading from: {}",path);
                                           nm.load(path);

                                           break;
                                       };
                case MENU_ITEM::ADD:{
                                        nm.addNote();
                                        break;
                                     }
                case MENU_ITEM::DEL:{
                                        nm.deleteNote();
                                        break;
                                     }
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
