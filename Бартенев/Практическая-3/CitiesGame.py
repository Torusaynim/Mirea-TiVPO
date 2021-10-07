import time
from inputimeout import inputimeout, TimeoutOccurred


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
        self.start_time = 0

    def next_turn(self, turn_time):
        self.turn += 1
        self.turn_times.append(turn_time)
        return self.turn

    def get_turn_time(self):
        turn_time = round(time.perf_counter() - self.start_time, 1)
        self.start_time = time.perf_counter()
        return turn_time

    def start_stopwatch(self):
        self.start_time = time.perf_counter()

    @property
    def turn_time(self):
        return 10 + self.turn / 10

    @property
    def average_turn_times(self):
        sum_time = []
        n = []
        avg_times = []
        for i in range(self.players):
            sum_time.append(0)
            n.append(0)
        for i in range(0, len(self.turn_times)):
            sum_time[i % self.players] += self.turn_times[i]
            n[i % self.players] += 1
        for i in range(0, self.players):
            if n[i] == 0:
                avg_times.append(0)
            else:
                avg_times.append(round(sum_time[i] / n[i], 1))
        return avg_times


class Game:
    def __init__(self, players):
        self.dict = CitiesDict()
        self.watch = Watch(players)
        self.players = players
        self.currentPlayer = 0
        self.lastChar = ''

    def check_turn(self, city):
        if self.dict.is_city(city):
            if self.lastChar == '' or self.lastChar == city[0].upper():
                if self.dict.is_available(city):
                    self.make_turn(city)
                    if __name__ == '__main__':
                        print('Принято')
                    return 1
                else:
                    if __name__ == '__main__':
                        print('Этот город уже называли')
                    return 0
            else:
                if __name__ == '__main__':
                    print('Начинается на неправильную букву')
                return -1
        else:
            if __name__ == '__main__':
                print('Это не город')
            return -2

    def make_turn(self, city):
        self.dict.select_city(city)
        self.lastChar = self.dict.get_next_char(city)
        self.currentPlayer = (self.currentPlayer + 1) % self.players
        turn_time = self.watch.get_turn_time()
        self.watch.next_turn(turn_time)
        return self.lastChar

    def get_results(self):
        winner = (self.currentPlayer - 1) % self.players + 1
        avg_times = self.watch.average_turn_times
        if __name__ == '__main__':
            if self.watch.turn != 0:
                print('Победил игрок %s' % winner)
            else:
                print('Ничья')
            print('Среднее время ходов:')
            for i in range(len(avg_times)):
                print('  Игрок %s: %s секунд' % (i + 1, avg_times[i]))
        return [winner, *avg_times]

    def start_game(self):
        timer = self.watch.turn_time
        while True:
            player = self.currentPlayer + 1
            try:
                answer_time = time.perf_counter()
                city = inputimeout(prompt='Игрок %s, введите город: ' % player, timeout=timer)
                answer_time = round(time.perf_counter() - answer_time, 1)
                timer -= answer_time
            except TimeoutOccurred:
                if __name__ == '__main__':
                    print('Время вышло')
                self.watch.turn_times.append(self.watch.turn_time)
                break
            if self.check_turn(city) == 1:
                timer = self.watch.turn_time
            if __name__ == '__main__':
                print()
        if __name__ == '__main__':
            print()
        self.get_results()


if __name__ == '__main__':
    players = int(input('Введите количество игроков: '))
    game = Game(players)
    game.start_game()
