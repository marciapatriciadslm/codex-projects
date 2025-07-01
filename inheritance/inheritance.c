#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

// Function prototypes
person *create_family(int generations);
void print_family(const person *p, int generation);
void free_family(person *p);
char random_allele(void);

int main(void)
{
    // Seed random number generator
    srand(time(NULL));

    // Create a new family with three generations
    int generations = 3;
    person *p = create_family(generations);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
    return 0;
}

// Create a family of `generations` generations
person *create_family(int generations)
{
    // Allocate memory for new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Base case: generation with no parents
    if (generations <= 1)
    {
        p->parents[0] = NULL;
        p->parents[1] = NULL;
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }
    else
    {
        // Recursively create parents
        p->parents[0] = create_family(generations - 1);
        p->parents[1] = create_family(generations - 1);

        // Randomly assign alleles based on parents
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    return p;
}

// Free `p` and all ancestors of `p`
void free_family(person *p)
{
    if (p == NULL)
    {
        return;
    }

    // Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free this person
    free(p);
}

// Print each family member and their alleles
void print_family(const person *p, int generation)
{
    if (p == NULL)
    {
        return;
    }

    // Indentation by generation
    for (int i = 0; i < generation * 4; i++)
    {
        printf(" ");
    }

    // Print person's generation and blood type
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);

    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly choose a blood type allele
char random_allele(void)
{
    switch (rand() % 3)
    {
        case 0:
            return 'A';
        case 1:
            return 'B';
        default:
            return 'O';
    }
}

