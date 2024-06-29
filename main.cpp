#include <QCoreApplication>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <QtGlobal>
#include <clocale>
#include <QtAlgorithms>
#include <QMap>
#include <QDebug>
#include <QString>
#include <Windows.h>
using namespace std;
using namespace Qt;

typedef QPair<QString, QString> NameSurnamePair;
typedef QMap<int, NameSurnamePair> NameSurnameMap;

// Функция для сравнения отображений
bool compareMaps(const NameSurnameMap& map1, const NameSurnameMap& map2) {
    return lexicographical_compare(map1.begin(), map1.end(), map2.begin(), map2.end());
}
void show(const NameSurnameMap& map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
        qDebug()  << it.key() << "," << it.value().first << "," << it.value().second;
    }
}
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QTextStream cin(stdin);
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    //QTextStream cout(stdout);
    //NameSurnameMap map;
    QMap<int, NameSurnamePair> map;
    map[1] = QPair<QString, QString>("abc1", "dfg2");
    map[2] = QPair<QString, QString>("abc3", "dfg4");
    map[3] = QPair<QString, QString>("abc5", "dfg6");

    cout << "1. Добавить  элемент" << "\n"
         << "2. Удалить элементы из заданного диапазона" << "\n"
         << "3. Поиск элементов больших заданного ключа" << "\n"
         << "4. Обменивает значения двух объектов (отображений)" << "\n"
         << "5. Замена значения элемента" << "\n"
         << "6. Выход из программы" << "\n";
    char op[100];
    cout << "Выберите операцию:" << endl;
    cin >> op;
    while (true) {
        switch (op[0]) {
        case '1':{
            cout << "Введите ключ:";
            int key;
            cin >> key;
            cout << "Введите имя:";
            QString name;
            cin >> name;
            cout << "Введите фамилию:";
            QString surname;
            cin >> surname;
            map.insert(key, qMakePair(name, surname));
            cout << "Элемент добавлен" << "\n";
            cout << "Ваш QMap:" << "\n";
            show(map);
            break;
        }
        case '2': {
            cout << "Введите начальный ключ диапазона:";
            int startKey;
            cin >> startKey;

            cout << "Введите конечный ключ диапазона:";
            int endKey;
            cin >> endKey;
            for (auto it = map.lowerBound(startKey); it != map.upperBound(endKey); ) {
                it = map.erase(it);
            }
            cout << "Элементы удалены"<<endl;
            cout << "Ваш QMap:" << "\n";
            show(map);
            break;
        }
        case '3': {
            cout << "Введите ключ:";
            int key;
            cin >> key;
            for (auto it = map.upperBound(key); it != map.end(); ++it) {
                qDebug() << it.key() << ", " << it.value().first << ", " << it.value().second;
            }
            break;
        }
        case '4': {
            int key1, key2;
            cout << "Введите ключи двух объектов для обмена значений: ";
            cin >> key1 >> key2;
            swap(map[key1], map[key2]);
            cout << "Значения обменены" << endl;
            cout << "Ваш QMap:" << "\n";
            show(map);
            break;
        }
        case '5':{
            int key;
            QString newFirstName, newLastName;
            cout << "Введите ключ элемента для замены значения: ";
            cin >> key;
            cout << "Введите новое имя и фамилию: ";
            cin >> newFirstName >> newLastName;
            map[key] = make_pair(newFirstName, newLastName);
            cout << "Ваш map:" << endl;
            show(map);
            break;}

        case '6':
            cout << "Спасибо за использование моей программы!";
            return 0;
        default:
            cout << "Ошибка, выберите другую операцию:" << endl;
        }
        cout << "Выберите операцию:" << endl;
        cin >> op;
    }

    return a.exec();
}
