# Банк
Программа реализует простейшее представление системы банковских аккаунтов.

Функционал программы:
- Банковский аккаунт
  - Создание банковского аккаунта
  - Проверка возможности вывода средств со счёта
  - Проверка, является ли баланс положительным
- Клиент банка
  - Создание клиента банка
  - Пополнение счёта
  - Снятие денег со счёта
  - Начисление процентов по ставке
  - Отображение баланса счетов
  - Отображение информации о клиенте банка

**Документация доступна по ссылке [BankAccountDocs](https://bankaccountdocs.ivankulagin.repl.co/)**

Ниже представлена Markdown-версия документации.

* * *

## Документация BankAccount.py


### class BankAccount.BankAccount(balance, int_rate)
Создает банковский аккаунт с атрибутами: баланс, процентная ставка


#### static can_withdraw(balance, amount)
Определяет возможность вывода средств со счёта


* **Параметры**

    
    * **balance** (*Integer*) – Баланс банковского счёта


    * **amount** (*Integer*) – Сумма перевода



* **Результат**

    True, если можно вывести средства, иначе Else



* **Тип результата**

    Boolean



#### static is_pos(balance)
Проверяет, является ли баланс банковского счёта положительным


* **Параметры**

    **balance** (*Integer*) – Баланс банковского счёта



* **Результат**

    True, если баланс положительный, иначе Else



* **Тип результата**

    Boolean



### class BankAccount.User(first_name, last_name, age)
Создаёт клиента банка с атрибутами: имя, фамилия, возраст


* **Параметры**

    
    * **first_name** (*String*) – Имя клиента


    * **last_name** (*String*) – Фамилия клиента


    * **age** (*Integer*) – Возраст клиента



#### deposit(amount, type)
Пополнение счета: проверяет тип счёта и увеличивает значение свойства balance нужного счёта
на определённую сумму


* **Параметры**

    
    * **amount** (*Integer*) – Сумма пополнения


    * **type** (*String*) – Тип счёта (текущий/сберегательный)



* **Результат**

    Изменённое значение баланса счёта



* **Тип результата**

    Integer



#### display_account_info()
Отображает информацию о балансе на счетах: баланс текущего счёта и сберегательного счёта


* **Результат**

    Баланс счетов



* **Тип результата**

    String



#### identify()
Отображает информацию о пользователе: имя и фамилию


* **Результат**

    Имя и фамилия клиента



* **Тип результата**

    String



#### withdraw(amount, type)
Вывод средств со счёта, в зависимости от типа счёта уменьшает значение свойства balance указанного счёта
на определённую сумму. Если у клиента недостаточно средств, взимается комиссия в размере 5$ со счёта


* **Параметры**

    
    * **amount** (*Integer*) – Сумма пополнения


    * **type** (*String*) – Тип счёта (текущий/сберегательный)



* **Результат**

    Изменённое значение баланса счёта



* **Тип результата**

    Integer



#### yield_interest(type)
Начисляет проценты по ставке в соответствии с типом банковского счёта, если баланс счёта положительный.
Если баланс счёта отрицательный, то выводит «Not interested».


* **Параметры**

    **type** (*String*) – Тип банковского счёта (текущий/сберегательный)



* **Результат**

    Баланс после начисления процентов



* **Тип результата**

    Integer

## Результаты тестирования

<p align="center"><img src="https://github.com/Torusaynim/Mirea-TiVPO/blob/master/assets/images/BankTesting.png"></p>
