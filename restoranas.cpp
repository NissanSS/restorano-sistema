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

void printCheck(menuItemType menuList[], int pasirinkimai[], int porcijos[], int kiekPasirinkta) {
    ofstream fout("receipt.txt");

    double tarpineSuma = 0.0;
    double pvmProcentas = 0.21;

    cout << endl;
    cout << "Restorana cekis" << endl;
    fout << "Restorana cekis" << endl;

    cout << endl;
    fout << endl;

    for (int i = 0; i < kiekPasirinkta; i++) {
        int index = pasirinkimai[i];

        string pavadinimas = menuList[index].menuItem;
        double vienetoKaina = menuList[index].menuPrice;
        int porcijuKiekis = porcijos[i];

        double patiekaloSuma = vienetoKaina * porcijuKiekis;

        tarpineSuma = tarpineSuma + patiekaloSuma;

        cout << porcijuKiekis << " x " << pavadinimas << " "
             << fixed << setprecision(2) << patiekaloSuma << " EUR" << endl;

        fout << porcijuKiekis << " x " << pavadinimas << " "
             << fixed << setprecision(2) << patiekaloSuma << " EUR" << endl;
    }

    double pvmSuma = tarpineSuma * pvmProcentas;
    double galutineSuma = tarpineSuma + pvmSuma;

    cout << endl;
    cout << "Tarpine suma: " << fixed << setprecision(2) << tarpineSuma << " EUR" << endl;
    cout << "PVM (21%): " << fixed << setprecision(2) << pvmSuma << " EUR" << endl;
    cout << "Galutine suma: " << fixed << setprecision(2) << galutineSuma << " EUR" << endl;

    fout << endl;
    fout << "Tarpine suma: " << fixed << setprecision(2) << tarpineSuma << " EUR" << endl;
    fout << "PVM (21%): " << fixed << setprecision(2) << pvmSuma << " EUR" << endl;
    fout << "Galutine suma: " << fixed << setprecision(2) << galutineSuma << " EUR" << endl;

    fout.close();
}

int main() {
    menuItemType menuList[20];
    int kiekis = 0;

    getData(menuList, kiekis);

    if (kiekis == 0) {
        return 0;
    }

    showMenu(menuList, kiekis);

    int pasirinkimai[20];
    int porcijos[20];
    int kiekPasirinkta = 0;

    char testi = 't';

    while (testi == 't' || testi == 'T') {
        int ivestasNumeris;
        int ivestasKiekis;

        cout << endl;
        cout << "Iveskite patiekalo numeri: ";
        cin >> ivestasNumeris;

        if (ivestasNumeris < 1 || ivestasNumeris > kiekis) {
            cout << "Neteisingas numeris." << endl;
            continue;
        }

        cout << "Iveskite porciju kieki: ";
        cin >> ivestasKiekis;

        if (ivestasKiekis < 1) {
            cout << "Neteisingas kiekis." << endl;
            continue;
        }

        int tikrasIndex = ivestasNumeris - 1;

        pasirinkimai[kiekPasirinkta] = tikrasIndex;
        porcijos[kiekPasirinkta] = ivestasKiekis;

        kiekPasirinkta++;

        cout << "Ar norite testi? (t/n): ";
        cin >> testi;
    }

    printCheck(menuList, pasirinkimai, porcijos, kiekPasirinkta);

    cout << endl;
    cout << "Saskaita issaugota receipt.txt faile" << endl;

    return 0;
}