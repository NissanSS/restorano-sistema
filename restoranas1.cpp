#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct menuitemtype {
    string menuitem;
    double menuprice;
};

void getdata(menuitemtype menulist[], int &kiekis) {
    ifstream fin("menu.txt");

    kiekis = 0;

    if (!fin) {
        cout << "Nepavyko atidaryti failo." << endl;
        return;
    }

    while (kiekis < 20 && getline(fin, menulist[kiekis].menuitem, ';') && fin >> menulist[kiekis].menuprice) {
        fin.ignore();
        kiekis++;
    }

    fin.close();
}

void showmenu(menuitemtype menulist[], int kiekis) {
    cout << endl;
    cout << "PUSRYCIU MENIU" << endl;

    for (int i = 0; i < kiekis; i++) {
        int numeris = i + 1;
        string pavadinimas = menulist[i].menuitem;
        double kaina = menulist[i].menuprice;

        cout << numeris << ". " << pavadinimas << " - "
             << fixed << setprecision(2) << kaina << " EUR" << endl;
    }
}

int main() {
    menuitemtype menulist[20];
    int kiekis = 0;

    getdata(menulist, kiekis);

    if (kiekis == 0) {
        return 0;
    }

    showmenu(menulist, kiekis);

    cout << endl;
    cout << "Kita programos dalis bus prideta veliau." << endl;

    return 0;
}
