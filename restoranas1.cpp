#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct menuItemType {
    string menuItem;
    double menuPrice;
};

void getData(menuItemType menuList[], int &kiekis) {
    ifstream fin("menu.txt");

    kiekis = 0;

    if (!fin) {
        cout << "Nepavyko atidaryti failo." << endl;
        return;
    }

    while (getline(fin, menuList[kiekis].menuItem, ';') && fin >> menuList[kiekis].menuPrice) {
        fin.ignore();
        kiekis++;
    }

    fin.close();
}

void showMenu(menuItemType menuList[], int kiekis) {
    cout << endl;
    cout << "PUSRYCIU MENIU" << endl;

    for (int i = 0; i < kiekis; i++) {
        int numeris = i + 1;
        string pavadinimas = menuList[i].menuItem;
        double kaina = menuList[i].menuPrice;

        cout << numeris << ". " << pavadinimas << " - "
             << fixed << setprecision(2) << kaina << " EUR" << endl;
    }
}

int main() {
    menuItemType menuList[20];
    int kiekis = 0;

    getData(menuList, kiekis);

    if (kiekis == 0) {
        return 0;
    }

    showMenu(menuList, kiekis);

    cout << endl;
    cout << "Kita programos dalis bus prideta veliau." << endl;

    return 0;
}