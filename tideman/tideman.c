#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int check_cycle(int thisloser, int original_winner);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            // printf("Rank %i: %s (%i)\n", rank, candidates[i], i);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    int higher_rank_candidate;
    int lower_rank_candidate;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            higher_rank_candidate = ranks[i];
            lower_rank_candidate = ranks[j];
            preferences[higher_rank_candidate][lower_rank_candidate]++;
            // printf("Preferences[%i][%i]: %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pair_count++;
                pairs[pair_count - 1].winner = j;
                pairs[pair_count - 1].loser = i;
            }
            // printf("Pair win: %i\n", pairs[pair_count - 1].winner);
            // printf("Pair lose: %i\n", pairs[pair_count - 1].loser);
        }
    }
    // printf("\nPair count: %i\n\n", pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int maxVoter;
    int highestPair;
    pair temp;
    for (int i = 0; i < pair_count; i++)
    {
        maxVoter = 0;
        highestPair = i;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > maxVoter)
            {
                maxVoter = preferences[pairs[j].winner][pairs[j].loser];
                highestPair = j;
            }
        }
        temp = pairs[i];
        pairs[i] = pairs[highestPair];
        pairs[highestPair] = temp;
    }

    for (int i = 0; i < pair_count; i++)
    {
        // printf("Pair win: %i\n", pairs[i].winner);
        // printf("Pair lose: %i\n", pairs[i].loser);
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //Check every pair in pairs[] by check_cycle function, if pair don't create a loop, then add pair to locked[]
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(pairs[i].loser, pairs[i].winner) == -1)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool check_column;
    for (int i = 0; i < candidate_count; i++)
    {
        check_column = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                check_column = true;;
            }
        }
        if (!check_column)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Check if loser in input pair (thisloser) is winner in any other locked pair,
// if so, check if the loser of that pair is a winner in any other locked pair
// continue until finding the original winner "original_winner"
//- then return -2 as this is a loop (result in not locking pair), or return -1 as it's no loop.
int check_cycle(int thisloser, int original_winner)
{
    // "Default case" - looser in current inputed pair equals to original willer - return -2 (= don't lock pair)
    if (thisloser == original_winner)
    {
        return -2;
    }

    // Go through the pair array to see if the current loser wins in any other pair, use recursion to create
    // chain until above function is satisfied or loop finishes and return -1 (lock pair)
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[thisloser][i] == true && check_cycle(i, original_winner) == -2)
        {
            return -2;
        }
    }
    return -1;
}