
#include "Editor.hpp"
#include <fmt/core.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/ostreamwrapper.h>

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include <Notes.hpp>

/*
 save format::
{
    "notes": [
        {
            "text": "Hello world",
            "coords": {
                "x": 398,
                "y": 171
            }
        },
        ...
    ]
}
*/

NoteManger::NoteManger(){
    WorldOffset = Vector2Zero();
 notes.push_back(std::make_shared<Note>(Vector2{100,200},"Hello world"));
}
void NoteManger::load(std::string jpath){
    
    std::fstream file;
    size_t x;
    while((  x = jpath.find('\n'))  != jpath.npos) {
        jpath.erase(x);
    }
    
    
    

    file.open(jpath,std::ios_base::in);

    if (!std::filesystem::exists(jpath)){
        system("zenity --error --text=\"Could not find file!\" ");
        return; 
    }

    rapidjson::Document doc;
    // Loading json
    std::string json;
    file.seekg(0,std::ios_base::end);
    size_t fileSize = file.tellg();
    file.seekg(0,std::ios_base::beg);
    json.resize(fileSize);
    file.read(&json[0], fileSize);
    doc.Parse(&json[0],fileSize);
    if (doc.HasParseError()){
        system("zenity --error --text=\"A parse error has occured\" ");
        return; 
    }

    notes.clear();
    std::cout << "Number of notes: " << doc["notes"].Size() << std::endl;
    for ( int i = 0; i < doc["notes"].Size();i++){
        std::string text =doc["notes"][i]["text"].GetString(); 
        int x = doc["notes"][i]["coords"]["x"].GetInt() ;  
        int y = doc["notes"][i]["coords"]["y"].GetInt() ;  

        notes.push_back(std::make_shared<Note>((Vector2){(float)x,(float)y},text));
    }
    


}

void NoteManger::save(std::string path){

    rapidjson::Document docs;

    size_t x;
    while((  x = path.find('\n'))  != path.npos) {
        path.erase(x);
    }

    docs.Parse("{}");

    rapidjson::Value arr(rapidjson::kArrayType); 
    for (auto i : notes){
        rapidjson::Value obj(rapidjson::kObjectType);
        rapidjson::Value coords(rapidjson::kObjectType);
        rapidjson::Value text(rapidjson::kStringType);
        rapidjson::Value x(rapidjson::kNumberType);
        rapidjson::Value y(rapidjson::kNumberType);

        text.SetString(&i->text[0],i->text.size());
        x.SetInt(i->bounds.x);
        y.SetInt(i->bounds.y);
        obj.AddMember("text",text,docs.GetAllocator());

        coords.AddMember("x",x,docs.GetAllocator());
        coords.AddMember("y",y,docs.GetAllocator());
        obj.AddMember("coords", coords,docs.GetAllocator());

        arr.PushBack(obj,docs.GetAllocator());

    }
    docs.AddMember("notes",arr,docs.GetAllocator());



    /* rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    docs.Accept(writer);
    auto save= sb.GetString();
*/
    std::fstream saveFile(path,std::ios_base::out);
    /* std::cout << "data: "<< sb.GetString()<< std::endl;
    std::cout << "Size: "<< sb.GetSize()<< std::endl;
    saveFile.write(sb.GetString(), 100); */

    rapidjson::OStreamWrapper osw(saveFile);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    docs.Accept(writer);



}
void NoteManger::addNote(){
    notes.push_back(std::make_shared<Note>( Vector2{10,10}, "Nil"));
}
void NoteManger::deleteNote(){
    if (!editing)
        return;
    for (auto it = notes.begin(); it != notes.end(); it++){
        if (*it == editing)
        {

            it = notes.erase(it);
            return;
        }
    }

}

void NoteManger::calculateOffset(){

    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)){

        WorldOffset = Vector2Add(WorldOffset, GetMouseDelta());
    }
}
void NoteManger::handleSelection(std::shared_ptr<Note> note){
    if (selected != nullptr){
        auto mappedPotsition =  Vector2Subtract(GetMousePosition(), selectedOffset );
        selected->setPosition(mappedPotsition);
        if(!selected ->isLeftClicked()){
            selected = nullptr;
        }
    }
    else if (selected == nullptr && note->isLeftClicked()) {
        selected = note;
        selectedOffset = Vector2Subtract( GetMousePosition(),{selected->bounds.x,selected->bounds.y});
    }

}
void NoteManger::update(){
    calculateOffset();


    for(auto i : notes){
        i->update();
        i->setOffset(WorldOffset);
        handleSelection(i);
        handleEditing(i);
    }

}

void NoteManger::handleEditing(std::shared_ptr<Note> note){
        if(editing == nullptr && note -> isRightClicked()){
            editing = note;
            editor = std::make_unique<Editor>(editing);
    
        }else if( note -> isRightClicked()){
            editor = nullptr;
            editing = note;
            editor = std::make_unique<Editor>(editing);
        }
        if(editor){
            renderEditor(editing);
        }

}
void NoteManger::renderEditor(std::shared_ptr<Note> note){

        editor->update();
        editor->draw();
        if (editor->shouldClose()){
            editor = nullptr;
        }
    

}

void NoteManger::draw(){
    for(auto i : notes){
        i->draw();
    }
}

Note::Note(Vector2 position,std::string text){
    bounds.x = position.x;
    bounds.y = position.y;
    bounds.width = 200;
    bounds.height = 170;

    this->text = text;
}

bool Note::isLeftClicked(){return leftClicked;}
bool Note::isRightClicked(){return rightClicked;}
bool Note::isHovered(){return hovered;}

void Note::update(){

    bool withinXBounds =GetMouseX()  - (offset.x + bounds.x) > 0 && GetMouseX() - (offset.x +bounds.x) < bounds.width ;
    bool withinYBounds =GetMouseY()  - (offset.y +bounds.y) > 0 && GetMouseY() - (offset.y +bounds.y) < bounds.height;
    if (withinXBounds && withinYBounds){
        hovered = true;
    }
    else hovered = false;


    if (isHovered() && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        leftClicked = true;
    }
    else{
        leftClicked = false;
    }
    if (isHovered() && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        rightClicked = true;
    }
    else{
        rightClicked = false;
    }
}
void Note::draw(){
    DrawRectangle(offset.x + bounds.x-1,offset.y + bounds.y-1, bounds.width+2, bounds.height+2, isLeftClicked()? BLUE: BLACK);

    DrawRectangle(offset.x + bounds.x,offset.y + bounds.y, bounds.width, bounds.height,WHITE);

    auto difference = Vector2Subtract( GetMousePosition(),{offset.x + bounds.x, offset.y + bounds.y});
    auto mappedPotsition =  Vector2Subtract(GetMousePosition(), difference );
    /* DrawCircleV(difference, 10, RED);
    DrawCircleV(mappedPotsition, 5, PURPLE);
    auto x = TEXT_ALIGN_CENTER; */

    GuiSetStyle(LABEL,TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    auto wrap =  GuiGetStyle(DEFAULT, TEXT_WRAP_MODE);
    auto valign =  GuiGetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL);
    GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);
    GuiLabel({offset.x + bounds.x,offset.y + bounds.y,bounds.width,bounds.height}, &text[0]);
    //GuiDrawText(&text[0], {offset.x + bounds.x,offset.y + bounds.y,bounds.width,bounds.height}, TEXT_ALIGN_CENTER, BLACK);

    GuiSetStyle(DEFAULT, TEXT_WRAP_MODE,  wrap);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL,  valign);


}

void Note::setPosition(Vector2 position){
    this->bounds.x = position.x;
    this->bounds.y = position.y;
}
void Note::setOffset(Vector2 offset){
    this->offset = offset;
}
