class BankAccount:
    def __init__(self, balance, int_rate):
        self.balance = balance
        self.int_rate = int_rate

    @staticmethod                                                    
    def can_withdraw(balance,amount):
        if (balance - amount) < 0:
            return False
        else:
            return True

    @staticmethod
    def is_pos(balance):
        if balance < 0:
            return False
        else:
            return True


class User:
    bank = "Bank of Dojo"
    def __init__(self, first_name, last_name, age):
        self.first_name = first_name
        self.last_name = last_name
        self.age = age
        self.user_checking = BankAccount(0, 0.2)
        self.user_savings = BankAccount(0, 0.2)

    def identify(self):
        print(self.first_name +" "+ self.last_name)
        return self

    def display_account_info(self):
        print(f"Checking Balance: ${self.user_checking.balance} Savings Balance:${self.user_savings.balance}")
        return self

    def deposit(self, amount, type):
        if type == "checking":                                                       
            self.user_checking.balance += amount
            return self
        elif type == "savings":
            self.user_savings.balance += amount
            return self

    def withdraw(self, amount, type):
        if type == "checking":
            if BankAccount.can_withdraw(self.user_checking.balance,amount): 
                self.user_checking.balance -= amount
                return self
            else: 
                print("Insufficient Funds: Charging a $5 Fee")
                self.user_checking.balance -= 5
                return self
        elif type == "savings":
            if BankAccount.can_withdraw(self.user_savings.balance,amount):                  
                self.user_savings.balance -= amount
                return self
            else: 
                print("Insufficient Funds: Charging a $5 Fee")
                self.user_savings.balance -= 5
                return self

    def yield_interest(self, type):
        if type == "checking":
            if BankAccount.is_pos(self.user_checking.balance):
                self.user_checking.balance= (self.user_checking.balance*self.user_checking.int_rate)+self.user_checking.balance
                return self
            else:
                print("Not interested")
                return self
        elif type == "savings":
            if BankAccount.is_pos(self.user_savings.balance):
                self.user_savings.balance= (self.user_savings.balance*self.user_savings.int_rate)+self.user_savings.balance
            else:
                print("Not interested")
            return self

todd = User("Todd", "Aulwurm", 27)
# todd = BankAccount(100,0.04)
nich = User("Nich", "Aulwurm", 31)
# nich = BankAccount(200,0.04)

todd.identify().deposit(100, "savings").deposit(200, "checking").deposit(300, "checking").withdraw(50, "checking").yield_interest("checking").display_account_info()
nich.identify().deposit(20, "savings").deposit(200, "checking").withdraw(20, "checking").withdraw(80, "checking").withdraw(10, "checking").withdraw(5, "checking").yield_interest("checking").display_account_info()


