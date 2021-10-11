import time
import pytest
from CitiesGame import CitiesDict, Watch, Game


@pytest.fixture
def cities_dict():
    """

    """
    return CitiesDict()


@pytest.fixture
def watch():
    """

    """
    return Watch(2)


@pytest.fixture
def game():
    """

    """
    return Game(2)


def test_is_city(cities_dict):
    """

    """
    assert cities_dict.is_city('Архангельск') == True
    assert cities_dict.is_city('Москва') == True
    assert cities_dict.is_city('Варшава') == True
    assert cities_dict.is_city('Стол') == False
    assert cities_dict.is_city('Стул') == False


def test_is_available(cities_dict):
    """

    """
    assert cities_dict.select_city('Архангельск') == True
    cities_dict.select_city('Архангельск')
    assert cities_dict.select_city('архангельск') == False
    assert cities_dict.select_city('Москва') == True
    assert cities_dict.select_city('Стол') == False
    assert cities_dict.select_city('Стул') == False


def test_select_city(cities_dict):
    """

    """
    assert cities_dict.select_city('Архангельск') == True
    assert cities_dict.select_city('архангельск') == False
    assert cities_dict.select_city('Москва') == True
    assert cities_dict.select_city('Санкт-Петербург') == True
    assert cities_dict.select_city('Москва') == False


def test_get_next_char(cities_dict):
    """

    """
    assert cities_dict.get_next_char('Архангельск') == 'К'
    assert cities_dict.get_next_char('Москва') == 'А'
    assert cities_dict.get_next_char('Чаны') == 'Н'
    assert cities_dict.get_next_char('Пермь') == 'М'
    assert cities_dict.get_next_char('Калуга') == 'А'


def test_next_turn(watch):
    """

    """
    assert watch.next_turn(5) == 1
    assert watch.next_turn(5) == 2
    assert watch.next_turn(5) == 3
    assert watch.next_turn(5) == 4
    assert watch.next_turn(5) == 5


def test_get_turn_time(watch):
    """

    """
    watch.start_stopwatch()
    assert watch.get_turn_time() == 0
    time.sleep(1)
    assert watch.get_turn_time() == 1
    time.sleep(0.5)
    assert watch.get_turn_time() == 0.5
    time.sleep(1)
    assert watch.get_turn_time() == 1
    assert watch.get_turn_time() == 0


def test_turn_time(watch):
    """

    """
    assert watch.turn_time == 10
    watch.next_turn(5)
    assert watch.turn_time == 10.1
    watch.next_turn(5)
    assert watch.turn_time == 10.2
    watch.next_turn(5)
    assert watch.turn_time == 10.3
    watch.next_turn(5)
    assert watch.turn_time == 10.4


def test_average_turn_time(watch):
    """

    """
    assert watch.average_turn_times == [0, 0]
    watch.next_turn(5)
    assert watch.average_turn_times == [5, 0]
    watch.next_turn(6)
    assert watch.average_turn_times == [5, 6]
    watch.next_turn(7)
    assert watch.average_turn_times == [6, 6]
    watch.next_turn(8)
    assert watch.average_turn_times == [6, 7]


def test_make_turn(game):
    """

    """
    assert game.make_turn('Кабардинск') == 'К'
    assert game.make_turn('Калуга') == 'А'
    assert game.make_turn('Анталия') == 'Я'
    assert game.make_turn('Якутск') == 'К'
    assert game.make_turn('Керчь') == 'Ч'


def test_check_turn(game):
    """

    """
    assert game.check_turn('Стул') == -2
    assert game.check_turn('Чаны') == 1
    assert game.check_turn('Нальчик') == 1
    assert game.check_turn('Кукла') == -2
    assert game.check_turn('Казань') == 1
    assert game.check_turn('нальчик') == 0
    assert game.check_turn('Москва') == -1


def test_current_player(game):
    """

    """
    assert game.currentPlayer == 0
    game.make_turn('Кабардинск')
    assert game.currentPlayer == 1
    game.make_turn('Калуга')
    assert game.currentPlayer == 0
    game.make_turn('Анталия')
    assert game.currentPlayer == 1
    game.make_turn('Якутск')
    assert game.currentPlayer == 0
    game.make_turn('Керчь')
    assert game.currentPlayer == 1


def test_get_results(game):
    """

    """
    game.watch.start_stopwatch()
    time.sleep(0.1)
    game.make_turn('Кабардинск')
    time.sleep(0.2)
    game.make_turn('Калуга')
    time.sleep(0.1)
    game.make_turn('Анталия')
    time.sleep(0.2)
    game.make_turn('Якутск')
    game.kickedPlayers.append(1)
    assert game.get_results(False) == [1, 0.1, 0.2]
