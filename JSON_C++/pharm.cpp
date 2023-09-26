#include <iostream>
#include <string>
#include "pharmacy_data.cpp"

using namespace std;

class Pharm
{
public:
    Pharm() = default;
    Pharm(PharmacyData pharmacyData) :
        pharmacyData(pharmacyData)
    {}
    Pharm(string name, bool warehause, ll_int v_phone_num, int w_num, string remark)
    {
        pharmacyData = PharmacyData(name, warehause, v_phone_num, w_num, remark);
    }
    Pharm(json js)
    {
        pharmacyData.getJsonHeader() = js;
    }

    void add(PharmacyData pharmacy_data)
    {
        pharmacyData.add(pharmacy_data);
    }

    json& get()
    {
        return pharmacyData.getJsonHeader();
    }

    void remove(int index) {
        pharmacyData.getJsonHeader()["List_pharmacy_base"].erase(index);
    }

private:

    PharmacyData pharmacyData;

};
