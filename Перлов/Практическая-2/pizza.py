class Pizza:
    """
    Создает пиццу с атрибутами: название, размер, и полем для ингредиентов

    :param name: Название пиццы
    :type name: String
    :param size: Размер пиццы ( small / medium / large )
    :type size: String
    """
    def __init__(self, name, size):
        self.name = name
        self.size = size
        self.ingredients = None

    @property
    def price(self):
        """
        Рассчитывает и возвращает цену в зависимости от размера и ингредиентов

        :return: Стоимость пиццы
        :rtype: Integer
        """
        price_per_ingredient = 210
        size_price = {
            "small": 1,
            "medium": 1.2,
            "large": 1.5
        }
        return size_price[self.size] * len(self.ingredients) * price_per_ingredient


class VeganPizza(Pizza):
    """
    Создает вегетарианскую пиццу, наследуя атрибуты от класса Pizza, с атрибутами: название, размер
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'pepper', 'olives']


class CarnivoraPizza(Pizza):
    """
    Создает мясную пиццу, наследуя атрибуты от класса Pizza, с атрибутами: название, размер
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'chicken', 'parmesan', 'spinach']


class PepperoniPizza(Pizza):
    """
    Создает пиццу пепперони, наследуя атрибуты от класса Pizza, с атрибутами: название, размер
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'salami', 'habanero_pepper']


class HawaiianPizza(Pizza):
    """
    Создает гавайскую пиццу, наследуя атрибуты от класса Pizza, с атрибутами: название, размер
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'pineapple', 'cooked_ham', 'onion']


class Client:
    """
    Создает клиента с атрибутами: имя, адрес, наличие карты

    :param name: Имя клиента
    :type name: String
    :param address: Адрес доставки
    :type address: String
    :param has_card: Наличие карты
    :type has_card: Boolean
    """
    def __init__(self, name, address, has_card=True):
        self.name = name
        self.address = address
        self.has_card = has_card


class Order:
    """
    Создает заказ, включающий в себя объект Client и спискок объектов Pizza

    :param client: Объект клиента
    :type client: Client
    :param products: Список объектов заказанных пицц
    :type products: Pizza
    """
    def __init__(self, client, products):
        self.client = client
        self.products = products

    @property
    def total_price(self):
        """
        Рассчитывает и возвращает общую стоимость заказа. Если у клиента есть карта, применяется скидка 10%

        :return: Общая стоимость заказа
        :rtype: Integer
        """
        price = sum([product.price for product in self.products])
        if self.client.has_card:
            return price * 0.9
        return price

    @property
    def invoice(self):
        """
        Формирует и возвращает строку в формате таблицы, содержащую подробную информацию о заказе

        :return: Сформированный счёт заказа
        :rtype: String
        """
        result = '\n'.join([f'{product.name} - {product.price}' for product in self.products])
        result += f'\nThe total price is {self.total_price}! \nThe delivery will be in {self.client.address}!'
        return result
