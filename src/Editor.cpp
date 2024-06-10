#include <Editor.hpp>

#include <memory>
#include <raylib.h>
#include <raygui.h>

#include <Notes.hpp>


Editor::Editor(std::shared_ptr<Note> note){
    this->currentNote = note;

        text = note->text;
        text.resize(250);

        editBthClicked =false;
        close = false;
}

void Editor::updateText(std::string text){
    if (currentNote)
    {
        this->currentNote->text = text;
    }
}


void Editor::update(){

    if(editBthClicked){
        updateText(text);
        close = true;
    }

}
bool Editor::shouldClose(){return close;}
void Editor::draw(){
    GuiTextBox({0,(float)GetScreenHeight()-40,(float)GetScreenWidth()- 65,35},&text[0] ,150, true);
    editBthClicked = GuiButton({(float) GetScreenWidth() - 60 ,(float)GetScreenHeight()-40,(float)60,35}, "Enter");
    
}

