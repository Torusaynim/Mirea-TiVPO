class BankAccount:
    """
    Создает банковский аккаунт с атрибутами: баланс, процентная ставка
    """
    def __init__(self, balance, int_rate):
        self.balance = balance
        self.int_rate = int_rate

    @staticmethod
    def can_withdraw(balance, amount):
        """
        Определяет возможность вывода средств со счёта

        :param balance: Баланс банковского счёта
        :type balance: Integer

        :param amount: Сумма перевода
        :type amount: Integer

        :return: True, если можно вывести средства, иначе Else
        :rtype: Boolean
        """
        if (balance - amount) < 0:
            return False
        else:
            return True

    @staticmethod
    def is_pos(balance):
        """
        Проверяет, является ли баланс банковского счёта положительным

        :param balance: Баланс банковского счёта
        :type balance: Integer

        :return: True, если баланс положительный, иначе Else
        :rtype: Boolean
        """
        if balance <= 0:
            return False
        else:
            return True


class User:
    """
    Создаёт клиента банка с атрибутами: имя, фамилия, возраст

    :param first_name: Имя клиента
    :type first_name: String
    :param last_name: Фамилия клиента
    :type last_name: String
    :param age: Возраст клиента
    :type age: Integer
    """
    bank = "Bank of Dojo"

    def __init__(self, first_name, last_name, age):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age
        self.user_checking = BankAccount(10, 0.2)
        self.user_savings = BankAccount(10, 0.4)

    def identify(self):
        """
        Отображает информацию о пользователе: имя и фамилию

        :return: Имя и фамилия клиента
        :rtype: String
        """
        print(self.first_name + " " + self.last_name)
        return self.first_name + " " + self.last_name

    def display_account_info(self):
        """
        Отображает информацию о балансе на счетах: баланс текущего счёта и сберегательного счёта

        :return: Баланс счетов
        :rtype: String
        """
        print(f"Checking Balance: ${self.user_checking.balance} Savings Balance:${self.user_savings.balance}")
        return f"Checking Balance: ${self.user_checking.balance} Savings Balance:${self.user_savings.balance}"

    def deposit(self, amount, type):
        """
        Пополнение счета: проверяет тип счёта и увеличивает значение свойства balance нужного счёта
        на определённую сумму

        :param amount: Сумма пополнения
        :type amount: Integer
        :param type: Тип счёта (текущий/сберегательный)
        :type type: String

        :return: Изменённое значение баланса счёта
        :rtype: Integer
        """
        if type == "checking":
            self.user_checking.balance += amount
            return self.user_checking.balance
        elif type == "savings":
            self.user_savings.balance += amount
            return self.user_savings.balance

    def withdraw(self, amount, type):
        """
        Вывод средств со счёта, в зависимости от типа счёта уменьшает значение свойства balance указанного счёта
        на определённую сумму. Если у клиента недостаточно средств, взимается комиссия в размере 5$ со счёта

        :param amount: Сумма пополнения
        :type amount: Integer
        :param type: Тип счёта (текущий/сберегательный)
        :type type: String
        :return: Изменённое значение баланса счёта
        :rtype: Integer
        """
        if type == "checking":
            if BankAccount.can_withdraw(self.user_checking.balance, amount):
                self.user_checking.balance -= amount
                return self.user_checking.balance
            else:
                print("Insufficient Funds: Charging a $5 Fee")
                self.user_checking.balance -= 5
                return self.user_checking.balance
        elif type == "savings":
            if BankAccount.can_withdraw(self.user_savings.balance, amount):
                self.user_savings.balance -= amount
                return self.user_savings.balance
            else:
                print("Insufficient Funds: Charging a $5 Fee")
                self.user_savings.balance -= 5
                return self.user_savings.balance

    def yield_interest(self, type):
        """
        Начисляет проценты по ставке в соответствии с типом банковского счёта, если баланс счёта положительный.
        Если баланс счёта отрицательный, то выводит "Not interested".

        :param type: Тип банковского счёта (текущий/сберегательный)
        :type type: String
        :return: Баланс после начисления процентов
        :rtype: Integer
        """
        if type == "checking":
            if BankAccount.is_pos(self.user_checking.balance):
                self.user_checking.balance = (self.user_checking.balance*self.user_checking.int_rate)+self.user_checking.balance
                return self.user_checking.balance
            else:
                print("Not interested")
                return self.user_checking.balance
        elif type == "savings":
            if BankAccount.is_pos(self.user_savings.balance):
                self.user_savings.balance = (self.user_savings.balance*self.user_savings.int_rate)+self.user_savings.balance
            else:
                print("Not interested")
            return self.user_savings.balance
        
