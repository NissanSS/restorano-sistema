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

    int pasirinkimai[20];
    int porcijos[20];
    int kiekpasirinkta = 0;

    char testi = 't';

    while (testi == 't' || testi == 'T') {
        int ivestasnumeris;
        int ivestaskiekis;

        cout << endl;
        cout << "Iveskite patiekalo numeri: ";
        cin >> ivestasnumeris;

        if (ivestasnumeris < 1 || ivestasnumeris > kiekis) {
            cout << "Neteisingas numeris." << endl;
            continue;
        }

        cout << "Iveskite porciju kieki: ";
        cin >> ivestaskiekis;

        if (ivestaskiekis < 1) {
            cout << "Neteisingas kiekis." << endl;
            continue;
        }

        int tikrasindex = ivestasnumeris - 1;

        pasirinkimai[kiekpasirinkta] = tikrasindex;
        porcijos[kiekpasirinkta] = ivestaskiekis;

        kiekpasirinkta++;

        cout << "Ar norite testi? (t/n): ";
        cin >> testi;
    }

    double tarpinesuma = 0.0;

    cout << endl;
    cout << "Jusu pasirinkti patiekalai:" << endl;

    for (int i = 0; i < kiekpasirinkta; i++) {
        int index = pasirinkimai[i];

        string pavadinimas = menulist[index].menuitem;
        double vienetokaina = menulist[index].menuprice;
        int porcijukiekis = porcijos[i];

        double patiekalosuma = vienetokaina * porcijukiekis;

        tarpinesuma = tarpinesuma + patiekalosuma;

        cout << porcijukiekis << " x " << pavadinimas << " - "
             << fixed << setprecision(2) << patiekalosuma << " EUR" << endl;
    }

    cout << endl;
    cout << "Tarpine suma: " << fixed << setprecision(2) << tarpinesuma << " EUR" << endl;
    cout << "PVM ir saskaitos failas bus prideti veliau." << endl;

    return 0;
}
