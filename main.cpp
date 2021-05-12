#include <iostream>
#include <windows.h>
//#include <conio.h>

#include "ETable.cpp"

using namespace std;

void setBulgarianText() {
    SetConsoleCP(65001); // UTF-8
    SetConsoleOutputCP(65001);
}

int main()
{
    setBulgarianText();

    ETable *eTable = new ETable("test.txt");
    char operation = 'N';
    do {
        cout << "Въведете операция." << endl;
        cout << "Извеждане съдържанието на таблицата на екрана print P/p" << endl;
        cout << "Редактира съдържанието на дадена клетка edit E/e" << endl;
        // Not required. Usefull for testing:
        cout << "Създава тестови файл с данни C/c" << endl;
        cout << "Разпознава типовете данни от файл R/r" << endl;
        //
        cout << "Изход Q/q" << endl;
        cin >> operation; //operation = getch();
        switch(operation) {
        case 'P':
        case 'p':
            eTable->print();
            break;
        case 'E':
        case 'e':
            eTable->saveRow("R1");
            break;
        case 'C':
        case 'c':
            eTable->createTestData();
            break;
        case 'R':
        case 'r':
            eTable->recognizeTestData();
            break;
        default:
            cout<<"Error 404!Command not found!";
        }
    } while (operation != 'Q' && operation != 'q');
    delete eTable;

    return 0;
}
