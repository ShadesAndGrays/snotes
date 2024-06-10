#pragma once
#include <memory>
#include <string>

class Note;
class Editor{
    private:
        std::shared_ptr<Note> currentNote;
        std::string text;
        bool editBthClicked;
        bool close;

    public:
        Editor(std::shared_ptr<Note> note);

        void updateText(std::string text);
        void draw();
        void update();
        bool shouldClose();




};
