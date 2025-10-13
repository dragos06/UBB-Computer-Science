import numpy as np
import random


def initialize_population(pop_size, bounds, encoding='real', bit_length=16):
    # Initialize a population of individuals based on the specified encoding
    if encoding == 'real':
        return np.random.uniform(bounds[0], bounds[:, 1], size=(pop_size, 2))
    else:
        return np.random.randint(0, 2, size=(pop_size, 2 * bit_length))


def binary_to_real(bits, bound, bit_length):
    # Convert a binary representation to a real number within the specified bounds
    integer = int("".join(str(b) for b in bits), 2)
    return bound[0] + (bound[1] - bound[0]) * integer / (2 ** bit_length - 1)


def decode_binary(individual, bounds, bit_length):
    # Decode a binary individual into real values based on the specified bounds
    x_bin = individual[:bit_length]
    y_bin = individual[bit_length:]
    x = binary_to_real(x_bin, bounds[0], bit_length)
    y = binary_to_real(y_bin, bounds[1], bit_length)
    return np.array([x, y])


def evaluate_population(population, fitness_func, bounds, encoding, bit_length):
    # Evaluate the fitness of each individual in the population
    if encoding == 'real':
        return np.array([fitness_func(ind[0], ind[1]) for ind in population])
    else:
        return np.array([
            fitness_func(*decode_binary(ind, bounds, bit_length)) for ind in population
        ])


def select_parents(population, fitness, num_parents):
    # Select parents based on their fitness using tournament selection
    idx = np.argsort(fitness)
    return population[idx[:num_parents]]


def crossover(parents, encoding='real', crossover_type='arithmetic', alpha=0.5, crossover_rate=0.9):
    children = []
    for i in range(0, len(parents), 2):
        p1, p2 = parents[i], parents[(i + 1) % len(parents)]

        if random.random() < crossover_rate:
            if encoding == 'real':
                if crossover_type == 'arithmetic':
                    child = alpha * p1 + (1 - alpha) * p2
                elif crossover_type == 'blx':
                    c_min = np.minimum(p1, p2)
                    c_max = np.maximum(p1, p2)
                    diff = c_max - c_min
                    child = np.random.uniform(c_min - alpha * diff, c_max + alpha * diff)
            else:
                point = random.randint(1, len(p1) - 1)
                if crossover_type == '1point':
                    child = np.concatenate((p1[:point], p2[point:]))
                else:  # uniform 2-point example
                    child = np.concatenate((p1[:point // 2], p2[point // 2:point], p1[point:]))
        else:
            # No crossover, child is a copy of one parent
            child = p1.copy()

        children.append(child)
    return np.array(children)


def mutate(population, mutation_rate, encoding='real', bounds=None, bit_length=16):
    # Mutate individuals in the population based on the mutation rate
    for i in range(len(population)):
        if encoding == 'real':
            # Randomly mutate real-valued individuals
            mutation = np.random.rand(2) < mutation_rate
            random_val = np.random.uniform(bounds[:, 0], bounds[:, 1])
            population[i][mutation] = random_val[mutation]
        else:
            # Randomly mutate binary individuals
            for j in range(len(population[i])):
                if random.random() < mutation_rate:
                    population[i][j] = 1 - population[i][j]
    return population


def genetic_algorithm(fitness_func, bounds, encoding='real', crossover_type='arithmetic', pop_size=50, generations=100,
                      mutation_rate=0.1, crossover_rate=0.9, bit_length=16):
    # Main function to run the genetic algorithm
    bounds = np.array(bounds)
    population = initialize_population(pop_size, bounds, encoding, bit_length)
    best_fitness = []
    for gen in range(generations):
        fitness = evaluate_population(population, fitness_func, bounds, encoding, bit_length)
        best_fitness.append(np.min(fitness))
        parents = select_parents(population, fitness, pop_size // 2)
        children = crossover(parents, encoding, crossover_type, crossover_rate)
        children = mutate(children, mutation_rate, encoding, bounds, bit_length)
        population[:len(children)] = children
    return best_fitness
