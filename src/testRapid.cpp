#include <cstdio>
#include <fmt/core.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/rapidjson.h>

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


