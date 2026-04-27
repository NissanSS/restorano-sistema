#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// struktura saugo patiekalo pavadinima ir kaina
struct menuitemtype {
    string menuitem;
    double menuprice;
};

// nuskaito meniu duomenis is failo
void getdata(menuitemtype menulist[], int &kiekis) {
    ifstream fin("menu.txt");

    kiekis = 0;

    if (!fin) {
        cout << "Nepavyko atidaryti failo." << endl;
        return;
    }

    while (getline(fin, menulist[kiekis].menuitem, ';') && fin >> menulist[kiekis].menuprice) {
        fin.ignore();
        kiekis++;
    }

    fin.close();
}

// parodo meniu
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

// skaiciuoja saskaita ir isveda i faila
void printcheck(menuitemtype menulist[], int pasirinkimai[], int porcijos[], int kiekpasirinkta) {
    ofstream fout("receipt.txt");

    double tarpinesuma = 0.0;
    double pvmprocentas = 0.21;

    cout << endl;
    cout << "Sveiki atvyke i restorana" << endl;
    fout << "Sveiki atvyke i restorana" << endl;

    cout << endl;
    fout << endl;

    for (int i = 0; i < kiekpasirinkta; i++) {
        int index = pasirinkimai[i];

        string pavadinimas = menulist[index].menuitem;
        double vienetokaina = menulist[index].menuprice;
        int porcijukiekis = porcijos[i];

        double patiekalosuma = vienetokaina * porcijukiekis;

        tarpinesuma = tarpinesuma + patiekalosuma;

        cout << porcijukiekis << " x " << pavadinimas << " "
             << fixed << setprecision(2) << patiekalosuma << " EUR" << endl;

        fout << porcijukiekis << " x " << pavadinimas << " "
             << fixed << setprecision(2) << patiekalosuma << " EUR" << endl;
    }

    double pvmsuma = tarpinesuma * pvmprocentas;
    double galutinesuma = tarpinesuma + pvmsuma;

    cout << endl;
    cout << "Tarpine suma: " << fixed << setprecision(2) << tarpinesuma << " EUR" << endl;
    cout << "PVM (21%): " << fixed << setprecision(2) << pvmsuma << " EUR" << endl;
    cout << "Galutine suma: " << fixed << setprecision(2) << galutinesuma << " EUR" << endl;

    fout << endl;
    fout << "Tarpine suma: " << fixed << setprecision(2) << tarpinesuma << " EUR" << endl;
    fout << "PVM (21%): " << fixed << setprecision(2) << pvmsuma << " EUR" << endl;
    fout << "Galutine suma: " << fixed << setprecision(2) << galutinesuma << " EUR" << endl;

    fout.close();
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

    printcheck(menulist, pasirinkimai, porcijos, kiekpasirinkta);

    cout << endl;
    cout << "Saskaita issaugota receipt.txt faile" << endl;

    return 0;
}
