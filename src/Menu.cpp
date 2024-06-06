#include <Menu.hpp>

void Menu::initMenu(std::array<const char *, 3> &items,size_t n,NoteManger &nm){
     listView.bounds = Rectangle{0,30,40,60};
     listView.text = "Save \n Load";
     listView.active = false;

    for (size_t i = 0; i < n; i ++){

        if (GuiButton(Rectangle{40.0f*i,0,40,30}, items[i])){
            MENU_ITEM menuItem = menuItems[items[i]];
            switch (menuItem) {
                case MENU_ITEM::SAVE : {
                                           fmt::println("stuff  /{}/",exec("zenity --file-selection"));

                                           break;
                                       };
                case MENU_ITEM::LOAD : {

                                           break;
                                       };
                case MENU_ITEM::EXIT:{
                                         break;
                                     };
                default:{
                            break;
                        };
            }

        }
    }

}
