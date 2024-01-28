import unittest
from src.board import GomokuBoard
from src.player import HumanPlayer, ComputerPlayer


class UnitTesting(unittest.TestCase):
    def setUp(self):
        self.__board = GomokuBoard()
        self.__human_player = HumanPlayer(self.__board, 'X')
        self.__computer_player = ComputerPlayer(self.__board, 'O')

    def test_human_make_move(self):
        self.__human_player.make_move('1', '1')
        self.__human_player.make_move('12', '6')
        self.__human_player.make_move('5', '9')
        self.assertEqual(self.__board.place(0, 0), 'X')
        self.assertEqual(self.__board.place(11, 5), 'X')
        self.assertEqual(self.__board.place(4, 8), 'X')

    def test_computer_best_move(self):
        self.__board.make_move(0, 0, 'O')
        self.__board.make_move(1, 1, 'O')
        self.__board.make_move(2, 2, 'O')
        self.__board.make_move(4, 4, 'O')
        self.__computer_player.make_move()
        self.assertEqual(self.__board.place(3, 3), 'O')

    def test_computer_block_move(self):
        self.__board.make_move(0, 0, 'X')
        self.__board.make_move(1, 1, 'X')
        self.__board.make_move(2, 2, 'X')
        self.__board.make_move(3, 3, 'X')
        self.__computer_player.make_move()
        self.assertEqual(self.__board.place(4, 4), 'O')

    def test_is_winner(self):
        self.__board.make_move(0, 0, 'X')
        self.__board.make_move(1, 1, 'X')
        self.__board.make_move(2, 2, 'X')
        self.__board.make_move(3, 3, 'X')
        self.__board.make_move(4, 4, 'X')
        self.assertEqual(self.__board.is_winner('X'), True)

        self.__board.undo_move(0, 0, 'X')
        self.__board.undo_move(1, 1, 'X')
        self.__board.undo_move(2, 2, 'X')
        self.__board.undo_move(3, 3, 'X')
        self.__board.undo_move(4, 4, 'X')

        self.__board.make_move(0, 0, 'X')
        self.__board.make_move(0, 1, 'X')
        self.__board.make_move(0, 2, 'X')
        self.__board.make_move(0, 3, 'X')
        self.__board.make_move(0, 4, 'X')
        self.assertEqual(self.__board.is_winner('X'), True)

        self.__board.undo_move(0, 0, 'X')
        self.__board.undo_move(0, 1, 'X')
        self.__board.undo_move(0, 2, 'X')
        self.__board.undo_move(0, 3, 'X')
        self.__board.undo_move(0, 4, 'X')

        self.__board.make_move(0, 0, 'X')
        self.__board.make_move(1, 0, 'X')
        self.__board.make_move(2, 0, 'X')
        self.__board.make_move(3, 0, 'X')
        self.__board.make_move(4, 0, 'X')
        self.assertEqual(self.__board.is_winner('X'), True)

        self.__board.undo_move(0, 0, 'X')
        self.__board.undo_move(1, 0, 'X')
        self.__board.undo_move(2, 0, 'X')
        self.__board.undo_move(3, 0, 'X')
        self.__board.undo_move(4, 0, 'X')

        self.__board.make_move(0, 4, 'X')
        self.__board.make_move(1, 3, 'X')
        self.__board.make_move(2, 2, 'X')
        self.__board.make_move(3, 1, 'X')
        self.__board.make_move(4, 0, 'X')
        self.assertEqual(self.__board.is_winner('X'), True)

    def test_is_board_full(self):
        for i in range(self.__board.size):
            for j in range(self.__board.size):
                self.__human_player.make_move(str(i + 1), str(j + 1))
        self.assertEqual(self.__board.is_board_full(), True)
