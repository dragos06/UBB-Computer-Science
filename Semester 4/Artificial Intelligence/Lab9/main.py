from functions.cross_in_tray import cross_in_tray, DOMAIN as DOMAIN1
from functions.bukin_n6 import bukin_n6, DOMAIN_X, DOMAIN_Y
from utils.plotting import plot_function

if __name__ == "__main__":
    # Plot the functions
    plot_function(cross_in_tray, DOMAIN1, DOMAIN1, "Cross-in-Tray Function")
    plot_function(bukin_n6, DOMAIN_X, DOMAIN_Y, "Bukin N6 Function")