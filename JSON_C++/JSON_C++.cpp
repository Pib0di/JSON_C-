// JSON_C++.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 7 лаба
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include <vector>
#include <string>
#include "pharm.cpp"
#include "pharmacy_data.cpp"

using namespace std;


void outputTable(json data)
{
    int count = data["List_pharmacy_base"].size();
    string name;
    int dataLength = data.size();

    cout << "Общие данные" << endl;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        if (dataLength == 1)
        {
            cout << it.key() << ": \n" << endl;
        }
        else
        {
            cout << it.key() << ": " << it.value() << endl;
        }
        --dataLength;
    }
    dataLength = 0;
    cout << '\t' << setw(10) << " ";
    name = data["List_pharmacy_base"][0].begin().key();
    for (auto it = data["List_pharmacy_base"][0][name].begin(); it != data["List_pharmacy_base"][0][name].end(); ++it)
    {
        cout << setw(10) << " " << it.key();
    }
    cout << endl;
    for (int i = 0; i < count; ++i)
    {
        name = data["List_pharmacy_base"][i].begin().key();
        cout << name;
        for (auto const& val : data["List_pharmacy_base"][i][name])
        {
            cout << '\t' << setw(10) << " " << val;
        }
        cout << endl;
        
    }
}

void eventLoop(json data)
{
    string cmd;
    int num;

    Pharm pharm(data);

    int choice = 0;
    while (choice != 4) {
        cout << "Выберите действие:\n";
        cout << "1. Показать аптеки\n";
        cout << "2. Удалить аптеку\n";
        cout << "3. Добавить аптеку\n";
        cout << "4. Выход\n";
        cin >> choice;

        switch (choice) {
        case 1:
            outputTable(pharm.get());
            break;
        case 2:
            int index;
            cout << "Введите номер аптеки для удаления: ";
            cin >> index;
            pharm.remove(index);
            break;
        case 3: {
            string name, remark;
            bool war;
            ll_int numb;
            int num_w;
            cout << "Введите данные для новой аптеки:\n";
            cout << "Имя аптеки (строка): ";
            cin >> name;
            cout << "Наличие склада (1 - да, 0 - нет): ";
            cin >> war;
            cout << "Номер телефона: ";
            cin >> numb;
            cout << "Номер базы: ";
            cin >> num_w;
            cout << "Отзыв (строка): ";
            cin >> remark;
            pharm.add(PharmacyData(name, war, numb, num_w, remark));
            cin.clear();
            cin.ignore();
            break;
        }
        case 4:
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, выберите снова.\n";
            break;
        }

        std::ofstream o("pharm.json");
        o << setw(4) << pharm.get() << std::endl;
    }
}

int main()
{
    setlocale(LC_ALL, "ru");
    Pharm pharm;
    
    vector<string> v_name = {"No to diseases", "Heal    ", "P. pharm"};
    vector<bool> v_warehause = {true, false, false};
    vector<ll_int> v_phone = { 89626766044, 947586926409, 924375627354 };
    vector<int> v_w_num = {393, 254, 458};
    vector<string> v_remark = {"Sale!", "discount", "destroyed!"};

    for (int i = 0; i < v_name.size(); ++i)
    {
        PharmacyData pharmacyData(v_name[i], v_warehause[i], v_phone[i], v_w_num[i], v_remark[i]);
        pharm.add(pharmacyData);
    }

    //Serialization
    std::ofstream o ("pharm.json");
    o << setw(4) << pharm.get() << std::endl;

    //Deserialization
    std::ifstream i("pharm.json");
    json j_input;
    i >> j_input;

    //Вывод в виде таблицы
    json data = j_input;
    outputTable(data);

    //удаление добавление
    eventLoop(data);
}
