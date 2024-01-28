import tkinter as tk
from tkinter import messagebox
from src.repo_exceptions import RepoExceptions
from src.player import HumanPlayer, ComputerPlayer
from src.board import GomokuBoard


class GomokuGUI:
    def __init__(self, master):
        self._master = master
        self._master.title("Gomoku Game")

        self._gomoku_board = GomokuBoard()
        self._human_player = HumanPlayer(self._gomoku_board, 'X')
        self._computer_player = ComputerPlayer(self._gomoku_board, 'O')

        self.create_widgets()
        self._game_over = False

    def create_widgets(self):
        self.label = tk.Label(self._master, text="Gomoku Game", font=("Helvetica", 16))
        self.label.pack(pady=10)

        self.canvas = tk.Canvas(self._master, width=400, height=400, bg="white")
        self.canvas.pack()

        self.canvas.bind("<Button-1>", self.on_canvas_click)

        self.restart_button = tk.Button(self._master, text="Restart Game", command=self.restart_game)
        self.restart_button.pack(pady=10)

        self.draw_board()

    def draw_board(self):
        self.canvas.delete("all")
        cell_size = 400 // self._gomoku_board.size

        for i in range(self._gomoku_board.size):
            for j in range(self._gomoku_board.size):
                x1, y1 = j * cell_size, i * cell_size
                x2, y2 = x1 + cell_size, y1 + cell_size
                self.canvas.create_rectangle(x1, y1, x2, y2, outline="black")

                symbol = self._gomoku_board.place(i, j)
                if symbol == 'X':
                    self.canvas.create_text((x1 + x2) // 2, (y1 + y2) // 2, text="X", font=("Helvetica", 12))
                elif symbol == 'O':
                    self.canvas.create_text((x1 + x2) // 2, (y1 + y2) // 2, text="O", font=("Helvetica", 12))

    def on_canvas_click(self, event):
        cell_size = 400 // self._gomoku_board.size
        row = event.y // cell_size
        column = event.x // cell_size
        if self._game_over:
            return
        try:
            self._human_player.make_move(str(row + 1), str(column + 1))
            self.draw_board()

            if self._gomoku_board.is_winner(self._human_player.symbol):
                self.display_winner("Human")
            elif self._gomoku_board.is_board_full():
                self.display_draw()
            else:
                self._computer_player.make_move()
                self.draw_board()

                if self._gomoku_board.is_winner(self._computer_player.symbol):
                    self.display_winner("Computer")
                elif self._gomoku_board.is_board_full():
                    self.display_draw()

        except RepoExceptions as e:
            print(e)
        except ValueError as ve:
            print('Invalid input: ' + str(ve))

    def restart_game(self):
        self._game_over = False
        self._gomoku_board = GomokuBoard()
        self._human_player = HumanPlayer(self._gomoku_board, 'X')
        self._computer_player = ComputerPlayer(self._gomoku_board, 'O')
        self.draw_board()

    def display_winner(self, winner):
        tk.messagebox.showinfo("Game Over", f"{winner} has won the game!")
        self._game_over = True

    def display_draw(self):
        tk.messagebox.showinfo("Game Over", "The game is a draw!")
