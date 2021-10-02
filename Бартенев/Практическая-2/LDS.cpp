#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <limits>
using namespace std;

struct Node //������� ���
{
    int data; //�������������� ��������
    Node* prev, * next; //��������� �� ����������� � ���������
    static Node* getnode(int data) //�����������
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
};

class Lds //���
{
    Node* front; //����� �������
    Node* rear; //������ �������
    int Size; //���������� ���������

public:
    Lds() //�����������
    {
        front = rear = NULL;
        Size = 0;
    }

    void insertFront(int data) { //�������� �����
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //��� ������������
            cout << "������������" << endl;
        else
        {
            if (front == NULL) //���� ��� ����
                rear = front = newNode;
            else
            {
                newNode->next = front;
                front->prev = newNode;
                front = newNode;
            }
            Size++;
            cout << "������� ��������" << endl;
        }
    };

    void insertRear(int data, bool print) { //�������� ������
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //��� ������������
            cout << "������������" << endl;
        else
        {
            if (rear == NULL) //���� ��� ����
                front = rear = newNode;
            else
            {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
            }
            Size++;
            if (print) { cout << "������� ��������" << endl; }
        }
    };

    void deleteFront() { //������� �����
        if (isEmpty()) //���� ��� ����
            cout << "��� ����" << endl;
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
            cout << "������� �����" << endl;
        }
    };

    void deleteRear() { //������� ������
        if (isEmpty()) //���� ��� ����
            cout << "��� ����";
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
            cout << "������� �����" << endl;
        }
    };

    int getSize() { //�������� ���������� ���������
        return Size;
    };;

    bool isEmpty() { //�������� �� �������
        return (front == NULL);
    }

    void erase() { //������� �������� ���
        if (isEmpty()) //���� ��� ����
            cout << "��� ����" << endl;
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
            cout << "�������� ��� �������" << endl;
        }
    };

    void insert(int element, int data, bool after) { //�������� ������� � ��������
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (ptr->data == element) {
                if (after) { //���� ����� �������� �����
                    Node* newNode = Node::getnode(data);
                    Node* temp = ptr->next;
                    ptr->next = newNode;
                    newNode->prev = ptr;
                    newNode->next = temp;
                    temp->prev = newNode;
                    Size++;
                }
                else { //���� ����� �������� ��
                    Node* newNode = Node::getnode(data);
                    Node* temp = ptr->prev;
                    ptr->prev = newNode;
                    newNode->prev = temp;
                    newNode->next = ptr;
                    temp->next = newNode;
                    Size++;
                }
                cout << "������� ��������" << endl;
                break;
            }
            ptr = ptr->next;
        }
    };

    vector<Node*> findAll(int data, bool out) { //����� ��� ��������� ��������
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
        if (out) { //���� ����� ������� ��� ���������
            if (indexes.size() == 0) cout << "������� " << data << " �� ������ � ���." << endl;
            else if (indexes.size() == 1) cout << "������� " << data << " ��������� �� " << indexes[0] + 1 << " �����." << endl;
            else {
                cout << "������� " << data << " ����������� �� ";
                for (int i : indexes) {
                    cout << i + 1 << " ";
                }
                cout << "������." << endl;
            }
        }
        return vector_ptrs;
    };

    void changeAll(int data, int new_data) { //�������� ��� ��������� ��������
        vector<Node*> temp;
        temp = findAll(data, false);
        for (Node* i : temp) {
            i->data = new_data;
        }
        cout << "�������� ��������" << endl;
    };

    void print(bool straight) { //������� ���
        if (isEmpty()) //���� ��� ����
            cout << "��� ����" << endl;
        else{
            if (straight) { //������� �����-�������
                Node* temp = front;
                for (int i = 0; i < this->getSize(); i++) {
                    cout << temp->data << "  ";
                    temp = temp->next;
                }
            }
            else { //������� ������-������
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

void menu() { //������� ������ ���� ���������
    cout << endl;
    cout << "---����---" << endl;
    cout << "1x) �������� �������" << endl;
    cout << "    11) �������� ������� � ������ (�����)" << endl;
    cout << "    12) �������� ������� � ����� (������)" << endl;
    cout << "    13x) �������� ������� � ��������" << endl;
    cout << "         131) �������� ������� ����� ��������" << endl;
    cout << "         132) �������� ������� ����� ���������" << endl;
    cout << "2x) ������� �������(�)" << endl;
    cout << "    21) ������� ����� �������" << endl;
    cout << "    22) ������� ������ �������" << endl;
    cout << "    23) ������� ��� ��������" << endl;
    cout << "3) ����� ��� ��������� ��������" << endl;
    cout << "4) �������� ������� �� ���� ����������" << endl;
    cout << "5x) ������� (�����������) ��� �� �����" << endl;
    cout << "    51) �����-�������" << endl;
    cout << "    52) ������-������" << endl;
    cout << "0) �����" << endl;
}


int main()
{

	SetConsoleCP(1251); //���������� ��������� 1251 ��� �����
	SetConsoleOutputCP(1251); //���������� ��������� 1251 ��� ������

    Lds lds; //������� ������ ���
    int key, elem, data, new_data;
    cout << "������� ��� �� 10 ���������: ";
    for (int i = 0; i < 10; i++) { //��������� ���� ���������
        int temp;
        cin >> temp;
        lds.insertRear(temp, false);
    }
    cin.clear(); //�� ������, ���� ���������� ���� ���������� � �������
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    bool flag = true;
    while (flag) {
        menu();
        cout << endl << "�������� �������: ";
        cin >> key;
        switch (key) {
        case 11:
            cout << "������� ����������� �������: ";
            cin >> data;
            lds.insertFront(data);
            break;
        case 12:
            cout << "������� ����������� �������: ";
            cin >> data;
            lds.insertRear(data, true);
            break;
        case 131:
            cout << "������� �������, ����� ������� ����� ����������� �������: ";
            cin >> elem;
            cout << "������� ����������� �������: ";
            cin >> data;
            lds.insert(elem, data, false);
            break;
        case 132:
            cout << "������� �������, ����� �������� ����� ����������� �������: ";
            cin >> elem;
            cout << "������� ����������� �������: ";
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
            cout << "������� ������� �������: ";
            cin >> data;
            lds.findAll(data, true);
            break;
        case 4:
            cout << "������� ���������� �������: ";
            cin >> data;
            cout << "������� �������, �� ������� ����� ��������: ";
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
            cout << "�� ����� ������ �����? 0 - ��, ����� ������ ���� - ���: ";
            cin >> key;
            if (key == 0)
                flag = false;
            break;
        default:
            cout << "������ �������� ����� �������" << endl;
            break;
        }
        cin.clear(); //�� ������, ���� ���������� ���� ���������� � �������
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "��������� ���������" << endl;
    return 0;
}