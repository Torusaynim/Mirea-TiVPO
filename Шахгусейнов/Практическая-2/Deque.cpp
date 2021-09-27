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
    void findFront(int data); //найти слева-направо
    void findLast(int data); //найти справа-налево
    void findAll(int data); //найти все вхождения
    bool isEmpty(); //проверка на пустоту
    void eraseAll(); //удаление дека
    void printFront(); //вывести слева-направо
    void printLast(); //вывести справа-налево
    void changeByData(int oldData, int newData); //изменить по значению
    void changeByDataAll(int oldData, int newData); //изменить по значению (все вхождения)
    void changeByIndexFront(int index, int newData); //изменить по позиции слева-направо
    void changeByIndexLast(int index, int newData); //изменить по позиции справа-налево
    void swapFront(int data1, int data2); //поменять два элемента слева-направо
    void swapLast(int data1, int data2); //поменять два элемента справа-налево
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
                cout << "Функция выполнила свою работу\n";
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

void deque::findFront(int data)
{
    node* curr = front; //ищем нужный элемент слева-направо
    int i = 0;
    while (curr != NULL)
    {
        if (curr->data == data)
        {
            cout << "Найден элемент под номером " << i << "\n"; //если нашли- выводим его с индексом
            return;
        }
        curr = curr->next;
        i++;
    }
    cout << "Элемент не найден\n"; //если не вышли из цикла раньше
}

void deque::findLast(int data)
{
    node* curr = last; //ищем нужный элемент справа-налево
    int i = 0;
    while (curr != NULL)
    {
        if (curr->data == data)
        {
            cout << "Найден элемент под номером " << i << "\n"; //если нашли- выводим его с индексом
            return;
        }
        curr = curr->prev;
        i++;
    }
    cout << "Элемент не найден\n"; //если не вышли из цикла раньше
}

void deque::findAll(int data)
{
    node* curr = front; //ищем нужные элементы
    int i = 0;
    while (curr != NULL)
    {
        if (curr->data == data)
            i++; //инкрементируем счетчик
        curr = curr->next;
    }

    if (i == 0) //если счетчик не изменился- элементов нет в деке
        cout << "Элемент не найден\n";
    else
        cout << "Всего элементов " << data << " : " << i << '\n';
}

void deque::changeByData(int oldData, int newData)
{
    node* curr = front;
    while (curr != NULL) //ищем нужный элемент
    {
        if (curr->data == oldData)
        {
            curr->data = newData; //при нахождении- выходим с заменой
            cout << "Изменено\n";
            return;
        }
        curr = curr->next;
    }
    cout << "Элемент не найден\n"; //если не вышли в цикле- элемента нет
}

void deque::changeByDataAll(int oldData, int newData)
{
    node* curr = front;
    bool flag = false;
    while (curr != NULL)  //ищем нужные элементы
    {
        if (curr->data == oldData) //при нахождении- заменяем и меняем значение флага
        {
            curr->data = newData;
            flag = true;
        }
        curr = curr->next;
    }

    if (flag)
        cout << "Изменены\n";
    else //если флаг не изменен- элемент не был найден
        cout << "Элемент не найден\n";
}

void deque::changeByIndexFront(int index, int newData)
{
    node* curr = front; //ищем нужный слева-направо
    while (curr != NULL)
    {
        if (index == 0)
        {
            curr->data = newData; //при нахождении- меняем с выходом
            cout << "Изменено\n";
            return;
        }
        curr = curr->next;
        index--;
    }
    cout << "Элемент не найден\n"; //если не вышли в цикле- нет элемента
}

void deque::changeByIndexLast(int index, int newData)
{
    node* curr = last; //ищем нужный слева-направо
    while (curr != NULL)
    {
        if (index == 0)
        {
            curr->data = newData; //при нахождении- меняем с выходом
            cout << "Изменено\n";
            return;
        }
        curr = curr->prev;
        index--;
    }
    cout << "Элемент не найден\n"; //если не вышли в цикле- нет элемента
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
    }
}

void deque::swapFront(int data1, int data2)
{
    if (isEmpty()) //нет дека- выводим сообщение
    {
        cout << "Дека нет\n";
        return;
    }

    if (data1 == data2) //введены одинаковые значения- выходим
    {
        cout << "Значения поменялись местами\n";
        return;
    }

    node* curr1 = front; //ищем нужный первый
    while (curr1->data != data1 && curr1 != NULL)
        curr1 = curr1->next;

    node* curr2 = front; //и второй
    while (curr2->data != data2 && curr2 != NULL)
        curr2 = curr2->next;

    if (curr1 == NULL || curr2 == NULL) //если хотя бы один не найден- выходим из функции
    {
        cout << "Не найдено\n";
        return;
    }

    if (curr1->prev == NULL && curr2->next == NULL) //рассматриваем случай при обмене первого и последнего элемента
    {
        (curr1->next)->prev = curr2;
        (curr2->prev)->next = curr1;
        curr2->next = curr1->next;
        curr1->prev = curr2->prev;
        curr1->next = NULL;
        curr2->prev = NULL;
        last = curr1;
        front = curr2;
        cout << "Изменены\n";
        return;
    }

    if (curr1->prev == NULL) //рассматриваем случай при обмене первого и другого элемента
    {
        (curr2->next)->prev = curr1;
        (curr2->prev)->next = curr1;
        (curr1->next)->prev = curr2;
        node* temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
        curr1->prev = curr2->prev;
        curr2->prev = NULL;
        front = curr2;
        cout << "Изменены\n";
        return;
    }

    if (curr2->next == NULL) //рассматриваем случай при обмене другого и последнего элемента
    {
        (curr2->prev)->next = curr1;
        (curr1->prev)->next = curr2;
        (curr1->next)->prev = curr2;
        node* temp = curr2->prev;
        curr2->prev = curr1->prev;
        curr1->prev = temp;
        curr2->next = curr1->next;
        curr1->next = NULL;
        last = curr1;
        cout << "Изменены\n";
        return;
    }

    (curr1->prev)->next = curr2; //и рассматриваем общий случай
    (curr2->prev)->next = curr1;
    (curr1->next)->prev = curr2;
    (curr2->next)->prev = curr1;
    node* temp = curr1->prev;
    curr1->prev = curr2->prev;
    curr2->prev = temp;
    temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
    cout << "Изменены\n";
}

void deque::swapLast(int data1, int data2)
{
    if (isEmpty()) //нет дека- выводим сообщение
    {
        cout << "Дека нет\n";
        return;
    }

    if (data1 == data2) //введены одинаковые значения- выходим
    {
        cout << "Значения поменялись местами\n";
        return;
    }

    node* curr1 = last; //ищем нужный первый
    while (curr1->data != data1 && curr1 != NULL)
        curr1 = curr1->prev;

    node* curr2 = last; //и второй
    while (curr2->data != data2 && curr2 != NULL)
        curr2 = curr2->prev;

    if (curr1 == NULL || curr2 == NULL) //если хотя бы один не найден- выходим из функции
    {
        cout << "Не найдено\n";
        return;
    }
    
    if (curr1->prev == NULL && curr2->next == NULL) //рассматриваем случай при обмене первого и последнего элемента
    {
        (curr1->next)->prev = curr2;
        (curr2->prev)->next = curr1;
        curr2->next = curr1->next;
        curr1->prev = curr2->prev;
        curr1->next = NULL;
        curr2->prev = NULL;
        last = curr1;
        front = curr2;
        cout << "Изменены\n";
        return;
    }

    if (curr1->prev == NULL) //рассматриваем случай при обмене первого и другого элемента
    {
        (curr2->next)->prev = curr1;
        (curr2->prev)->next = curr1;
        (curr1->next)->prev = curr2;
        node* temp = curr2->next;
        curr2->next = curr1->next;
        curr1->next = temp;
        curr1->prev = curr2->prev;
        curr2->prev = NULL;
        front = curr2;
        cout << "Изменены\n";
        return;
    }

    if (curr2->next == NULL)  //рассматриваем случай при обмене другого и последнего элемента
    {
        (curr2->prev)->next = curr1;
        (curr1->prev)->next = curr2;
        (curr1->next)->prev = curr2;
        node* temp = curr2->prev;
        curr2->prev = curr1->prev;
        curr1->prev = temp;
        curr2->next = curr1->next;
        curr1->next = NULL;
        last = curr1;
        cout << "Изменены\n";
        return;
    }

    (curr1->prev)->next = curr2; //и рассматриваем общий случай
    (curr2->prev)->next = curr1;
    (curr1->next)->prev = curr2;
    (curr2->next)->prev = curr1;
    node* temp = curr1->prev;
    curr1->prev = curr2->prev;
    curr2->prev = temp;
    temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
    cout << "Изменены\n";
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
        cout << "Выберите команду:\n1.Добавить элемент\n2.Удалить элемент\n3.Найти элемент\n4.Изменить элемент\n5.Поменять два элемента местами\n6.Вывести дек на экран\n7.Удалить дек\n0.Выход из программы\n";
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
                cout << '\n';
                break;
            }
            case 2:
            {
                cout << "Введите значение\n";
                cin >> data;
                deq.insertLast(data);
                cout << '\n';
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
                    cout << '\n';
                    break;
                }
                case 2:
                {
                    cout << "Введите новое и старое значения элемента\n";
                    cin >> data >> num;
                    deq.insertBefore(data, num);
                    cout << '\n';
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
            }
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
                cout << "Выберите подкоманду:\n1.Проход слева-направо\n2.Проход справа-налево\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите значение\n";
                    cin >> data;
                    deq.findFront(data);
                    break;
                }
                case 2:
                {
                    cout << "Введите значение\n";
                    cin >> data;
                    deq.findLast(data);
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
                cout << "Введите значение\n";
                cin >> data;
                deq.findAll(data);
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
            cout << "Выберите подкоманду:\n1.По значению\n2.По порядковому номеру\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Выберите подкоманду:\n1.Первое вхождение\n2.Все вхождения\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите старое и новое значение элемента\n";
                    cin >> data >> num;
                    deq.changeByData(data, num);
                    break;
                }
                case 2:
                {
                    cout << "Введите старое и новое значение элемента\n";
                    cin >> data >> num;
                    deq.changeByDataAll(data, num);
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
                cout << "Выберите подкоманду:\n1.Проход слева-направо\n2.Проход справа-налево\n";
                cin >> subcommand;
                switch (subcommand)
                {
                case 1:
                {
                    cout << "Введите индекс и новое значение\n";
                    cin >> num >> data;
                    deq.changeByIndexFront(num, data);
                    break;
                }
                case 2:
                {
                    cout << "Введите индекс и новое значение\n";
                    cin >> num >> data;
                    deq.changeByIndexLast(num, data);
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
            break;
            }
            break;
        }
        case 5:
        {
            cout << "Выберите подкоманду:\n1.Проход слева-направо\n2.Проход справа-налево\n";
            cin >> subcommand;
            switch (subcommand)
            {
            case 1:
            {
                cout << "Введите два значения\n";
                cin >> num >> data;
                deq.swapFront(num, data);
                break;
            }
            case 2:
            {
                cout << "Введите два значения\n";
                cin >> num >> data;
                deq.swapLast(num, data);
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
        case 6:
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
        case 7:
        {
            deq.eraseAll();
            cout << "Дек удален\n";
            break;
        }
        case 0:
        {
            cout << "Введите ноль снова, если хотите закончить программу\n";
            cin >> command;
            if (command == 0)
            {
                cout << "Спасибо за внимание! Работа программы завершена\n";
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

//1 2 3 4 5 6 7 8 9 10

//1 1 2 1 3 1 4 1 5 1