class User:
    def __init__(self, name, email):
        self.name = name
        self.email = email
        self.balance = 0
    def make_deposit(self, amount):
        self.balance += amount
        return self
    def make_withdrawal(self, amount):
        self.balance -= amount
        return self
    def display_balance(self):
        print(self.balance)
        return self
    def transfer(self, amount):
        self.balance -= amount
        paul.balance += amount
        return self
    def identity(self):
        print(self.name)
        print(self.email)
        return self


todd = User("Todd", "toddaulwurm@yahoo.com")
nich = User("Nich", "nichaulwurm@yahoo.com")
paul = User("Paul", "paulaulwurm@yahoo.com")

todd.identity().make_deposit(100).make_deposit(200).make_deposit(300).make_withdrawal(50).display_balance()

nich.identity().make_deposit(20).make_deposit(200).make_withdrawal(3).make_withdrawal(100).display_balance()

paul.identity().make_deposit(1000).make_withdrawal(400).make_withdrawal(400).make_withdrawal(400).display_balance()

nich.identity().transfer(200).display_balance()

paul.identity().display_balance()

