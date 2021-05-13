#include <iostream>
#include <windows.h>
//#include <conio.h>
#include<string>

#include "ETable.cpp"

using namespace std;

void setBulgarianText() {
    SetConsoleCP(65001); // UTF-8
    SetConsoleOutputCP(65001);
}

int main()
{
    setBulgarianText();
    string fileName;
    string rowNum;
    do{
    cout<<"Create file: \n";
    cin>>fileName;
    if(fileName.find('.')!=string::npos) cout<<"you can't use '.' in filename! \n";
    if(doesFileExist(".\\Data/"+fileName+".txt")==1) cout<<"such file already exists! \n";
    }while(fileName.find('.')!=string::npos || doesFileExist(".\\Data/"+fileName+".txt")==1);
    ETable *eTable = new ETable(fileName+".txt");
    char operation = 'N';
    do {
        cout << "Choose what to do with the file:" << endl;
        cout << "To see the table type: P/p" << endl;
        cout << "To change sell value type: E/e" << endl;
        // Not required. Usefull for testing:
        cout << "To create test data type: C/c" << endl;
        cout << "To see type of data in the table type: R/r" << endl;
        //
        cout << "To Exit type: Q/q" << endl;
        cin >> operation; //operation = getch();
        switch(operation) {
        case 'P':
        case 'p':
            eTable->print();
            break;
        case 'E':
        case 'e':
            cout<<"choose row (ex: R1 or 1)";
            cin>>rowNum;
            cout<<typeid(rowNum).name();
            //if the addres is number convert it to int
            eTable->saveRow(rowNum);
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
