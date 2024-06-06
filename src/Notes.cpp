
#include <Notes.hpp>
#include <memory>
#ifndef RAYGUI_IMPLEMENTATION 
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#endif


NoteManger::NoteManger(){
 notes.push_back(std::make_shared<Note>(Vector2{100,0},"Hello world"));
}
void NoteManger::load(std::string path){

}
void NoteManger::save(std::string path){

}
void NoteManger::draw(){
    for(auto i : notes){
        i->draw();
    }
}

Note::Note(Vector2 position,std::string text){
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 100;
    bounds.height = 150;

    this->text = text;
}
void Note::draw(){
    DrawRectangle(bounds.x-1, bounds.y-1, bounds.width+2, bounds.height+2,BLACK);

    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height,WHITE);

#ifdef RAYGUI_IMPLEMENTATION
    // GuiGetStyle(, int property);
    // GuiSetStyle(DEFAULT, TEXT_PADDING, 0);
    GuiDrawText(&text[0], bounds, TEXT_ALIGN_CENTER, BLACK);
#endif

}
