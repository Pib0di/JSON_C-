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
    string name;
    bool warehause = false; // наличие склада
    ll_int v_phone_num; // номенр тел.
    int w_num = 0; // номер базы
    string remark = ""; // отзыв
    //j4["List_pharmacy_base"] += { {"currency", { {"USD", "sdf"}, { "value", 42.99 } }} } /*{j_list_of_pairs, 3, 4, 3, 4}*/;
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

int main()
{
    Pharm pharm_0;
    //pharm_0.show();
    
    vector<string> v_name = {"No to diseases", "Heal", "P. pharm"};
    vector<bool> v_warehause = {true, false, false};
    vector<ll_int> v_phone = { 89626766044, 947586926409, 924375627354 };
    vector<int> v_w_num = {393, 254, 458};
    vector<string> v_remark = {"Sale!", "discount", "destroyed!"};

    for (int i = 0; i < v_name.size(); ++i)
    {
        bool warehause = v_warehause[i];
        pharm_0.add(v_name[i], warehause, v_phone[i], v_w_num[i], v_remark[i]);
    }

    pharm_0.show(4);

    std::ofstream o ( " pharm.json " );
    o << setw(4) << pharm_0.get() << std::endl;
}
