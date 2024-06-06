#include <array>
#include <unordered_map>
#include <string>
#include <raylib.h>
#include <raygui.h>


namespace Menu{
enum class MENU_ITEM{
    NONE = 0,
    FILE,
    EXIT

};
inline std::array<const char *, 3> menu_bar_items={
    "File",
    "Exit"
};

inline std::unordered_map<std::string, MENU_ITEM> menuItems{
    {menu_bar_items[0],MENU_ITEM::FILE},
    {menu_bar_items[1],MENU_ITEM::EXIT},
};


inline void initMenu(std::array<const char *, 3> &items,size_t n){

    for (size_t i = 0; i < n; i ++){
        if (GuiButton(Rectangle{40.0f*i,0,40,30}, items[i])){
            MENU_ITEM menuItem = menuItems[items[i]];
            switch (menuItem) {
                case MENU_ITEM::FILE : {

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

};
