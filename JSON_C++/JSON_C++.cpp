// JSON_C++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

int main()
{
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;



    // or even nicer with a raw string literal
    auto j2 = R"(
 {
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
}
)"_json;

    // parse explicitly
    auto j3 = json::parse("{ \"happy\": true, \"pi\": 3.141 }");


    // explicit conversion to string
    std::string s = j.dump();    // {\"happy\":true,\"pi\":3.141}

    // serialization with pretty printing
    // pass in the amount of spaces to indent
    //cout << s;
    std::cout << j.dump(4) << std::endl;
    // {
    //     "happy": true,
    //     "pi": 3.141
    // }

    std::ofstream o ( " pretty.json " );
    o << setw(4) << j2 << std::endl;
}
