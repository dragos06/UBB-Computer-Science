#include <stdio.h>

void print_menu()
{
	/*
	* This function prints the menu of the application.
	* -input: none
	* -output: the menu is printed
	*/
	printf("	MENU APPLICATION\n");
	printf("1. Read a vector of length n.\n");
	printf("2. Print the Pascal triangle of dimension n of all combinations C(m,k) of m objects taken by k, k = 0, 1, ..., m, for line m, where m = 1, 2, ..., n.\n");
	printf("3. Given a vector of numbers, find the longest contiguous subsequence of prime numbers.\n");
	printf("4. Exit.\n");
}

int is_prime(int number)
{
	/*
	* This functions checks if a number is prime.
	* -input: number - integer
	* -output: 1 if the number is prime, 0 otherwise
	*/
	if (number < 2)
		return 0;
	if (number == 2)
		return 1;
	if (number % 2 == 0)
			return 0;
	for (int d = 3; d * d <= number; d += 2)
		if (number % d == 0)
			return 0;
	return 1;
}

void option_1(int length, int vector[])
{
	/*
	* This function reads a vector of length n.
	* -input: length - integer, vector - array of integers
	* -output: the vector is read
	*/
	int current_vector = 0;
	printf("Please enter the elements of the vector:\n");
	for (int i = 0; i < length; i++)
	{
		printf("Element %d: ", i + 1);
		scanf_s("%d", &current_vector);
		vector[i] = current_vector;
		printf("\n");
	}
}

void option_2(int dimension)
{
	/*
	* This function prints the Pascal triangle of dimension n of all combinations C(m,k) of m objects taken by k, k = 0, 1, ..., m, for line m, where m = 1, 2, ..., n.
	* -input: dimension - integer
	* -output: the Pascal triangle is printed
	*/
	int triangle[100][100] = { 0 };
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
		{
			if (i == j || j == 0)
				triangle[i][j] = 1;
			else
				triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
		}
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < i + 1; j++)
			printf("%d ", triangle[i][j]);
		printf("\n");
	}
}

void option_3(int vector_list[], int vector_length)
{
	/*
	* This function finds the longest contiguous subsequence of prime numbers in a given vector.
	* -input: vector_list - array of integers, vector_length - integer
	* -output: the longest contiguous subsequence of prime numbers is printed
	*/
	int length_max_subsequence = 0, max_finish_index = 0, length_subsequence = 0;
	for (int i = 0; i < vector_length - 1; i++)
	{ 
		if (is_prime(vector_list[i]))
			length_subsequence++;
		if (length_subsequence > length_max_subsequence)
			length_max_subsequence = length_subsequence, max_finish_index = i;
		if (!is_prime(vector_list[i]))
			length_subsequence = 0;
	}
	for (int i = max_finish_index - length_max_subsequence + 1; i <= max_finish_index; i++)
		printf("%d ", vector_list[i]);
}

int main()
{
	int user_option = 0, vector_list[100] = {0}, vector_length = 0;
	print_menu();
	while (1)
	{
		printf("\nPlease select an option: ");
		scanf_s("%d", &user_option);
		switch (user_option)
		{
			case 1:
				printf("Please enter the length of the list of vectors: ");
				scanf_s("%d", &vector_length);
				option_1(vector_length, vector_list);
				break;
			case 2:
			{
				int triangle_dimension = 0;
				printf("Please enter the dimension of the triangle: ");
				scanf_s("%d", &triangle_dimension);
				option_2(triangle_dimension);
				break;
			}
			case 3:
				if (vector_length == 0)
					printf("Vector hasn't been read. Please choose option 1.");
				else
					option_3(vector_list, vector_length);
				break;
			case 4:
				printf("Exiting...");
				return 0;
			default:
				printf("Invalid input.");
				break;
		}
	}
	return 0;
}