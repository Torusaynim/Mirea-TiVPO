#include <iostream>

using namespace std;

struct node //элемент дека
{
    int data; //информационное значение
    node* prev, * next; //указатели на потомков
    node(int data) //конструктор
    {
        prev = NULL;
        next = NULL;
        this->data = data;
    }
};

class deque //дек
{
    node* front; //первый элемент
    node* last; //последний

public:
    deque() //конструктор
    {
        front = NULL;
        last = NULL;
    }

    void insertFront(int data); //добавить слева
    void insertLast(int data); //добавить справа
    void insertAfter(int data, int i); //добавить после
    void insertBefore(int data, int i); //добавить перед
    void deleteFront(); //удалить слева
    void deleteLast(); //удалить справа
    void deleteByData(int data); //удалить по значению
    void deleteByDataAll(int data); //удалить по значению (все вхождения)
    bool isEmpty(); //проверка на пустоту
    void eraseAll(); //удаление дека
    void printFront(); //вывести слева-направо
    void printLast(); //вывести справа-налево
};

bool deque::isEmpty()
{
    return (front == NULL); //нет первого элемента- нет дека
}

void deque::insertFront(int data)
{
    node* temp = new node(data); //создаем вставляемый элемент

    if (front == NULL) //нет певрого элемента- создаем дек
    {
        last = temp;
        front = temp;
    }
    else //иначе- вставляем перед первым
    {
        temp->next = front;
        front->prev = temp;
        front = temp;
    }
}

void deque::insertLast(int data)
{
    node* temp = new node(data); //создаем вставляемый элемент

    if (last == NULL) //нет последнего элемента- создаем дек
    {
        front = temp;
        last = temp;
    }
    else //иначе- вставляем после последнего
    {
        temp->prev = last;
        last->next = temp;
        last = temp;
    }

}

void deque::insertAfter(int data, int i)
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* curr = front; //иначе- идем по деку, пока не найдем нужный элемент
        while (curr != NULL)
        {
            if (curr->data == i)
                break;
            curr = curr->next;
        }
        if (curr == NULL) //если дек пройден, но переменная стала NULL- нет элемента
        {
            cout << "Элемент не найден\n";
            return;
        }

        node* temp = new node(data); //если найден- вставляем
        temp->data = data;
        temp->prev = curr;
        temp->next = curr->next;
        (curr->next)->prev = temp;
        curr->next = temp;
    }
}

void deque::insertBefore(int data, int i)
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* curr = front; //иначе- идем по деку, пока не найдем нужный элемент
        while (curr != NULL)
        {
            if (curr->data == i)
                break;
            curr = curr->next;
        }
        if (curr == NULL) //если дек пройден, но переменная стала NULL- нет элемента
        {
            cout << "Элемент не найден\n";
        }

        node* temp = new node(data); //если найден- вставляем ПОСЛЕ нужного
        temp->data = data;

        temp->prev = curr;
        temp->next = curr->next;
        (curr->next)->prev = temp;
        curr->next = temp;

        int num = curr->data; //и применяем трюк Вирта
        curr->data = temp->data;
        temp->data = num;
    }
}

void deque::deleteFront()
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* temp = front; //иначе- начинаем удаление самого левого
        front = front->next;
        if (front == NULL) //если элемент один- убираем указатели
            last = NULL;
        else
            front->prev = NULL; //иначе- только предыдущий
        free(temp); //и удаляем оканчательно
    }
}

void deque::deleteLast()
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    {
        node* temp = last; //иначе- начинаем удаление самого правого
        last = last->prev;

        if (last == NULL)  //если элемент один- убираем указатели
            front = NULL;
        else
            last->next = NULL; //иначе- только следующий
        free(temp); //и удаляем оканчательно
    }
}

void deque::deleteByData(int data)
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* curr = front; //иначе- ищем нужный
        while (curr != NULL)
        {
            if (curr->data == data)
                break;
            curr = curr->next;
        }
        if (curr == NULL) //случай, если его нет
        {
            cout << "Элемент не найден\n";
            return;
        }

        if (curr->prev == NULL) //если элемент оказался первым- удаляем первый
        {
            deleteFront();
            return;
        }
        if (curr->next == NULL) //если элемент оказался последним- удаляем последний
        {
            deleteLast();
            return;
        }

        (curr->prev)->next = curr->next; //иначе- общий случай
        (curr->next)->prev = curr->prev;
        curr->next = NULL;
        curr->prev = NULL;
        free(curr);
    }
}

void deque::deleteByDataAll(int data)
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* curr = front, * prev = NULL; //curr- текущий, prev- предыдущий текущему
        while (curr != NULL && curr->data == data) //удаляем все элемент слева, если такие есть
        {
            (curr->next)->prev = NULL;
            front = curr->next;
            curr->next = NULL;
            free(curr);
            curr = front;
        }

        while (curr != NULL) //иначе- более общий случай
        {
            while (curr != NULL && curr->data != data) //идем по деку
            {
                prev = curr;
                curr = curr->next;
            }
            if (curr == NULL) //если все удалено или ничего не найдено- выходим
            {
                return;
            }

            prev->next = curr->next; //удаляем элемент
            if (curr->next != NULL)
                (curr->next)->prev = prev;
            else
                last = prev; //случай, когда удаляемый элемент- последний
            curr->next = NULL;
            curr->prev = NULL;
            free(curr);
            curr = prev->next;
        }
    }
}

void deque::printFront()
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* temp = front;
        while (temp != NULL) //выводим слева-направо
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
    cout << '\n';
}

void deque::printLast()
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        node* temp = last;
        while (temp != NULL) //выводим справа-налево
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
    }
    cout << '\n';
}

void deque::eraseAll()
{
    if (isEmpty()) //нет дека- выводим сообщение
        cout << "Дека нет\n";
    else
    {
        last = NULL; //удаляем все элементы в цикле
        while (front != NULL)
        {
            node* temp = front;
            front = front->next;
            free(temp);
        }
        cout << "Дек удален\n";
    }
}

int main()
{
    setlocale(LC_CTYPE, "rus");
    deque deq;
    int data;
    int command = 1, subcommand = 0, num;

    cout << "Введите 10 целочисленных знчений для создания дека\n";

    for (int i = 0; i < 10; i++)
    {
        cin >> data;
        deq.insertLast(data);
    }

    while (command != 0)
    {
        cout << "Выберите команду:\n1.Добавить элемент\n2.Удалить элемент\n3.Вывести дек на экран\n4.Удалить дек\n0.Выход из программы\n";
        cin >> command;
        switch (command)
        {
        case 1:
        {
            cout << "Выберите подкомманду:\n1.В дек слева\n2.В дек справа\n3.В середину дека\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Введите значение\n";
                cin >> data;
                deq.insertFront(data);
                break;
            }
            case 2:
            {
                cout << "Введите значение\n";
                cin >> data;
                deq.insertLast(data);
                break;
            }
            case 3:
            {
                cout << "Выберите подкоманду:\n1.Добавить элемент после заданного\n2.Добавить элемент перед заданным\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите новое и старое значения элемента\n";
                    cin >> data >> num;
                    deq.insertAfter(data, num);
                    break;
                }
                case 2:
                {
                    cout << "Введите новое и старое значения элемента\n";
                    cin >> data >> num;
                    deq.insertBefore(data, num);
                    break;
                }
                default:
                {
                    cout << "Некорректное значение- попробуйте снова\n";
                    break;
                }
                }
                break;
            }
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 2:
        {
            cout << "Выберите подкомманду:\n1.Первый элемент\n2.Последний элемент\n3.Заданный элемент\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                deq.deleteFront();
                break;
            }
            case 2:
            {
                deq.deleteLast();
                break;
            }
            case 3:
            {
                cout << "Выберите подкоманду:\n1.Первое вхождение\n2.Все вхождения\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите значение элемента\n";
                    cin >> data;
                    deq.deleteByData(data);
                    break;
                }
                case 2:
                {
                    cout << "Введите значение элемента\n";
                    cin >> data;
                    deq.deleteByDataAll(data);
                    break;
                }
                default:
                {
                    cout << "Некорректное значение- попробуйте снова\n";
                    break;
                }
                }
                break;
            }
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 3:
        {
            cout << "Выберите подкоманду:\n1.Проход слева-направо\n2.Проход справа-налево\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                deq.printFront();
                break;
            }
            case 2:
            {
                deq.printLast();
                break;
            }
            default:
            {
                cout << "Некорректное значение- попробуйте снова\n";
                break;
            }
            }
            break;
        }
        case 4:
        {
            deq.eraseAll();
            break;
        }
        case 0:
        {
            cout << "Введите ноль снова, если хотите закончить программу\n";
            cin >> command;
            if (command == 0)
            {
                cout << "Спасибо за внимание! Работа программы завершена";
                return 0;
            }
            break;
        }
        default:
        {
            cout << "Некорректное значение- попробуйте снова\n";
            break;
        }
        }
        cout << '\n';
    }
}

//1 2 3 4 5 6 7 8 9 1

//1 1 2 1 3 1 4 1 5 1