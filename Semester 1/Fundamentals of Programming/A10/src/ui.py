from src.repo_exceptions import RepoExceptions
from src.player import HumanPlayer, ComputerPlayer
from src.board import GomokuBoard


class Console:
    def __init__(self):
        self.__gomoku_board = GomokuBoard()
        self.__human_player = HumanPlayer(self.__gomoku_board, 'X')
        self.__computer_player = ComputerPlayer(self.__gomoku_board, 'O')

    @staticmethod
    def print_menu():
        print("     GOMOKU      ")
        print("Players alternate turns placing a stone of their color on an empty intersection. Black plays first.\n"
              "The winner is the first player to form an unbroken line of five stones of their color horizontally,\n"
              "vertically, or diagonally. In some rules, this line must be exactly five stones long; six or more "
              "stones\n"
              " in a row does not count as a win and is called an 'over-line'. If the board is completely filled and\n"
              "no one can make a line of 5 stones, then the game ends in a draw. ")
        print("X - User Player | O - Computer Player")
        print("User Player goes first")

    def print_board(self):
        print(self.__gomoku_board)

    def start_game(self):
        self.print_menu()
        self.print_board()
        human_player_turn = True
        while True:
            if human_player_turn:
                print("Input coordinates for your piece:")
                try:
                    row = input("Row: ")
                    column = input("Column:")
                    self.__human_player.make_move(row, column)
                    human_player_turn = False
                    if self.__gomoku_board.is_winner(self.__human_player.symbol):
                        print("Human has won the game")
                        break
                except RepoExceptions as e:
                    print(e)
                except ValueError as ve:
                    print('Invalid input: ' + str(ve))
            else:
                self.__computer_player.make_move()
                human_player_turn = True
                self.print_board()
                if self.__gomoku_board.is_winner(self.__computer_player.symbol):
                    print("Computer has won the game")
                    break
            if self.__gomoku_board.is_board_full():
                self.print_board()
                print("Draw")
                break
