from texttable import Texttable
from src.repo_exceptions import OutOfBoundsError, PlaceAlreadyUsedError


class GomokuBoard:
    def __init__(self, size: int = 15):
        self.__size = size
        self.__board = [[' ' for _ in range(size)] for _ in range(size)]

    def __str__(self):
        table = Texttable()
        header = [' '] + [str(i + 1) for i in range(self.size)]
        table.header(header)
        for i in range(self.size):
            row = [str(i + 1)] + self.__board[i]
            table.add_row(row)
        return table.draw()

    def make_move(self, row: int, column: int, player: str):
        """
        Stores the move on the board in case the parameters are correct
        :param row: Row to make move on
        :param column: Column to make move on
        :param player: Symbol of current player
        :raises: PlaceAlreadyUsedError in case the space is not free
                OutOfBoundsError in case row or column are out of the board size
        """
        if 0 <= row < self.__size and 0 <= column < self.__size:
            if self.__board[row][column] == ' ':
                self.__board[row][column] = player
            else:
                raise PlaceAlreadyUsedError
        else:
            raise OutOfBoundsError

    def undo_move(self, row: int, column: int, player: str):
        """
        Undoes the move
        :param row: Row to undo move for
        :param column: Column to undo move for
        :param player: Player symbol for which to undo move
        """
        if 0 <= row < self.__size and 0 <= column < self.__size and self.__board[row][column] == player:
            self.__board[row][column] = ' '

    def is_winner(self, player: str) -> bool:
        """
        Checks all possible winning conditions
        :param player: Player's symbol to check if it has won
        :return: True if won, False otherwise
        """
        for i in range(self.__size):
            for j in range(self.__size - 4):
                if self.__board[i][j] == self.__board[i][j + 1] == self.__board[i][j + 2] == self.__board[i][j + 3] == \
                        self.__board[i][j + 4] == player:
                    return True
        for i in range(self.__size - 4):
            for j in range(self.__size):
                if self.__board[i][j] == self.__board[i + 1][j] == self.__board[i + 2][j] == self.__board[i + 3][j] == \
                        self.__board[i + 4][j] == player:
                    return True

        for i in range(self.__size - 4):
            for j in range(self.__size - 4):
                if self.__board[i][j] == self.__board[i + 1][j + 1] == self.__board[i + 2][j + 2] == \
                        self.__board[i + 3][j + 3] == self.__board[i + 4][j + 4] == player:
                    return True

        for i in range(4, self.__size):
            for j in range(self.__size - 4):
                if self.__board[i][j] == self.__board[i - 1][j + 1] == self.__board[i - 2][j + 2] == \
                        self.__board[i - 3][j + 3] == self.__board[i - 4][j + 4] == player:
                    return True

        return False

    def is_board_full(self) -> bool:
        """
        Checks if board is full
        :return: True in case it's full, False otherwise
        """
        for row in self.__board:
            if ' ' in row:
                return False
        return True

    def place(self, row: int, column: int) -> str:
        """
        :param row: Row of piece
        :param column: Column of piece
        :return: the piece at the place located on specified row and column
        """
        return self.__board[row][column]

    @staticmethod
    def get_opponent_symbol(player_symbol: str):
        return 'X' if player_symbol == 'O' else 'O'

    @property
    def size(self):
        return self.__size
