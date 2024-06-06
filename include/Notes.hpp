#pragma once

#include <memory>
#include <string>
#include <vector>
#include <raylib.h>

#undef  RAYGUI_IMPLEMENTATION

#ifndef RAYGUI_IMPLEMENTATION
#include <raygui.h>
#endif

class Note;

class NoteManger{

    private:
    std::vector<std::shared_ptr<Note>> notes;

    public: 
    NoteManger();
    void load(std::string path);
    void save(std::string path);
    void update();
    void draw();

};


class Note{
    public:
        Rectangle bounds;
        std::string text;

        Note(Vector2 postion,std::string text);
        void update();
        void draw();
};

