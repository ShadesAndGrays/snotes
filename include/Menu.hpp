#pragma once

#include <array>
#include <cstdlib>
#include <fmt/core.h>
#include <unordered_map>
#include <string>
#include <Notes.hpp>

std::string exec(const char* cmd);

namespace Menu{

inline struct ListView{
    Rectangle bounds;
    const char* text;
    int active;

}listView;

struct MenuBarState{
    bool FileDialogOpen;

};
enum class MENU_ITEM{
    NONE = 0,
    SAVE,
    LOAD,
    EXIT

};
inline std::array<const char *, 3> menu_bar_items={
    "Save",
    "Load",
    "Exit"
};

inline std::unordered_map<std::string, MENU_ITEM> menuItems{
    {menu_bar_items[0],MENU_ITEM::SAVE},
    {menu_bar_items[1],MENU_ITEM::LOAD},
    {menu_bar_items[2],MENU_ITEM::EXIT},
};


void initMenu(std::array<const char *, 3> &items,size_t n,NoteManger &nm);
void handleFile();

};
