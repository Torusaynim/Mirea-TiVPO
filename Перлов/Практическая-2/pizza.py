class Pizza:
    """
    Создает пиццу с атрибутами: название, размер, ингредиенты
    """
    def __init__(self, name, size):
        self.name = name
        self.size = size
        self.ingredients = None

    @property
    def price(self):
        """
        Рассчитывает цену в зависимости от размера и ингредиентов
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
    Создает веганскую пиццу, наследуя атрибуты от класса Pizza
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'pepper', 'olives']


class CarnivoraPizza(Pizza):
    """
    Создает мясную пиццу, наследуя атрибуты от класса Pizza
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'chicken', 'parmesan', 'spinach']


class PepperoniPizza(Pizza):
    """
    Создает пиццу пепперони, наследуя атрибуты от класса Pizza
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'salami', 'habanero_pepper']


class HawaiianPizza(Pizza):
    """
    Создает гавайскую пиццу, наследуя атрибуты от класса Pizza
    """
    def __init__(self, name, size):
        super().__init__(name, size)
        self.ingredients = ['tomato_sauce', 'cheese', 'pineapple', 'cooked_ham', 'onion']


class Client:
    """
    Создает клиента с атрибутами имя, адрес, наличие карты заведения (булевая)
    """
    def __init__(self, name, address, has_card=True):
        self.name = name
        self.address = address
        self.has_card = has_card


class Order:
    """
    Создает заказ на основе класса Client и продуктов (список объектов Pizza)
    """
    def __init__(self, client, products):
        self.client = client
        self.products = products

    @property
    def total_price(self):
        """
        Рассчитывает общую стоимость заказа на основе атрибутов товаров
        Если у клиента has_card, применяется скидка 10%
        """
        price = sum([product.price for product in self.products])
        if self.client.has_card:
            return price * 0.9
        return price

    @property
    def invoice(self):
        """
        Строка в формате таблицы, содержащая все товары, связанные с этим заказом,
        их цены, общая цена и информация о клиенте
        """
        result = '\n'.join([f'{product.name} - {product.price}' for product in self.products])
        result += f'\nThe total price is {self.total_price}! \nThe delivery will be in {self.client.address}!'
        return result
