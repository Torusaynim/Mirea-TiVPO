from BankAccount import BankAccount, User
import pytest


@pytest.fixture
def bank_account():
    """
    Создаёт банковский аккаунт с положительным балансом на основе класса BankAccount
    """
    return BankAccount(100, 0.4)


@pytest.fixture
def bank_account_neg():
    """
    Создаёт банковский аккаунт с отрицательным балансом на основе класса BankAccount
    """
    return BankAccount(-100, 0.4)


@pytest.fixture
def user():
    """
    Создаёт клиента банка на основе класса User
    """
    return User("Todd", "Aulwurm", 27)


def test_bank_account(bank_account):
    """
    Создаёт банковский аккаунт с положительным балансом и тестирует его свойства
    """
    assert bank_account.balance == 100
    assert bank_account.int_rate == 0.4


def test_bank_account_neg(bank_account_neg):
    """
    Создаёт банковский аккаунт с отрицательным балансом и тестирует его свойства
    """
    assert bank_account_neg.balance == -100
    assert bank_account_neg.int_rate == 0.4


def test_can_withdraw(bank_account, bank_account_neg):
    """
    Определяет возможность вывода средств со счёта
    """
    assert BankAccount.can_withdraw(bank_account.balance, 100) is True
    assert BankAccount.can_withdraw(bank_account.balance, 101) is False
    assert BankAccount.can_withdraw(bank_account_neg.balance, 30) is False


def test_is_pos(bank_account, bank_account_neg):
    """
    Проверяет, является ли баланс положительным
    """
    assert BankAccount.is_pos(bank_account.balance) is True
    assert BankAccount.is_pos(bank_account_neg.balance) is False


def test_user(user):
    """
    Создаёт клиента и тестирует его свойства
    """
    assert user.first_name == "Todd"
    assert user.last_name == "Aulwurm"
    assert user.age == 27
    assert user.user_checking.balance == 10
    assert user.user_checking.int_rate == 0.2
    assert user.user_savings.balance == 10
    assert user.user_savings.int_rate == 0.4


def test_identify(user):
    """
    Отображает информацию о клиенте
    """
    assert user.identify() == "Todd Aulwurm"


def test_display_account_info(user):
    """
    Отображает информацию о счетах клиента
    """
    assert user.display_account_info() == "Checking Balance: $10 Savings Balance:$10"


def test_deposit(user):
    """
    Проверяет функцию пополнения счёта
    """
    assert user.deposit(100, "checking") == 110
    assert user.deposit(100, "savings") == 110


def test_withdraw(user):
    """
    Проверяет функцию снятия денег со счёта
    """
    assert user.withdraw(4, "checking") == 6
    assert user.withdraw(100, "checking") == 1
    assert user.withdraw(3, "savings") == 7
    assert user.withdraw(100, "savings") == 2


def test_yield_interest(user):
    """
    Проверяет функцию начисления процентов
    """
    assert user.yield_interest("savings") == 14
    assert user.yield_interest("checking") == 12
    user.withdraw(14, "savings")
    user.withdraw(6, "savings")
    user.withdraw(12, "checking")
    user.withdraw(6, "checking")
    assert user.yield_interest("savings") == -5
    assert user.yield_interest("checking") == -5