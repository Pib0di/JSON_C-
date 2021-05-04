// JSON_C++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 7 лаба

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
    Pharm(string n, bool w, ll_int phone, int num, string r) :
        name(n), warehause(w), v_phone_num(phone), w_num(num), remark(r)
    {
        j["List_pharmacy_base"] += {name, { {"Warehause", warehause}, {"Phone number", v_phone_num}, {"Warehause number", w_num}, {"Remark", remark} }};
    }
    Pharm(vector<string>& name, vector<bool>& w, vector<ll_int>& phone, vector<int>& num, vector<string>& r)
    {
        for (int i = 0; i < name.size(); ++i)
        {
            bool b_w = w[i];
            j["List_pharmacy_base"] += {
                name[i],
                {
                    {"Warehause", b_w},
                    {"Phone number", phone[i]},
                    {"Warehause number", num[i]},
                    {"Remark", r[i]}
                }
            };
        }
    }
    Pharm(json js)
    {
        j = js;
    }

    void show(int i)
    {
        cout << j.dump(i);
    }

    void add(string name, bool war, ll_int phone, int w_num, string remark)
    {
        j["List_pharmacy_base"] += { {name, { {"Warehause", war}, {"Phone number", phone}, {"Warehause number", w_num}, {"Remark", remark} }}};
    }

    json& get()
    {
        return j;
    }
private:
    string name; // имя аптеки
    bool warehause = false; // наличие склада
    ll_int v_phone_num; // номенр тел.
    int w_num = 0; // номер базы
    string remark = ""; // отзыв
    json j = R"(
    {
        "File": "Pharmacy bases",
        "Cyty": "Russia",
        "Date": "20/04/2021",
        "List_pharmacy_base": 
        [
            
        ]
    }
    )"_json;
};

void input_table(json data)
{
    int count = data["List_pharmacy_base"].size();
    string name;
    int i = data.size();

    cout << "Общие данные" << endl;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (i == 1)
        {
            cout << it.key() << ": \n" << endl;
        }
        else
        {
            cout << it.key() << ": " << it.value() << endl;
        }
        --i;
    }
    i = 0;
    cout << '\t' << setw(10) << " ";
    name = data["List_pharmacy_base"][0].begin().key();
    for (auto it = data["List_pharmacy_base"][0][name].begin(); it != data["List_pharmacy_base"][0][name].end(); ++it)
    {
        cout << setw(10) << " " << it.key();
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        //if (data["List_pharmacy_base"][i][name] != 0)
        //{
            name = data["List_pharmacy_base"][i].begin().key();
            cout << name;
            for (auto const& val : data["List_pharmacy_base"][i][name])
            {
                cout << '\t' << setw(10) << " " << val;
            }
            cout << endl;
        //}
    }
}

void func(json data)
{
    string cmd;
    int num;

    Pharm pharm(data);
    while (cmd != "exit")
    {
        cout << "\nУдаление \"del\" + \"номер строки\". \nДобавление \"add\" + ввод соответствующих данных. \nВыход - \"exit\". \nПоказать табл \"show\"\n" << endl;
        cin >> cmd;
        if (cmd == "del")
        {
            cout << "Введите номер строки: " << endl;
            cin >> num;
            pharm.get()["List_pharmacy_base"].erase(num);
        }
        else if (cmd == "add")
        {

            string name, remark;
            bool war;
            ll_int numb;
            int num_w;
            cout << "Последовательно введите Имя аптеки(string), наличие склада(bool), номер телефона(int), номер базы(int), отзыв(str)" << endl;
            cin >> name >> war >> numb >> num_w >> remark;
            pharm.add(name, war, numb, num_w, remark);
            cin.clear();
            cin.ignore();
        }
        else if (cmd == "exit")
        {
            break;
        }
        else if (cmd == "show")
        {
            input_table(pharm.get());
        }
        std::ofstream o("pharm.json");
        o << setw(4) << pharm.get() << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    Pharm pharm_0;
    
    vector<string> v_name = {"No to diseases", "Heal    ", "P. pharm"};
    vector<bool> v_warehause = {true, false, false};
    vector<ll_int> v_phone = { 89626766044, 947586926409, 924375627354 };
    vector<int> v_w_num = {393, 254, 458};
    vector<string> v_remark = {"Sale!", "discount", "destroyed!"};

    for (int i = 0; i < v_name.size(); ++i)
    {
        pharm_0.add(v_name[i], v_warehause[i], v_phone[i], v_w_num[i], v_remark[i]);
    }

    //Serialization
    std::ofstream o ("pharm.json");
    o << setw(4) << pharm_0.get() << std::endl;

    //Deserialization
    std::ifstream i("pharm.json");
    json j_input;
    i >> j_input;
    //cout << j_input.dump(4);

    //Вывод в виде таблицы
    json data = j_input;
    input_table(data);

    //удаление добавление
    func(data);
}
