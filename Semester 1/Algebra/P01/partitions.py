def print_current_partition(given_partition):  # THIS FUNCTION PRINTS THE PARTITION EVERYTIME IT GETS COMPLETED
    print("{ ", end="")
    for sub_partition in given_partition:
        print("{", end=" ")
        for set_number in sub_partition:
            print(f"a{set_number}", end=" ")
        print("}", end=" ")
    print("} ---> ", end="")


def partition_set(set_list, current_pos, partition_list):  # THIS FUNCTION GENERATES EVERY PARTITION OF SET A
    if current_pos == len(set_list):  # WE PRINT THE PARTITION WHEN THE NUMBER OF ELEMENTS IS EQUAL TO THE GIVEN LENGTH
        print_current_partition(partition_list)
        if len(partition_list) == 1:  # IF WE HAVE ONLY A SUBPARTITION, THE EQUIV. REL. IS AxA
            print("AxA\n")
        elif len(partition_list) == user_n_number:
            # IF THE NUMBER OF SUBPARTITIONS IS EQUAL TO THE GIVEN LENGTH, ΔA IS THE EQUIV. REL.
            print("ΔA\n")
        else:
            print("ΔA U ", end="{ ")
            for sub_partition in range(len(partition_list)):
                if 1 < len(partition_list[sub_partition]) < user_n_number:
                    from itertools import permutations
                    equiv_rel = permutations(partition_list[sub_partition], 2)
                    # WE GENERATE ALL EQUIVALENCE RELATIONS USING ARRANGEMENTS OF 2 OF THE ELEMENTS OF THE PARTITION
                    for relation in list(equiv_rel):
                        print("( ", end="")
                        for relation_number in relation:
                            print(f"a{relation_number}", end=" ")
                        print(")", end=" ")
            print("}\n")
        return
    for sub_partition in range(len(partition_list)):
        # WE ADD IN THE PARTITION THE NUMBER OF SET A AT THE CURRENT POSITION AND RECALL THE FUNCTION
        partition_list[sub_partition].append(set_list[current_pos])
        partition_set(set_list, current_pos + 1, partition_list)
        partition_list[sub_partition].pop()  # WE FREE THE LAST POSITION TO COMPLETE IT WITH ANOTHER SUBPARTITION
    # WE ADD ANOTHER SUBPARTITION IF WE STILL HAVE UNUSED ELEMENTS
    partition_list.append([set_list[current_pos]])
    partition_set(set_list, current_pos + 1, partition_list)
    partition_list.pop()  # WE CLEAR THE LAST SUBPARTITION TO SEE IF WE CAN USE ANOTHER VALUE IN ITS POSITION


def find_bell_number(n: int) -> int:
    # BASED ON MY RESEARCH, THE NUMBER OF POSSIBLE PARTITIONS OF A SET IS CALLED THE BELL NUMBER
    # USING THE BELL TRIANGLE, THE NUMBER OF PARTITIONS OF A SET OF LENGTH UP TO 8 IS AS FOLLOWS:
    if n == 0 or n == 1:
        return 1
    elif n == 2:
        return 2
    elif n == 3:
        return 5
    elif n == 4:
        return 15
    elif n == 5:
        return 52
    elif n == 6:
        return 203
    elif n == 7:
        return 877
    elif n == 8:
        return 4140


user_n_number = int(input("Please enter a non-zero natural number n: "))
print("\n")
set_A = []
for number in range(1, user_n_number + 1):
    set_A.append(number)  # WE CREATE THE SET A OF N ELEMENTS
print(f"1. The number of partitions on set A = {set_A} is: ", find_bell_number(len(set_A)))
print("\n")
print(f"2. the partitions on set A = {set_A} and their corresponding equivalence relations are:\n")
partition_backtrack = []
partition_set(set_A, 0, partition_backtrack)
# SERBAN DRAGOS
