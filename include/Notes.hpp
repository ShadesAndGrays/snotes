#pragma once

#include <memory>
#include <string>
#include <vector>
#include <raylib.h>
#include <Editor.hpp>


class Note;

class NoteManger{

    private:
    std::vector<std::shared_ptr<Note>> notes;
    std::shared_ptr<Note> selected;
    std::shared_ptr<Note> editing;
    std::unique_ptr<Editor> editor;
    Vector2 selectedOffset;
    Vector2 WorldOffset;

    void calculateOffset();
    void handleSelection(std::shared_ptr<Note> note);
    void handleEditing(std::shared_ptr<Note> note);
    void renderEditor(std::shared_ptr<Note> note);

    void bringForward();

    public: 
    NoteManger();
    void addNote();
    void deleteNote();
    void load(std::string path);
    void save(std::string path);
    void update();
    void draw();

};


class Note{
    private:
        bool leftClicked;
        bool rightClicked;
        bool hovered;
        Vector2 offset;
    public:
        Rectangle bounds;
        std::string text;

        Note(Vector2 position,std::string text);
        ~Note();
        void setPosition(Vector2 position);
        bool isHovered();
        bool isLeftClicked();
        bool isRightClicked();
        void update();
        void draw();
        void setOffset(Vector2 offset);
        
};

