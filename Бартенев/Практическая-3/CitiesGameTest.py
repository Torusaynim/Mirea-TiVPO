from CitiesGame import CitiesDict, Watch
import pytest


@pytest.fixture
def cities_dict():
    """

    """
    return CitiesDict()


@pytest.fixture
def watch():
    """

    """
    return Watch()


def test_is_city(cities_dict):
    """

    """
    assert cities_dict.is_city("Архангельск") == True
    assert cities_dict.is_city("Москва") == True
    assert cities_dict.is_city("Варшава") == True
    assert cities_dict.is_city("Стол") == False
    assert cities_dict.is_city("Стул") == False


def test_is_available(cities_dict):
    """

    """
    assert cities_dict.select_city("Архангельск") == True
    cities_dict.select_city("Архангельск")
    assert cities_dict.select_city("Архангельск") == False
    assert cities_dict.select_city("Москва") == True
    assert cities_dict.select_city("Стол") == False
    assert cities_dict.select_city("Стул") == False


def test_select_city(cities_dict):
    """

    """
    assert cities_dict.select_city("Архангельск") == True
    assert cities_dict.select_city("Архангельск") == False
    assert cities_dict.select_city("Москва") == True
    assert cities_dict.select_city("Стол") == False
    assert cities_dict.select_city("Стул") == False


def test_get_next_char(cities_dict):
    """

    """
    assert cities_dict.get_next_char("Архангельск") == "К"
    assert cities_dict.get_next_char("Москва") == "А"
    assert cities_dict.get_next_char("Чаны") == "Н"
    assert cities_dict.get_next_char("Пермь") == "М"
    assert cities_dict.get_next_char("Калуга") == "А"


def test_next_turn(watch):
    """

    """
    assert watch.next_turn() == 1
    assert watch.next_turn() == 2
    assert watch.next_turn() == 3
    assert watch.next_turn() == 4
    assert watch.next_turn() == 5


def test_turn_time(watch):
    """

    """
    assert watch.turn_time == 10
    watch.next_turn()
    assert watch.turn_time == 10.1
    watch.next_turn()
    assert watch.turn_time == 10.2
    watch.next_turn()
    assert watch.turn_time == 10.3
    watch.next_turn()
    assert watch.turn_time == 10.4


def test_average_turn_time(watch):
    """

    """
    assert watch.average_turn_time == -1
    watch.next_turn()
    assert watch.average_turn_time == 5
    watch.next_turn(6)
    assert watch.average_turn_time == 5.5
    watch.next_turn(7)
    assert watch.average_turn_time == 6
    watch.next_turn(4)
    assert watch.average_turn_time == 5.5
