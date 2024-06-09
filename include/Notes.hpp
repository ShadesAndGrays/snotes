#pragma once

#include <memory>
#include <string>
#include <vector>
#include <raylib.h>


class Note;

class NoteManger{

    private:
    std::vector<std::shared_ptr<Note>> notes;
    std::shared_ptr<Note> selected;
    Vector2 selectedOffset;
    Vector2 WorldOffset;

    public: 
    NoteManger();
    void load(std::string path);
    void save(std::string path);
    void update();
    void draw();

};


class Note{
    private:
        bool leftClicked;
        bool hovered;
        Vector2 offset;
    public:
        Rectangle bounds;
        std::string text;

        Note(Vector2 position,std::string text);
        void setPosition(Vector2 position);
        bool isHovered();
        bool isLeftClicked();
        void update();
        void draw();
        void setOffset(Vector2 offset);
};

