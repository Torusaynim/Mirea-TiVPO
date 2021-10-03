#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
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
private:

    int getSize() { //получить количество элементов
        return Size;
    };;

    bool isEmpty() { //проверка на пустоту
        return (front == NULL);
    }

public:
    Node* front; //левый элемент
    Node* rear; //правый элемент
    int Size; //количество элементов

    Lds() //конструктор
    {
        front = rear = NULL;
        Size = 0;
    }

    int insertFront(int data) { //добавить слева
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //при переполнении
        {
            cout << "Переполнение" << endl;
            return 0;
        }
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
            return 1;
        }
    };

    int insertRear(int data, bool print) { //добавить справа
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //при переполнения
        {
            cout << "Переполнение" << endl;
            return 0;
        }
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
            return 1;
        }
    };

    int insert(int element, int data, bool after) { //вставить элемент в середину
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (ptr->data == element) {
                if (after) { //если нужно вставить после
                    Node* newNode = Node::getnode(data);
                    if (newNode == NULL) //при переполнения
                    {
                        cout << "Переполнение" << endl;
                        return 0;
                    }
                    Node* temp = ptr->next;
                    ptr->next = newNode;
                    newNode->prev = ptr;
                    newNode->next = temp;
                    temp->prev = newNode;
                    Size++;
                }
                else { //если нужно вставить до
                    Node* newNode = Node::getnode(data);
                    if (newNode == NULL) //при переполнения
                    {
                        cout << "Переполнение" << endl;
                        return 0;
                    }
                    Node* temp = ptr->prev;
                    ptr->prev = newNode;
                    newNode->prev = temp;
                    newNode->next = ptr;
                    temp->next = newNode;
                    Size++;
                }
                cout << "Элемент добавлен" << endl;
                return 1;
            }
            ptr = ptr->next;
        }
        cout << "Элемент не найден" << endl;
        return -1;
    };

    int deleteFront() { //удалить слева
        if (isEmpty()) //если ЛДС пуст
        {
            cout << "ЛДС пуст" << endl;
            return 0;
        }
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
            return 1;
        }
    };

    int deleteRear() { //удалить справа
        if (isEmpty()) //если ЛДС пуст
        {
            cout << "ЛДС пуст";
            return 0;
        }
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
            return 1;
        }
    };

    int erase() { //удалить элементы ЛДС
        if (isEmpty()) //если ЛДС пуст
        {
            cout << "ЛДС пуст" << endl;
            return 0;
        }
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
            return 1;
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
        if (out) { //если нужно вывести вхождения
            if (this->isEmpty())
                cout << "ЛДС пуст" << endl;
            else if (indexes.size() == 0)
                cout << "Элемент " << data << " не входит в ЛДС." << endl;
            else if (indexes.size() == 1)
                cout << "Элемент " << data << " находится на " << indexes[0] + 1 << " месте." << endl;
            else 
            {
                cout << "Элемент " << data << " встречается на ";
                for (int i : indexes) {
                    cout << i + 1 << " ";
                }
                cout << "местах." << endl;
            }
        }
        return vector_ptrs;
    };

    int changeAll(int data, int new_data) { //заменить все вхождения элемента
        vector<Node*> temp;
        if (this->isEmpty()) //если ЛДС пуст
        { 
            cout << "ЛДС пуст" << endl;
            return -1;
        }
        else
        {
            temp = findAll(data, false);
            if (temp.size() == 0) //если нужного элемента нет в ЛДС
            {
                cout << "Элемент не найден";
                return 0;
            }
            else
            {
                for (Node* i : temp) {
                    i->data = new_data;
                }
                cout << "Элементы заменены" << endl;
                return 1;
            }
        }
    };

    int print(bool straight) { //вывести ЛДС
        if (isEmpty()) //если ЛДС пуст
        {
            cout << "ЛДС пуст" << endl;
            return 0;
        }
        else
        {
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
            return 1;
        }
    };
};