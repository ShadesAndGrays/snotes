#include <cstdio>
#include <cstring>
#include <fmt/core.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/stringbuffer.h>
#include <string>

void test2(){
    rapidjson::Document docs;

    docs.Parse("{}");

    std::string names[10] = {
        "Hero",
        "Samason",
        "Teeny",
        "Hamada",
        "Ariel",
        "Chang Sha",
        "Shamson",
        "Cavel",
        "Cream",
        "Shadow"
    };

    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

    rapidjson::Value arr(rapidjson::kArrayType); 

    for (int i = 0; i < 10; i++){

        rapidjson::Value obj(rapidjson::kObjectType); 
        rapidjson::Value uname(rapidjson::kStringType);
        rapidjson::Value age(rapidjson::kNumberType);
        char x[10] = "Number";
        
        uname.SetString( &names[i][0] ,names[i].size());
        age.SetInt(i);
        obj.AddMember("Name",uname,docs.GetAllocator());
        obj.AddMember("Age",age,docs.GetAllocator());

        arr.PushBack(obj,docs.GetAllocator());
     writer.Reset(sb);
        sb.Clear();
        arr.Accept(writer);
        puts(sb.GetString());
    }

    docs.AddMember("Notes",arr,docs.GetAllocator());


     writer.Reset(sb);
    sb.Clear();
    docs.Accept(writer);
    puts(sb.GetString());

}
void test(){
    rapidjson::Document docs;

    std::fstream file = std::fstream("test.json",std::ios_base::in);
    if (!file.is_open()){
        fmt::println("{}","Error: File is not open");
    }


    std::string jsonStr;
    file.seekg(0,std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0,std::ios::beg);
    jsonStr.resize(fileSize);
    file.read(&jsonStr[0],fileSize);
    file.close();


    if (docs.Parse(&jsonStr[0]).HasParseError()) {
        fmt::println("Error: Failed to parse Json {}",(int) docs.GetParseError());
        return;
    }

    fmt::println("Docs is object: {}",docs.IsObject());


    rapidjson::Document::AllocatorType& allocator = docs.GetAllocator();

    rapidjson::StringBuffer sb ;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    docs["Greetings"].Accept(writer);    // Accept() traverses the DOM and generates Handler events.


    rapidjson::Value cmplxGreeting(rapidjson::kStringType);

    if (!docs["Greetings"].HasMember("complex"))
        docs["Greetings"].AddMember("complex",cmplxGreeting,allocator);

    docs["Greetings"]["complex"].SetString("Hello how are you doing");

    sb.Clear();
    writer.Reset(sb);
    docs.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
                            //
    file.open("test.json",std::ios_base::out);

    file.write(sb.GetString(),sb.GetSize());
    fmt::println("JSON: {}",sb.GetString());
}


