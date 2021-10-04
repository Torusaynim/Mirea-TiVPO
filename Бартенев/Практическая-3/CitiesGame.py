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

    def get_next_char(self, city):
        city = city.upper()
        if city[-1] in ['Ы', 'Й', 'Ь', 'Ъ']:
            return city[-2]
        else:
            return city[-1]


class Watch:
    def __init__(self):
        self.turns_time = []
        self.turn = 0

    def next_turn(self, time=5):
        self.turn += 1
        self.turns_time.append(time)
        return self.turn

    @property
    def turn_time(self):
        return 10 + self.turn / 10

    @property
    def average_turn_time(self):
        if len(self.turns_time) != 0:
            sum_time = 0
            for turn_time in self.turns_time:
                sum_time += turn_time
            return round(sum_time / len(self.turns_time), 1)
        else:
            return -1
