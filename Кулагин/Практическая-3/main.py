import unittest


class UserFriendlyInterface:
    def __init__(self, players=2, size=3):
        self.size = size
        self.players = players
        self.game = None

    def start_game(self):
        self.game = Tictac(self.players, self.size)
        return self

    def get_help_board(self):
        board = ""
        for i in range(1, self.size*self.size+1):
            if i % self.size == 1:
                board += ("\n| ")
            board += (str(i).rjust(2) + " | ")
        return board

    def move(self, x, game):
        coord = int(str(x), self.size)
        game.move(tuple([int(i) for i in coord.split()]))


class Tictac:
    ST_OK = 0  # Игра не завершена
    ST_END = 1  # Игра завершена

    MV_OK = 0  # Корректный ход
    MV_BAD = 1  # Некорректный ход, выход за границы или не пустая клетка
    MV_GAMEOVER = 2

    def __init__(self, players=2, size=3):
        self.size = size
        self.players = players
        self.current_player = 0
        self.empty = set([(i % size, i // size) for i in range(size * size)])
        self.moves = [set([]) for player in range(players)]
        self.state = Tictac.ST_OK
        self.winner = None

    def move(self, cell):
        # Проверить, что игра не завершена
        if self.state != Tictac.ST_OK:
            return Tictac.MV_GAMEOVER

        # Проверить, что ячейка пуста
        if cell not in self.empty:
            return Tictac.MV_BAD

        # Переместить ячейку из пустого набора в набор ходов конкретного игрока
        self.empty.remove(cell)
        self.moves[self.current_player].add(cell)

        # Проверяет победителя и завершает игру
        if self.check_winner(self.current_player):
            self.state = Tictac.ST_END
            self.winner = self.current_player
            # Завершить ход
            return Tictac.MV_OK

        # Если нет победителя, проверяем ничью
        if not self.empty:
            # Это последний ход
            self.state = Tictac.ST_END
            return Tictac.MV_OK

        # Переключиться на следующего игрока
        self.current_player = self.next_player(self.current_player)

        return Tictac.MV_OK

    def next_player(self, player):
        return (player + 1) % self.players

    def check_winner(self, player):
        rows = [0] * self.size
        cols = [0] * self.size
        diag1 = 0
        diag2 = 0

        for move in self.moves[player]:
            rows[move[1]] += 1
            cols[move[0]] += 1
            if move[0] == move[1]:
                diag1 += 1
            if move[0] + move[1] == self.size - 1:
                diag2 += 1

        for row in rows:
            if row == self.size:
                return True

        for col in cols:
            if col == self.size:
                return True

        if diag1 == self.size or diag2 == self.size:
            return True

        return False

    def sprint_result(self):
        result = []
        if self.state != Tictac.ST_OK:
            if self.winner is None:
                result.append("Result: Draw")
            else:
                result.append("Result: Winner player " + str(self.winner))
        return result

    def sprint_board(self):
        result = []
        for col in range(self.size):
            row_chars = []
            for row in range(self.size):
                cell_char = " "
                for player in range(self.players):
                    if (col, row) in self.moves[player]:
                        cell_char = str(player)
                row_chars.append(cell_char)
            result.append("|".join(row_chars))
        return result


class TictacTests(unittest.TestCase):

    def test_game_start_checks(self):
        # Начать новую игру
        t = Tictac()

        # Проверяет, что игровое поле 3х3 по умолчанию
        self.assertEqual(t.size, 3)
        # Проверяет, что в игре участвуют два игрока по умолчанию
        self.assertEqual(t.players, 2)
        # Проверить, что первый игрок - игрок 0
        self.assertEqual(t.current_player, 0)
        # Проверить, что все ячейки (3х3) пусты
        self.assertEqual(len(t.empty), 9)
        # Проверить, что ячейка (2, 2) пуста
        self.assertTrue((2, 2) in t.empty)
        # Проверить, что игроки ещё не делали ни одного хода
        self.assertEqual(t.moves, [set([]), set([])])
        # Проверить, что игра не завершена
        self.assertEqual(t.state, Tictac.ST_OK)
        # Проверить, что победитель отсутствует (т.е. это ничья)
        self.assertEqual(t.winner, None)

    def test_make_a_move(self):
        # Начать новую игру
        t = Tictac()
        # Первый ход, ячейка (0, 0)
        cell = (0, 0)

        # Проверить, что результат хода успешен
        self.assertEqual(t.move(cell), Tictac.MV_OK)

        # Проверить, что эта ячейка больше не пуста
        self.assertTrue(cell not in t.empty)
        # Проверить, что ячейка находится в наборе ходов игрока 0
        self.assertTrue(cell in t.moves[0])
        # Проверить, что текущий игрок - игрок 1
        self.assertEqual(t.current_player, 1)
        # Проверить, что результат хода в ту же ячейку вернёт ошибку
        self.assertEqual(t.move(cell), Tictac.MV_BAD)

    def test_next_player_helping_function(self):
        # Начать новую игру с тремя игроками
        t = Tictac(players=3)

        # Проверить, что следующий после игрока 0 - игрок 1
        self.assertEqual(t.next_player(0), 1)
        # Проверить, что следующий после игрока 2 - игрок 0
        self.assertEqual(t.next_player(2), 0)

    def test_winning_move(self):
        # Начать новую игру
        t = Tictac()
        # Добавить два хода для игрока 1
        t.moves[1] = {(0, 0), (0, 1)}
        # Установить игрока 1 текущим
        t.current_player = 1
        # Выполнить победный ход в ячейку (0, 2)
        t.move((0, 2))

        # Проверить, что игра заканчивается после данного хода
        self.assertEqual(t.state, Tictac.ST_END)
        # Проверить, что игрок 1 является победителем
        self.assertEqual(t.winner, 1)
        # Проверить, что нельзя сделать ход после завершения игры
        self.assertEqual(t.move((1, 2)), Tictac.MV_GAMEOVER)

    def test_winner_helping_function(self):
        # Начать новую игру
        t = Tictac()

        # Проверить, что игрок 1 не является победителем в начале игры
        self.assertFalse(t.check_winner(1))

        # Проверить, что 3 ячейки в ряд приведут к победе
        t.moves[1] = {(0, 0), (1, 0), (2, 0)}
        self.assertTrue(t.check_winner(1))

        # Проверить, что 3 ячейки в столбик приведут к победе
        t.moves[1] = {(1, 0), (1, 1), (1, 2)}
        self.assertTrue(t.check_winner(1))

        # Проверить, что 3 ячейки на главной диагонали приведут к побде
        t.moves[1] = {(0, 0), (1, 1), (2, 2)}
        self.assertTrue(t.check_winner(1))

        # Проверить, что 3 ячейки на побочной диагонали приведут к победе
        t.moves[1] = {(2, 0), (1, 1), (0, 2)}
        self.assertTrue(t.check_winner(1))

    def test_draw_move(self):
        # Начать новую игру
        t = Tictac()
        # Оставить только одну пустую ячейку
        t.empty = {(0, 0)}
        # Сделать ход в пустую ячейку
        t.move((0, 0))

        # Проверить, что игра заканчивается после этого хода
        self.assertEqual(t.state, Tictac.ST_END)
        # Проверить, что победитель отсутствует (идентификатор ничьи)
        self.assertEqual(t.winner, None)

    def test_sprint_helping_functions(self):
        # Начать новую игру
        t = Tictac()

        # Проверить, что строка с результатом незавершённой игры пуста
        self.assertEqual(t.sprint_result(), [])
        # Проверить, что результат завершённой игры без победителя - Ничья
        t.state = Tictac.ST_END
        self.assertEqual(t.sprint_result(), ["Result: Draw"])
        # Проверить результат завершённой игры, когда есть победитель
        t.winner = 1
        self.assertEqual(t.sprint_result(), ["Result: Winner player 1"])

        # Напечатать пустое игровое поле
        self.assertEqual(t.sprint_board(), [" | | ", " | | ", " | | "])
        # Напечатать непустое игровок поле
        t.moves = [set([(0, 0)]), set([(1, 1)])]
        self.assertEqual(t.sprint_board(), ["0| | ", " |1| ", " | | "])

    def test_play_a_random_game(self):
        t = Tictac(size=4, players=2)
        while t.state == Tictac.ST_OK:
            print()
            t.move(list(t.empty)[90 % len(t.empty)])
            print("\n".join(t.sprint_board()))
        print("\n".join(t.sprint_result()))


unittest.main(argv=[" "])
