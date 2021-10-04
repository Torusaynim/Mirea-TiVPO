#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node //ýëåìåíò ËÄÑ
{
    int data; //èíôîðìàöèîííîå çíà÷åíèå
    Node* prev, * next; //óêàçàòåëè íà ïðåäûûäóùèé è ñëåäóþùèé
    static Node* getnode(int data) //êîíñòðóêòîð
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
};

class Lds //ËÄÑ
{
private:

    int getSize() { //ïîëó÷èòü êîëè÷åñòâî ýëåìåíòîâ
        return Size;
    };;

    bool isEmpty() { //ïðîâåðêà íà ïóñòîòó
        return (front == NULL);
    }

public:
    Node* front; //ëåâûé ýëåìåíò
    Node* rear; //ïðàâûé ýëåìåíò
    int Size; //êîëè÷åñòâî ýëåìåíòîâ

    Lds() //êîíñòðóêòîð
    {
        front = rear = NULL;
        Size = 0;
    }

    int insertFront(int data) { //äîáàâèòü ñëåâà
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //ïðè ïåðåïîëíåíèè
        {
            cout << "Ïåðåïîëíåíèå" << endl;
            return 0;
        }
        else
        {
            if (front == NULL) //åñëè ËÄÑ ïóñò
                rear = front = newNode;
            else
            {
                newNode->next = front;
                front->prev = newNode;
                front = newNode;
            }
            Size++;
            cout << "Ýëåìåíò äîáàâëåí" << endl;
            return 1;
        }
    };

    int insertRear(int data, bool print) { //äîáàâèòü ñïðàâà
        Node* newNode = Node::getnode(data);
        if (newNode == NULL) //ïðè ïåðåïîëíåíèÿ
        {
            cout << "Ïåðåïîëíåíèå" << endl;
            return 0;
        }
        else
        {
            if (rear == NULL) //åñëè ËÄÑ ïóñò
                front = rear = newNode;
            else
            {
                newNode->prev = rear;
                rear->next = newNode;
                rear = newNode;
            }
            Size++;
            if (print) { cout << "Ýëåìåíò äîáàâëåí" << endl; }
            return 1;
        }
    };

    int insert(int element, int data, bool after) { //âñòàâèòü ýëåìåíò â ñåðåäèíó
        Node* ptr = front;
        for (int i = 0; i < this->getSize(); i++) {
            if (ptr->data == element) {
                if (after) { //åñëè íóæíî âñòàâèòü ïîñëå
                    if (i == this->getSize() - 1)
                        this->insertRear(data, false);
                    else
                    {
                        Node* newNode = Node::getnode(data);
                        if (newNode == NULL) //ïðè ïåðåïîëíåíèÿ
                        {
                            cout << "Ïåðåïîëíåíèå" << endl;
                            return 0;
                        }
                        Node* temp = ptr->next;
                        ptr->next = newNode;
                        newNode->prev = ptr;
                        newNode->next = temp;
                        temp->prev = newNode;
                        Size++;
                    }
                }
                else { //åñëè íóæíî âñòàâèòü äî
                    if (i == 0)
                        this->insertFront(data);
                    else
                    {
                        Node* newNode = Node::getnode(data);
                        if (newNode == NULL) //ïðè ïåðåïîëíåíèÿ
                        {
                            cout << "Ïåðåïîëíåíèå" << endl;
                            return 0;
                        }
                        Node* temp = ptr->prev;
                        ptr->prev = newNode;
                        newNode->prev = temp;
                        newNode->next = ptr;
                        temp->next = newNode;
                        Size++;
                    }
                }
                cout << "Ýëåìåíò äîáàâëåí" << endl;
                return 1;
            }
            ptr = ptr->next;
        }
        cout << "Ýëåìåíò íå íàéäåí" << endl;
        return -1;
    };

    int deleteFront() { //óäàëèòü ñëåâà
        if (isEmpty()) //åñëè ËÄÑ ïóñò
        {
            cout << "ËÄÑ ïóñò" << endl;
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
            cout << "Ýëåìåíò óäàë¸í" << endl;
            return 1;
        }
    };

    int deleteRear() { //óäàëèòü ñïðàâà
        if (isEmpty()) //åñëè ËÄÑ ïóñò
        {
            cout << "ËÄÑ ïóñò";
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
            cout << "Ýëåìåíò óäàë¸í" << endl;
            return 1;
        }
    };

    int erase() { //óäàëèòü ýëåìåíòû ËÄÑ
        if (isEmpty()) //åñëè ËÄÑ ïóñò
        {
            cout << "ËÄÑ ïóñò" << endl;
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
            cout << "Ýëåìåíòû ËÄÑ óäàëåíû" << endl;
            return 1;
        }
    };

    vector<Node*> findAll(int data, bool out) { //íàéòè âñå âõîæäåíèÿ ýëåìåíòà
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
        if (out) { //åñëè íóæíî âûâåñòè âõîæäåíèÿ
            if (this->isEmpty())
                cout << "ËÄÑ ïóñò" << endl;
            else if (indexes.size() == 0)
                cout << "Ýëåìåíò " << data << " íå âõîäèò â ËÄÑ." << endl;
            else if (indexes.size() == 1)
                cout << "Ýëåìåíò " << data << " íàõîäèòñÿ íà " << indexes[0] + 1 << " ìåñòå." << endl;
            else 
            {
                cout << "Ýëåìåíò " << data << " âñòðå÷àåòñÿ íà ";
                for (int i : indexes) {
                    cout << i + 1 << " ";
                }
                cout << "ìåñòàõ." << endl;
            }
        }
        return vector_ptrs;
    };

    int changeAll(int data, int new_data) { //çàìåíèòü âñå âõîæäåíèÿ ýëåìåíòà
        vector<Node*> temp;
        if (this->isEmpty()) //åñëè ËÄÑ ïóñò
        { 
            cout << "ËÄÑ ïóñò" << endl;
            return -1;
        }
        else
        {
            temp = findAll(data, false);
            if (temp.size() == 0) //åñëè íóæíîãî ýëåìåíòà íåò â ËÄÑ
            {
                cout << "Ýëåìåíò íå íàéäåí";
                return 0;
            }
            else
            {
                for (Node* i : temp) {
                    i->data = new_data;
                }
                cout << "Ýëåìåíòû çàìåíåíû" << endl;
                return 1;
            }
        }
    };

    int print(bool straight) { //âûâåñòè ËÄÑ
        if (isEmpty()) //åñëè ËÄÑ ïóñò
        {
            cout << "ËÄÑ ïóñò" << endl;
            return 0;
        }
        else
        {
            if (straight) { //âûâåñòè ñëåâà-íàïðàâî
                Node* temp = front;
                for (int i = 0; i < this->getSize(); i++) {
                    cout << temp->data << "  ";
                    temp = temp->next;
                }
            }
            else { //âûâåñòè ñïðàâà-íàëåâî
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
