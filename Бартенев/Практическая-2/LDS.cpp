#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
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
private:

    int getSize() { //�������� ���������� ���������
        return Size;
    };;

    bool isEmpty() { //�������� �� �������
        return (front == NULL);
    }

public:
    Node* front; //����� �������
    Node* rear; //������ �������
    int Size; //���������� ���������

    Lds() //�����������
    {
        front = rear = NULL;
        Size = 0;
    }

    int insertFront(int data) { //�������� �����
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //��� ������������
        {
            cout << "������������" << endl;
            return 0;
        }
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
            return 1;
        }
    };

    int insertRear(int data, bool print) { //�������� ������
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //��� ������������
        {
            cout << "������������" << endl;
            return 0;
        }
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
            return 1;
        }
    };

    int insert(int element, int data, bool after) { //�������� ������� � ��������
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (ptr->data == element) {
                if (after) { //���� ����� �������� �����
                    Node* newNode = Node::getnode(data);
                    if (newNode == NULL) //��� ������������
                    {
                        cout << "������������" << endl;
                        return 0;
                    }
                    Node* temp = ptr->next;
                    ptr->next = newNode;
                    newNode->prev = ptr;
                    newNode->next = temp;
                    temp->prev = newNode;
                    Size++;
                }
                else { //���� ����� �������� ��
                    Node* newNode = Node::getnode(data);
                    if (newNode == NULL) //��� ������������
                    {
                        cout << "������������" << endl;
                        return 0;
                    }
                    Node* temp = ptr->prev;
                    ptr->prev = newNode;
                    newNode->prev = temp;
                    newNode->next = ptr;
                    temp->next = newNode;
                    Size++;
                }
                cout << "������� ��������" << endl;
                return 1;
            }
            ptr = ptr->next;
        }
        cout << "������� �� ������" << endl;
        return -1;
    };

    int deleteFront() { //������� �����
        if (isEmpty()) //���� ��� ����
        {
            cout << "��� ����" << endl;
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
            cout << "������� �����" << endl;
            return 1;
        }
    };

    int deleteRear() { //������� ������
        if (isEmpty()) //���� ��� ����
        {
            cout << "��� ����";
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
            cout << "������� �����" << endl;
            return 1;
        }
    };

    int erase() { //������� �������� ���
        if (isEmpty()) //���� ��� ����
        {
            cout << "��� ����" << endl;
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
            cout << "�������� ��� �������" << endl;
            return 1;
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
        if (out) { //���� ����� ������� ���������
            if (this->isEmpty())
                cout << "��� ����" << endl;
            else if (indexes.size() == 0)
                cout << "������� " << data << " �� ������ � ���." << endl;
            else if (indexes.size() == 1)
                cout << "������� " << data << " ��������� �� " << indexes[0] + 1 << " �����." << endl;
            else 
            {
                cout << "������� " << data << " ����������� �� ";
                for (int i : indexes) {
                    cout << i + 1 << " ";
                }
                cout << "������." << endl;
            }
        }
        return vector_ptrs;
    };

    int changeAll(int data, int new_data) { //�������� ��� ��������� ��������
        vector<Node*> temp;
        if (this->isEmpty()) //���� ��� ����
        { 
            cout << "��� ����" << endl;
            return -1;
        }
        else
        {
            temp = findAll(data, false);
            if (temp.size() == 0) //���� ������� �������� ��� � ���
            {
                cout << "������� �� ������";
                return 0;
            }
            else
            {
                for (Node* i : temp) {
                    i->data = new_data;
                }
                cout << "�������� ��������" << endl;
                return 1;
            }
        }
    };

    int print(bool straight) { //������� ���
        if (isEmpty()) //���� ��� ����
        {
            cout << "��� ����" << endl;
            return 0;
        }
        else
        {
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
            return 1;
        }
    };
};