from CitiesGame import CitiesDict
import pytest


@pytest.fixture
def cities_dict():
    """

    """
    return CitiesDict()


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
