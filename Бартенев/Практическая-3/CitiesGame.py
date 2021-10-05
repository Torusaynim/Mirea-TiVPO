import time


class CitiesDict:
    def __init__(self):
        self.cities = {}
        with open('cities.txt', 'r', encoding='utf-8') as read_file:
            for city in read_file:
                city = city.lower()
                self.cities[city[:-1]] = True

    def is_city(self, city):
        city = city.lower()
        return city in self.cities

    def is_available(self, city):
        city = city.lower()
        return self.cities.get(city)

    def select_city(self, city):
        city = city.lower()
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
    def __init__(self, players):
        self.players = players
        self.turn_times = []
        self.turn = 0
        self.start_time = time.perf_counter()

    def next_turn(self, turn_time):
        self.turn += 1
        self.turn_times.append(turn_time)
        return self.turn

    def get_turn_time(self):
        turn_time = round(time.perf_counter() - self.start_time, 1)
        self.start_time = time.perf_counter()
        return turn_time

    @property
    def turn_time(self):
        return 10 + self.turn / 10

    @property
    def average_turn_time(self):
        sum_time = []
        n = []
        avg_time = []
        for i in range(self.players):
            sum_time.append(0)
            n.append(0)
        for i in range(0, len(self.turn_times)):
            sum_time[i % self.players] += self.turn_times[i]
            n[i % self.players] += 1
        for i in range(0, 2):
            if n[i] == 0:
                avg_time.append(-1)
            else:
                avg_time.append(round(sum_time[i] / n[i], 1))
        return avg_time


class Game:
    def __init__(self, players):
        self.dict = CitiesDict()
        self.watch = Watch(players)
        self.players = players
        self.currentPlayer = 0
        self.lastChar = ''

    def check_turn(self, city):
        if self.dict.is_city(city):
            if self.dict.is_available(city):
                if self.lastChar == '' or self.lastChar == city[0].upper():
                    self.make_turn(city)
                    return 1
            else:
                return 0
        else:
            return -1

    def make_turn(self, city):
        self.dict.select_city(city)
        self.lastChar = self.dict.get_next_char(city)
        self.currentPlayer = (self.currentPlayer + 1) % self.players
        turn_time = self.watch.get_turn_time()
        self.watch.next_turn(turn_time)
        return self.lastChar

    def get_current_player(self):
        return self.currentPlayer
