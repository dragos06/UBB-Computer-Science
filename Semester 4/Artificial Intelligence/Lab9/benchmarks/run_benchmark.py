import numpy as np
import pandas as pd
from functions.cross_in_tray import cross_in_tray, DOMAIN as DOMAIN1
from functions.bukin_n6 import bukin_n6, DOMAIN_X, DOMAIN_Y
from ga.genetic_algorithm import genetic_algorithm


def run_benchmark(func, bounds, encoding, crossover_type, trials=30, **kwargs):
    # Run the genetic algorithm multiple times to gather results
    results = []
    for _ in range(trials):
        fitness = genetic_algorithm(func, bounds, encoding=encoding, crossover_type=crossover_type, **kwargs)
        results.append(fitness[-1])
    return results

def main():
    # Define the configurations for the benchmarks
    configs = [
        ("cross_in_tray", cross_in_tray, [DOMAIN1, DOMAIN1]),
        ("bukin_n6", bukin_n6, [DOMAIN_X, DOMAIN_Y])
    ]
    # Define the encodings and crossover types to test
    encodings = ['real', 'binary']
    crossovers = {
        'real': ['arithmetic', 'blx'],
        'binary': ['1point', '2point']
    }
    # Run the benchmarks for each configuration, encoding, and crossover type
    all_results = []
    for fname, func, bounds in configs:
        for enc in encodings:
            for ctype in crossovers[enc]:
                # Run the genetic algorithm with the specified parameters
                label = f"{fname}_{enc}_{ctype}"
                results = run_benchmark(
                    func, bounds, enc, ctype,
                    pop_size=50, generations=100,
                    mutation_rate=0.1, crossover_rate=0.9
                )
                # Store the results in a DataFrame
                df = pd.DataFrame({'fitness': results})
                df['config'] = label
                all_results.append(df)

    # Concatenate all results into a single DataFrame and save to CSV
    final_df = pd.concat(all_results)
    final_df.to_csv("experiment_results.csv", index=False)
    print("Experiments complete. Results saved to experiment_results.csv")

if __name__ == "__main__":
    main()
