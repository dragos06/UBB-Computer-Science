import random
from src.repo_exceptions import RepoExceptions, InvalidInputError
from src.board import GomokuBoard


class Player:
    def __init__(self, gomoku_board: GomokuBoard, symbol: str):
        self._gomoku_board = gomoku_board
        self._symbol = symbol

    @property
    def symbol(self):
        """
        Returns the current player's symbol
        :return: current player symbol
        """
        return self._symbol

    @property
    def display_board(self):
        """
        Display's the board
        :return: current gomoku board
        """
        return self._gomoku_board


class HumanPlayer(Player):
    @property
    def opponent_symbol(self):
        """
        Returns the opponent's symbol
        :return: opponent's symbol
        """
        return self._gomoku_board.get_opponent_symbol('X')

    def make_move(self, row: str, column: str):
        """
        Makes a move based on the given row or column
        :param row: row to place piece
        :param column: column to place piece
        :raise: InvalidInputError if row and column are not numbers
        """
        if not (row.isnumeric() and column.isnumeric()):
            raise InvalidInputError
        self._gomoku_board.make_move(int(row) - 1, int(column) - 1, self._symbol)


class ComputerPlayer(Player):
    @property
    def opponent_symbol(self):
        """
        Returns the opponent's symbol
        :return: opponent's symbol
        """
        return self._gomoku_board.get_opponent_symbol('O')

    def make_move(self):
        """
        Makes the computer best move in case it can or makes a random one
        """
        best_move = self.get_best_move()
        if best_move:
            row, column = best_move
            self._gomoku_board.make_move(row, column, self._symbol)
        else:
            try:
                row = random.randint(0, self._gomoku_board.size - 1)
                column = random.randint(0, self._gomoku_board.size - 1)
                self._gomoku_board.make_move(row, column, 'O')
            except RepoExceptions:
                self.make_move()

    def get_best_move(self) -> (int, int):
        """
        Makes winning move or blocks the opponent in case he can win
        :return: the row and column of the best move
        """
        for row in range(self._gomoku_board.size):
            for column in range(self._gomoku_board.size):
                if self._gomoku_board.place(row, column) not in [self.opponent_symbol, self.symbol]:
                    self._gomoku_board.make_move(row, column, self._symbol)
                    if self._gomoku_board.is_winner(self._symbol):
                        self._gomoku_board.undo_move(row, column, self._symbol)
                        return row, column
                    self._gomoku_board.undo_move(row, column, self._symbol)

        for row in range(self._gomoku_board.size):
            for column in range(self._gomoku_board.size):
                if self._gomoku_board.place(row, column) not in [self.opponent_symbol, self.symbol]:
                    self._gomoku_board.make_move(row, column, self.opponent_symbol)
                    if self._gomoku_board.is_winner(self.opponent_symbol):
                        self._gomoku_board.undo_move(row, column, self.opponent_symbol)
                        return row, column
                    self._gomoku_board.undo_move(row, column, self.opponent_symbol)

        center = self._gomoku_board.size // 2
        if self._gomoku_board.place(center, center) == ' ':
            return center, center

        for distance in range(1, self._gomoku_board.size // 2 + 1):
            for i in range(4):
                row, column = self.get_edge_position(center, distance, i)
                if row != -1 and column != -1 and self._gomoku_board.place(row, column) == ' ':
                    return row, column
        return None

    def get_edge_position(self, center, distance, direction):
        """
        Gets the edge position closest to the centre
        :param center: centre of gomoku board
        :param distance: distance from centre
        :param direction: direction of distance
        :return: row and column of closest edge position
        """
        directions = [(0, 1), (1, 0), (1, 1), (-1, 1)]
        row, col = center + distance * directions[direction][0], center + distance * directions[direction][1]
        if 0 <= row < self._gomoku_board.size and 0 <= col < self._gomoku_board.size:
            return row, col
        return -1, -1
