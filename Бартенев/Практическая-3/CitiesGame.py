class CitiesDict:
    def __init__(self):
        self.cities = {}
        with open("cities.txt", "r", encoding='utf-8') as read_file:
            for city in read_file:
                self.cities[city[:-1]] = True

    def is_city(self, city):
        return city in self.cities

    def is_available(self, city):
        if self.is_city(city):
            return self.cities.get(city)
        else:
            return False

    def select_city(self, city):
        if self.is_available(city):
            self.cities[city] = False
            return True
        else:
            return False
