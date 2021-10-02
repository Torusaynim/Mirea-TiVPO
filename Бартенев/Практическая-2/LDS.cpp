#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <limits>
using namespace std;

struct Node //элемент ЛДС
{
    int data; //информационное значение
    Node* prev, * next; //указатели на предыыдущий и следующий
    static Node* getnode(int data) //конструктор
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
};

class Lds //ЛДС
{
    Node* front; //левый элемент
    Node* rear; //правый элемент
    int Size; //количество элементов

public:
    Lds() //конструктор
    {
        front = rear = NULL;
        Size = 0;
    }

    void insertFront(int data) { //добавить слева
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //при переполнении
            cout << "Переполнение" << endl;
        else
        {
            if (front == NULL) //если ЛДС пуст
                rear = front = newNode;
            else
            {
                newNode->next = front;
                front->prev = newNode;
                front = newNode;
            }
            Size++;
            cout << "Элемент добавлен" << endl;
        }
    };

    void insertRear(int data, bool print) { //добавить справа
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //при переполнения
            cout << "Переполнение" << endl;
        else
        {
            if (rear == NULL) //если ЛДС пуст
                front = rear = newNode;
            else
            {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
            }
            Size++;
            if (print) { cout << "Элемент добавлен" << endl; }
        }
    };

    void deleteFront() { //удалить слева
        if (isEmpty()) //если ЛДС пуст
            cout << "ЛДС пуст" << endl;
        else
        {
            Node* temp = front;
            front = front->next;
            if (front == NULL)
                rear = NULL;
            else
                front->prev = NULL;
            free(temp);
            Size--;
            cout << "Элемент удалён" << endl;
        }
    };

    void deleteRear() { //удалить справа
        if (isEmpty()) //если ЛДС пуст
            cout << "ЛДС пуст";
        else
        {
            Node* temp = rear;
            rear = rear->prev;
            if (rear == NULL)
                front = NULL;
            else
                rear->next = NULL;
            free(temp);
            Size--;
            cout << "Элемент удалён" << endl;
        }
    };

    int getSize() { //получить количество элементов
        return Size;
    };;

    bool isEmpty() { //проверка на пустоту
        return (front == NULL);
    }

    void erase() { //удалить элементы ЛДС
        if (isEmpty()) //если ЛДС пуст
            cout << "ЛДС пуст" << endl;
        else
        {
            rear = NULL;
            while (front != NULL)
            {
                Node* temp = front;
                front = front->next;
                free(temp);
            }
            Size = 0;
            cout << "Элементы ЛДС удалены" << endl;
        }
    };

    void insert(int element, int data, bool after) { //вставить элемент в середину
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (ptr->data == element) {
                if (after) { //если нужно вставить после
                    Node* newNode = Node::getnode(data);
                    Node* temp = ptr->next;
                    ptr->next = newNode;
                    newNode->prev = ptr;
                    newNode->next = temp;
                    temp->prev = newNode;
                    Size++;
                }
                else { //если нужно вставить до
                    Node* newNode = Node::getnode(data);
                    Node* temp = ptr->prev;
                    ptr->prev = newNode;
                    newNode->prev = temp;
                    newNode->next = ptr;
                    temp->next = newNode;
                    Size++;
                }
                cout << "Элемент добавлен" << endl;
                break;
            }
            ptr = ptr->next;
        }
    };

    vector<Node*> findAll(int data, bool out) { //найти все вхождения элемента
        vector<int> indexes;
        vector<Node*> vector_ptrs;
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (data == ptr->data) {
                indexes.push_back(i);
                vector_ptrs.push_back(ptr);
            }
            ptr = ptr->next;
        }
        if (out) { //если нужно вывести все вхождения
            if (indexes.size() == 0) cout << "Элемент " << data << " не входит в ЛДС." << endl;
            else if (indexes.size() == 1) cout << "Элемент " << data << " находится на " << indexes[0] + 1 << " месте." << endl;
            else {
                cout << "Элемент " << data << " встречается на ";
                for (int i : indexes) {
                    cout << i + 1 << " ";
                }
                cout << "местах." << endl;
            }
        }
        return vector_ptrs;
    };

    void changeAll(int data, int new_data) { //заменить все вхождения элемента
        vector<Node*> temp;
        temp = findAll(data, false);
        for (Node* i : temp) {
            i->data = new_data;
        }
        cout << "Элементы заменены" << endl;
    };

    void print(bool straight) { //вывести ЛДС
        if (isEmpty()) //если ЛДС пуст
            cout << "ЛДС пуст" << endl;
        else{
            if (straight) { //вывести слева-направо
                Node* temp = front;
                for (int i = 0; i < this->getSize(); i++) {
                    cout << temp->data << "  ";
                    temp = temp->next;
                }
            }
            else { //вывести справа-налево
                Node* temp = rear;
                for (int i = 0; i < this->getSize(); i++) {
                    cout << temp->data << "  ";
                    temp = temp->prev;
                }
            }
            cout << endl;
        }
    };
};

void menu() { //функция вывода меню программы
    cout << endl;
    cout << "---Меню---" << endl;
    cout << "1x) Добавить элемент" << endl;
    cout << "    11) Добавить элемент в начало (слева)" << endl;
    cout << "    12) Добавить элемент в конец (справа)" << endl;
    cout << "    13x) Добавить элемент в середину" << endl;
    cout << "         131) Добавить элемент перед заданным" << endl;
    cout << "         132) Добавить элемент после заданного" << endl;
    cout << "2x) Удалить элемент(ы)" << endl;
    cout << "    21) Удалить левый элемент" << endl;
    cout << "    22) Удалить правый элемент" << endl;
    cout << "    23) Удалить все элементы" << endl;
    cout << "3) Найти все вхождения элемента" << endl;
    cout << "4) Изменить элемент во всех вхождениях" << endl;
    cout << "5x) Вывести (распечатать) ЛДС на экран" << endl;
    cout << "    51) Слева-направо" << endl;
    cout << "    52) Справа-налево" << endl;
    cout << "0) Выход" << endl;
}


int main()
{

	SetConsoleCP(1251); //установить кодировку 1251 для ввода
	SetConsoleOutputCP(1251); //установить кодировку 1251 для вывода

    Lds lds; //создать объект ЛДС
    int key, elem, data, new_data;
    cout << "Введите ЛДС из 10 элементов: ";
    for (int i = 0; i < 10; i++) { //начальный ввод элементов
        int temp;
        cin >> temp;
        lds.insertRear(temp, false);
    }
    cin.clear(); //на случай, если предыдущий ввод завершился с ошибкой
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool flag = true;
    while (flag) {
        menu();
        cout << endl << "Выберите команду: ";
        cin >> key;
        switch (key) {
        case 11:
            cout << "Введите добавляемый элемент: ";
            cin >> data;
            lds.insertFront(data);
            break;
        case 12:
            cout << "Введите добавляемый элемент: ";
            cin >> data;
            lds.insertRear(data, true);
            break;
        case 131:
            cout << "Введите элемент, перед которым нужно осуществить вставку: ";
            cin >> elem;
            cout << "Введите добавляемый элемент: ";
            cin >> data;
            lds.insert(elem, data, false);
            break;
        case 132:
            cout << "Введите элемент, после которого нужно осуществить вставку: ";
            cin >> elem;
            cout << "Введите добавляемый элемент: ";
            cin >> data;
            lds.insert(elem, data, true);
            break;
        case 21:
            lds.deleteFront();
            break;
        case 22:
            lds.deleteRear();
            break;
        case 23:
            lds.erase();
            break;
        case 3:
            cout << "Введите искомый элемент: ";
            cin >> data;
            lds.findAll(data, true);
            break;
        case 4:
            cout << "Введите изменяемый элемент: ";
            cin >> data;
            cout << "Введите элемент, на который нужно заменить: ";
            cin >> new_data;
            lds.changeAll(data, new_data);
            break;
        case 51:
            lds.print(true);
            break;
        case 52:
            lds.print(false);
            break;
        case 0:
            cout << "Вы точно хотите выйти? 0 - да, любой другой ввод - нет: ";
            cin >> key;
            if (key == 0)
                flag = false;
            break;
        default:
            cout << "Введен неверный номер команды" << endl;
            break;
        }
        cin.clear(); //на случай, если предыдущий ввод завершился с ошибкой
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Программа завершена" << endl;
    return 0;
}