// JSON_C++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include <vector>
#include <string>

using json = nlohmann::json;
using namespace std;
typedef long long int ll_int;

class Pharm
{
public:
    Pharm() = default;
    Pharm(string name, bool w, vector<ll_int> phone, int w_num, string remark) :
        name(name), warehause(w), v_phone_num(phone), w_num(w_num), remark(remark)
    {}

private:
    string name;
    bool warehause = false; // наличие склада
    vector<ll_int> v_phone_num; // номенр тел.
    int w_num = 0; // номер базы
    string remark = ""; // отзыв
};

int main()
{
    Pharm pharm();
    json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    vector<string> v_name = {"Скажем нет болезням", "Мое здоровье", "А. аптека"};
    vector<bool> v_warehause = {true, false, false};
    vector<vector<ll_int>> v_phone = { {89626766044, 89098367854, 94238764977}, {947586926409, 845357209521}, {924375627354} };
    vector<int> v_w_num = {393, 254, 458};
    vector<string> v_remark = {"Отличная аптека, низкие цены", "Не советую", "Закрыта!"};

    for (int i = 0; i < v_name.size(); ++i)
    {
        
    }


    



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
