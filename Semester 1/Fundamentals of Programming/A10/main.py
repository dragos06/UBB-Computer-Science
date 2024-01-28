import configparser

from src.ui import Console
from src.gui import GomokuGUI
import tkinter as tk


def console_interface():
    console = Console()

    console.start_game()


def gui_interface():
    root = tk.Tk()
    app = GomokuGUI(root)
    root.mainloop()


def main():
    config = configparser.ConfigParser()
    config.read("settings.properties")

    interface_choice = config.get("Settings", "interface", fallback='ui')

    if interface_choice.lower() == 'gui':
        gui_interface()
    else:
        console_interface()


if __name__ == '__main__':
    main()
