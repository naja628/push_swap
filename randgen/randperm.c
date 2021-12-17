#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int *rand_perm(int n)
{
	int *tab = malloc(sizeof(int) * n);

	for (int i = 0; i < n; ++i)
		tab[i] = i;
	while (n > 0)
	{
		swap(tab + (rand() % n), tab + n - 1);
		--n;
	}
	return (tab);
}

int main(int ac, char **av)
{
	if (ac != 2)
		exit(-1);
	int n = atoi(av[1]);
	srand(time(NULL));
	int *tab = rand_perm(n);
	for (int i = 0; i < n; i++)
		printf("%d ", tab[i]);
	printf("\n");
	free(tab);
	return (0);
}
