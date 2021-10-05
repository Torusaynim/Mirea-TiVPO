from checkers import Field, Turn
import pytest


@pytest.fixture
def field0():
    """
    Real game field
    """
    return Field([[0, 3, 0, 3, 0, 3, 0, 3],
                  [3, 0, 3, 0, 3, 0, 3, 0],
                  [0, 3, 0, 3, 0, 3, 0, 3],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [1, 0, 1, 0, 1, 0, 1, 0],
                  [0, 1, 0, 1, 0, 1, 0, 1],
                  [1, 0, 1, 0, 1, 0, 1, 0]])


def test_new_game(field0):  # Creating field test
    assert field0.field == [[0, 3, 0, 3, 0, 3, 0, 3],
                            [3, 0, 3, 0, 3, 0, 3, 0],
                            [0, 3, 0, 3, 0, 3, 0, 3],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [1, 0, 1, 0, 1, 0, 1, 0],
                            [0, 1, 0, 1, 0, 1, 0, 1],
                            [1, 0, 1, 0, 1, 0, 1, 0]]


@pytest.fixture
def field1():
    """
    Optimal field for tests
    """
    return Field([[0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 3, 0, 1, 0, 0, 0, 0],
                  [0, 0, 0, 1, 0, 0, 0, 0],
                  [0, 0, 3, 0, 3, 0, 0, 0],
                  [0, 0, 0, 1, 0, 1, 0, 0],
                  [0, 0, 0, 0, 3, 0, 0, 0],
                  [0, 0, 0, 0, 3, 0, 1, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0]])


def test_draught_move(field1):
    Turn.make_move(Turn(1, 1, 0, 0, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 0, 1, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 0, 2, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 1, 0, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 1, 2, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 2, 1, field1.field))  # Must do nothing
    Turn.make_move(Turn(1, 1, 2, 0, field1.field))
    assert field1.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 1, 0, 0, 0, 0],
                            [3, 0, 0, 1, 0, 0, 0, 0],
                            [0, 0, 3, 0, 3, 0, 0, 0],
                            [0, 0, 0, 1, 0, 1, 0, 0],
                            [0, 0, 0, 0, 3, 0, 0, 0],
                            [0, 0, 0, 0, 3, 0, 1, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]
    Turn.make_move(Turn(2, 0, 3, 1, field1.field))
    assert field1.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 1, 0, 0, 0, 0],
                            [0, 0, 0, 1, 0, 0, 0, 0],
                            [0, 3, 3, 0, 3, 0, 0, 0],
                            [0, 0, 0, 1, 0, 1, 0, 0],
                            [0, 0, 0, 0, 3, 0, 0, 0],
                            [0, 0, 0, 0, 3, 0, 1, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]


def test_draught_attack(field1):
    Turn.make_move(Turn(4, 3, 2, 5, field1.field))  # White attack normal
    Turn.make_move(Turn(2, 3, 4, 1, field1.field))  # White attack backwards
    assert field1.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 3, 0, 1, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 1, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 1, 0, 0, 0, 1, 0, 0],
                            [0, 0, 0, 0, 3, 0, 0, 0],
                            [0, 0, 0, 0, 3, 0, 1, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]
    # Restoring
    field1.set_field([[0, 0, 0, 0, 0, 0, 0, 0],
                      [0, 3, 0, 1, 0, 0, 0, 0],
                      [0, 0, 0, 1, 0, 0, 0, 0],
                      [0, 0, 3, 0, 3, 0, 0, 0],
                      [0, 0, 0, 1, 0, 1, 0, 0],
                      [0, 0, 0, 0, 3, 0, 0, 0],
                      [0, 0, 0, 0, 3, 0, 1, 0],
                      [0, 0, 0, 0, 0, 0, 0, 0]])
    Turn.make_move(Turn(3, 4, 5, 2, field1.field))  # Red attack normal
    Turn.make_move(Turn(5, 4, 3, 6, field1.field))  # Red attack backwards
    assert field1.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 3, 0, 1, 0, 0, 0, 0],
                            [0, 0, 0, 1, 0, 0, 0, 0],
                            [0, 0, 3, 0, 0, 0, 3, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 3, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 3, 0, 1, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]


def test_draught_transform(field1):
    Turn.make_move(Turn(1, 3, 0, 2, field1.field))  # White transform
    Turn.make_move(Turn(6, 4, 7, 3, field1.field))  # Red transform
    assert field1.field == [[0, 0, 2, 0, 0, 0, 0, 0],
                            [0, 3, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 1, 0, 0, 0, 0],
                            [0, 0, 3, 0, 3, 0, 0, 0],
                            [0, 0, 0, 1, 0, 1, 0, 0],
                            [0, 0, 0, 0, 3, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 1, 0],
                            [0, 0, 0, 4, 0, 0, 0, 0]]


@pytest.fixture
def field2():
    """
    Queen field
    """
    return Field([[0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 3, 0, 4, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 2, 0, 1, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0]])


def test_queen_move(field2):
    assert field2.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 3, 0, 4, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 2, 0, 1, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]
    Turn.make_move(Turn(5, 2, 7, 4, field2.field))
    Turn.make_move(Turn(2, 5, 4, 7, field2.field))
    assert field2.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 3, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 4],
                            [0, 0, 0, 0, 1, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 2, 0, 0, 0]]
    Turn.make_move(Turn(7, 4, 3, 0, field2.field))
    Turn.make_move(Turn(4, 7, 0, 3, field2.field))
    assert field2.field == [[0, 0, 0, 4, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 3, 0, 0, 0, 0],
                            [2, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 1, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]


def test_queen_attack(field2):
    assert field2.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 3, 0, 4, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 2, 0, 1, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]
    Turn.make_move(Turn(5, 2, 4, 1, field2.field))
    Turn.make_move(Turn(4, 1, 1, 4, field2.field))
    Turn.make_move(Turn(2, 5, 3, 6, field2.field))
    Turn.make_move(Turn(3, 6, 6, 3, field2.field))
    assert field2.field == [[0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 2, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0],
                            [0, 0, 0, 4, 0, 0, 0, 0],
                            [0, 0, 0, 0, 0, 0, 0, 0]]
