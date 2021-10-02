from pizza import VeganPizza, CarnivoraPizza, PepperoniPizza, HawaiianPizza, Client, Order
import pytest


@pytest.fixture
def vegan_pizza():
    """
    Создаёт вегетарианскую пиццу на основе класса VeganPizza
    """
    return VeganPizza('vegan', 'small')


@pytest.fixture
def carnivora_pizza():
    """
    Создаёт мясную пиццу на основе класса CarnivoraPizza
    """
    return CarnivoraPizza('carnivora', 'large')


@pytest.fixture
def first_client():
    """
    Создаёт клиента на основе класса Client, включает в себя бонусную карту пиццерии
    """
    return Client('John Wick', 'Bucharest')


@pytest.fixture
def second_client():
    """
    Создаёт клиента на основе класса Client, без бонусной карты пиццерии
    """
    return Client('John Doe', 'Pisoni', False)


@pytest.fixture
def order_one(first_client, vegan_pizza, carnivora_pizza):
    """
    Создаёт заказ на основе объектов клиента и продуктов (вегетарианская пицца, мясная пицца)
    """
    return Order(client=first_client, products=[vegan_pizza, carnivora_pizza])


def test_vegan_price(vegan_pizza):
    """
    Создаёт вегетарианскую пиццу и проверяет свойство price (цена)
    """
    assert vegan_pizza.price == 630


def test_carnivora_price(carnivora_pizza):
    """
    Создаёт мясную пиццу и проверяет свойство price (цена)
    """
    assert carnivora_pizza.price == 1575


def test_first_client_address(first_client):
    """
    Создаёт клиента с бонусной картой и проверяет его свойства (address, name)
    """
    assert first_client.address == 'Bucharest'
    assert first_client.name == 'John Wick'


def test_second_client_name(second_client):
    """
    Создаёт клиента без бонусной карты и проверяет его свойства (address, name)
    """
    assert second_client.name == 'John Doe'
    assert second_client.address == 'Pisoni'


def test_order_total_price_with_card(order_one):
    """
    Создаёт заказ для клиента с бонусной картой и проверяет свойство total_price (полная стоимость заказа)
    """
    assert order_one.total_price == 1984.5


def test_order_total_price_no_card(second_client, vegan_pizza, carnivora_pizza):
    """
    Создаёт заказ для клиента без бонусной карты и проверяет свойство total_price (полная стоимость заказа)
    """
    pepperoni_pizza = PepperoniPizza('pepperoni', 'small')
    hawaiian_pizza = HawaiianPizza('hawaiian', 'medium')
    second_order = Order(client=second_client, products=[pepperoni_pizza, carnivora_pizza, vegan_pizza, hawaiian_pizza])
    assert second_order.total_price == 4305


def test_order_invoice(order_one):
    """
    Создаёт заказ и проверяет свойство invoice (строка в виде таблицы со всей информацией о заказе)
    """
    assert '1984.5' in order_one.invoice
    assert 'Bucharest' in order_one.invoice
    assert 'vegan' in order_one.invoice


def test_client_attributes(order_one):
    """
    Создаёт заказ и проверяет свойства (address, name) клиента, которому принадлежит этот заказ
    """
    assert order_one.client.address == "Bucharest"
    assert order_one.client.name == "John Wick"


def test_pizza_attributes(order_one):
    """
    Создаёт заказ и проверяет свойства объектов класса Pizza
    """
    assert order_one.products[1].size == "large"
    assert order_one.products[1].ingredients == ['tomato_sauce', 'cheese', 'chicken', 'parmesan', 'spinach']
    assert order_one.products[1].price == 1575
