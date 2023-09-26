#include <string>
#include "json-develop/single_include/nlohmann/json.hpp"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;
typedef long long int ll_int;

class PharmacyData {
public:
    PharmacyData() = default;
    PharmacyData(const string& n, bool w, ll_int phone, int num, const string& r) :
        name(n), warehause(w), v_phone_num(phone), w_num(num), remark(r) {
        jsonHeader["List_pharmacy_base"] += {
            name,
            {
                {"Warehause", warehause},
                {"Phone number", v_phone_num},
                {"Warehause number", w_num},
                {"Remark", remark} }
        };
    }

    json toJson() const {
        return {
            {"Warehause", warehause},
            {"Phone number", v_phone_num},
            {"Warehause number", w_num},
            {"Remark", remark}
        };
    }

    json& getJsonHeader() {
        return jsonHeader;
    }

    void add(PharmacyData pharmacyData) {
        jsonHeader["List_pharmacy_base"] += { 
            {pharmacyData.name, 
                { 
                    {"Warehause", pharmacyData.warehause}, 
                    {"Phone number", pharmacyData.warehause}, 
                    {"Warehause number", pharmacyData.warehause}, 
                    {"Remark", pharmacyData.warehause} 
                }
            }};
    }

private:
    string name; // имя аптеки
    bool warehause = false; // наличие склада
    ll_int v_phone_num; // номер телефона
    int w_num = 0; // номер базы
    string remark = ""; // отзыв

    json jsonHeader = R"(
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