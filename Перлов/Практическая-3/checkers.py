from tkinter import *
from math import fabs


class Field:
    def __init__(self, field=None):
        self.field = field

    def set_field(self, field):
        self.field = field

    @staticmethod
    def new_game():  # Start new game
        global field
        field = [[0, 3, 0, 3, 0, 3, 0, 3],
                 [3, 0, 3, 0, 3, 0, 3, 0],
                 [0, 3, 0, 3, 0, 3, 0, 3],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [0, 0, 0, 0, 0, 0, 0, 0],
                 [1, 0, 1, 0, 1, 0, 1, 0],
                 [0, 1, 0, 1, 0, 1, 0, 1],
                 [1, 0, 1, 0, 1, 0, 1, 0]]

    @staticmethod
    def get_images():  # Load images of draughts
        global draughts
        i1 = PhotoImage(file="White.png")
        i2 = PhotoImage(file="WhiteQ.png")
        i3 = PhotoImage(file="Red.png")
        i4 = PhotoImage(file="RedQ.png")
        draughts = [0, i1, i2, i3, i4]


class Draw:

    @staticmethod
    def draw_field(x_pos_1, y_pos_1, x_pos_2, y_pos_2):  # Drawing playing field
        global draughts
        global field
        global frameR, frameG
        k = 100
        x = 0
        table.delete('all')
        frameR = table.create_rectangle(-5, -5, -5, -5, outline="red", width=5)
        frameG = table.create_rectangle(-5, -5, -5, -5, outline="green", width=5)

        while x < 8 * k:  # Draw field
            y = 1 * k
            while y < 8 * k:
                table.create_rectangle(x, y, x + k, y + k, fill="black")
                y += 2 * k
            x += 2 * k
        x = 1 * k
        while x < 8 * k:  # Draw field
            y = 0
            while y < 8 * k:
                table.create_rectangle(x, y, x + k, y + k, fill="black")
                y += 2 * k
            x += 2 * k

        for y in range(8):  # Draw draughts
            for x in range(8):
                z = field[y][x]
                if z:
                    if (x_pos_1, y_pos_1) != (x, y):
                        table.create_image(x * k, y * k, anchor=NW, image=draughts[z])
        # Active draught
        z = field[y_pos_1][x_pos_1]
        if z:
            table.create_image(x_pos_1 * k, y_pos_1 * k, anchor=NW, image=draughts[z], tag='ani')
        kx = 1 if x_pos_1 < x_pos_2 else -1
        ky = 1 if y_pos_1 < y_pos_2 else -1
        for i in range(abs(x_pos_1 - x_pos_2)):  # Move animation
            for ii in range(33):
                table.move('ani', 0.03 * k * kx, 0.03 * k * ky)
                table.update()

    @staticmethod
    def pos_hover(event):  # Green light up of hovered cell
        x, y = event.x // 100, event.y // 100
        table.coords(frameG, x * 100, y * 100, x * 100 + 100, y * 100 + 100)  # Create green frame

    @staticmethod
    def pos_click(event):  # Red light up of picked cell
        global pos1_x, pos1_y, pos2_x, pos2_y
        global f_turn
        x, y = event.x // 100, event.y // 100
        if field[y][x] == 1 + f_turn * 2 or field[y][x] == 2 + f_turn * 2:  # Draught belongs to player
            table.coords(frameR, x * 100, y * 100, x * 100 + 100, y * 100 + 100)  # Create red frame
            pos1_x, pos1_y = x, y
        else:
            if pos1_x != -1:  # Draught is picked
                pos2_x, pos2_y = x, y
                Turn.turn()  # Make a turn
                pos1_x = -1  # Cell not chosen
                table.coords(frameR, -5, -5, -5, -5)  # рамка вне поля


class Turn:
    def __init__(self, pos1_y, pos1_x, pos2_y, pos2_x, field):
        self.pos1_y = pos1_y
        self.pos1_x = pos1_x
        self.pos2_y = pos2_y
        self.pos2_x = pos2_x
        self.field = field

    def make_move(self):
        if self.field[self.pos1_y][self.pos1_x] > 2:
            targets = [1, 2]
        else:
            targets = [3, 4]
        checker_x = self.pos1_x
        checker_y = self.pos1_y
        if self.pos2_y >= self.pos1_y:
            direction_y = 1
        else:
            direction_y = -1
        if self.pos2_x >= self.pos1_x:
            direction_x = 1
        else:
            direction_x = -1
        # direction variables
        if self.field[self.pos1_y][self.pos1_x] % 2:
            if fabs(self.pos2_x - self.pos1_x) == fabs(self.pos2_y - self.pos1_y) and \
                    fabs(self.pos2_y - self.pos1_y) == 2:  # Length 2
                if self.field[self.pos2_y][self.pos2_x] == 0 and \
                        self.field[self.pos1_y+direction_y][self.pos1_x+direction_x] in targets:
                    # White side Queen
                    if self.pos2_y == 0 and self.field[self.pos1_y][self.pos1_x] == 1:
                        field[self.pos1_y][self.pos1_x] = 2
                    # Red side Queen
                    if self.pos2_y == 7 and self.field[self.pos1_y][self.pos1_x] == 3:
                        self.field[self.pos1_y][self.pos1_x] = 4
                    # Moving
                    self.field[self.pos2_y][self.pos2_x] = self.field[self.pos1_y][self.pos1_x]
                    self.field[self.pos1_y][self.pos1_x] = 0
                    self.field[self.pos1_y+direction_y][self.pos1_x+direction_x] = 0
            elif fabs(self.pos2_x - self.pos1_x) == fabs(self.pos2_y - self.pos1_y) and \
                    fabs(self.pos2_y - self.pos1_y) == 1:  # Length 1
                if targets == [3, 4] and direction_y == -1 and self.field[self.pos2_y][self.pos2_x] == 0:  # Whites
                    # White side Queen
                    if self.pos2_y == 0 and self.field[self.pos1_y][self.pos1_x] == 1:
                        self.field[self.pos1_y][self.pos1_x] = 2
                    # Red side Queen
                    if self.pos2_y == 7 and self.field[self.pos1_y][self.pos1_x] == 3:
                        self.field[self.pos1_y][self.pos1_x] = 4
                    # Moving
                    self.field[self.pos2_y][self.pos2_x] = self.field[self.pos1_y][self.pos1_x]
                    self.field[self.pos1_y][self.pos1_x] = 0
                elif targets == [1, 2] and direction_y == 1 and \
                        self.field[self.pos2_y][self.pos2_x] == 0:  # Reds
                    # White side Queen
                    if self.pos2_y == 0 and self.field[self.pos1_y][self.pos1_x] == 1:
                        self.field[self.pos1_y][self.pos1_x] = 2
                    # Red side Queen
                    if self.pos2_y == 7 and self.field[self.pos1_y][self.pos1_x] == 3:
                        self.field[self.pos1_y][self.pos1_x] = 4
                    # Moving
                    self.field[self.pos2_y][self.pos2_x] = self.field[self.pos1_y][self.pos1_x]
                    self.field[self.pos1_y][self.pos1_x] = 0
            # Draught
        else:
            if fabs(self.pos2_x - self.pos1_x) == fabs(self.pos2_y - self.pos1_y):
                k = 0
                while checker_y != self.pos2_y and checker_x != self.pos2_x:
                    checker_y += direction_y
                    checker_x += direction_x
                    if self.field[checker_y][checker_x] in targets:
                        k += 1
                        rem_y = checker_y
                        rem_x = checker_x
                if k <= 1:
                    # Moving
                    self.field[self.pos2_y][self.pos2_x] = self.field[self.pos1_y][self.pos1_x]
                    self.field[self.pos1_y][self.pos1_x] = 0
                    if k == 1:
                        self.field[rem_y][rem_x] = 0
                    # Removing opponent's draught
            # Queen

    @staticmethod
    def turn():
        global pos1_x, pos1_y, pos2_x, pos2_y
        global f_turn
        f_turn = not f_turn  # Turn flag change
        Turn.move(pos1_x, pos1_y, pos2_x, pos2_y)  # If everything if fine, move draught
        if field[pos1_y][pos1_x] != 0:
            f_turn = not f_turn
        table.update()

    @staticmethod
    def move(pos1_x, pos1_y, pos2_x, pos2_y):
        global field
        if field[pos1_y][pos1_x] > 2:
            targets = [1, 2]
        else:
            targets = [3, 4]
        checker_x = pos1_x
        checker_y = pos1_y
        if pos2_y >= pos1_y:
            direction_y = 1
        else:
            direction_y = -1
        if pos2_x >= pos1_x:
            direction_x = 1
        else:
            direction_x = -1
        # direction variables
        if field[pos1_y][pos1_x] % 2:
            if fabs(pos2_x - pos1_x) == fabs(pos2_y - pos1_y) and fabs(pos2_y - pos1_y) == 2:  # Length 2
                if field[pos2_y][pos2_x] == 0 and field[pos1_y+direction_y][pos1_x+direction_x] in targets:
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
                    # White side Queen
                    if pos2_y == 0 and field[pos1_y][pos1_x] == 1:
                        field[pos1_y][pos1_x] = 2
                    # Red side Queen
                    if pos2_y == 7 and field[pos1_y][pos1_x] == 3:
                        field[pos1_y][pos1_x] = 4
                    # Moving
                    field[pos2_y][pos2_x] = field[pos1_y][pos1_x]
                    field[pos1_y][pos1_x] = 0
                    field[pos1_y+direction_y][pos1_x+direction_x] = 0
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
            elif fabs(pos2_x - pos1_x) == fabs(pos2_y - pos1_y) and fabs(pos2_y - pos1_y) == 1:  # Length 1
                if targets == [3, 4] and direction_y == -1 and field[pos2_y][pos2_x] == 0:  # Whites
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
                    # White side Queen
                    if pos2_y == 0 and field[pos1_y][pos1_x] == 1:
                        field[pos1_y][pos1_x] = 2
                    # Red side Queen
                    if pos2_y == 7 and field[pos1_y][pos1_x] == 3:
                        field[pos1_y][pos1_x] = 4
                    # Moving
                    field[pos2_y][pos2_x] = field[pos1_y][pos1_x]
                    field[pos1_y][pos1_x] = 0
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
                elif targets == [1, 2] and direction_y == 1 and field[pos2_y][pos2_x] == 0:  # Reds
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
                    # White side Queen
                    if pos2_y == 0 and field[pos1_y][pos1_x] == 1:
                        field[pos1_y][pos1_x] = 2
                    # Red side Queen
                    if pos2_y == 7 and field[pos1_y][pos1_x] == 3:
                        field[pos1_y][pos1_x] = 4
                    # Moving
                    field[pos2_y][pos2_x] = field[pos1_y][pos1_x]
                    field[pos1_y][pos1_x] = 0
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
            # Draught
        else:
            if fabs(pos2_x - pos1_x) == fabs(pos2_y - pos1_y):
                k = 0
                while checker_y != pos2_y and checker_x != pos2_x:
                    checker_y += direction_y
                    checker_x += direction_x
                    if field[checker_y][checker_x] in targets:
                        k += 1
                        rem_y = checker_y
                        rem_x = checker_x
                if k <= 1:
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
                    # Moving
                    field[pos2_y][pos2_x] = field[pos1_y][pos1_x]
                    field[pos1_y][pos1_x] = 0
                    if k == 1:
                        field[rem_y][rem_x] = 0
                    # Removing opponent's draught
                    Draw.draw_field(pos1_x, pos1_y, pos2_x, pos2_y)  # Drawing game field
            # Queen


window = Tk()  # Creating window
window.title('Checkers')
table = Canvas(window, width=800, height=800, bg='#FFFFFF')
table.pack()
f_turn = False  # P1(white) starts first
Field.get_images()  # Load images
Field.new_game()  # Start NG
Draw.draw_field(-1, -1, -1, -1)  # Drawing gaming field
table.bind("<Motion>", Draw.pos_hover)  # Mouse movement
table.bind("<Button-1>", Draw.pos_click)  # Mouse click
mainloop()  # Loop
