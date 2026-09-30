#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CANDIDATES 10
#define NAME_LEN 50
#define PARTY_LEN 30

// Structure to store Candidate details
struct Candidate {
    int id;
    char name[NAME_LEN];
    char party[PARTY_LEN];
    int votes;
};

// Function Prototypes
void setupCandidates(struct Candidate candidates[], int *candidateCount);
void displayCandidates(const struct Candidate candidates[], int candidateCount);
void castVote(struct Candidate candidates[], int candidateCount, int *totalVotes);
void checkVoteResults(const struct Candidate candidates[], int candidateCount, int totalVotes);

int main() {
    struct Candidate candidates[MAX_CANDIDATES];
    int candidateCount = 0;
    int totalVotes = 0;
    int choice;

    printf("=========================================\n");
    printf("     WELCOME TO THE ELECTION SYSTEM      \n");
    printf("=========================================\n\n");

    // Step 1: Prompt user to set up candidates and party affiliations
    setupCandidates(candidates, &candidateCount);

    // Step 2: Main interactive menu
    do {
        printf("\n-----------------------------------------\n");
        printf("               MAIN MENU                 \n");
        printf("-----------------------------------------\n");
        printf("1. Cast a Vote\n");
        printf("2. Check Vote Tally & Results\n");
        printf("3. Display Candidate List\n");
        printf("4. Exit Election System\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a valid number.\n");
            while (getchar() != '\n'); // Clear invalid input buffer
            continue;
        }

        switch (choice) {
            case 1:
                castVote(candidates, candidateCount, &totalVotes);
                break;
            case 2:
                checkVoteResults(candidates, candidateCount, totalVotes);
                break;
            case 3:
                displayCandidates(candidates, candidateCount);
                break;
            case 4:
                printf("\nClosing voting system. Final election results saved.\n");
                break;
            default:
                printf("\nInvalid option! Please select between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}

// Prompt user to enter candidates and their party affiliations
void setupCandidates(struct Candidate candidates[], int *candidateCount) {
    int count;

    printf("--- INITIAL ELECTION SETUP ---\n");
    printf("How many candidates are running? (1-%d): ", MAX_CANDIDATES);
    scanf("%d", &count);
    while (getchar() != '\n'); // Consume newline left in buffer

    if (count < 1 || count > MAX_CANDIDATES) {
        printf("Invalid count! Defaulting to 2 candidates.\n");
        count = 2;
    }

    for (int i = 0; i < count; i++) {
        candidates[i].id = i + 1;
        candidates[i].votes = 0;

        printf("\nCandidate #%d Name: ", i + 1);
        fgets(candidates[i].name, NAME_LEN, stdin);
        candidates[i].name[strcspn(candidates[i].name, "\n")] = '\0'; // Remove newline

        printf("Candidate #%d Party Affiliation: ", i + 1);
        fgets(candidates[i].party, PARTY_LEN, stdin);
        candidates[i].party[strcspn(candidates[i].party, "\n")] = '\0'; // Remove newline
    }

    *candidateCount = count;
    printf("\nSuccess: Election setup complete with %d candidate(s).\n", count);
}

// Display the list of candidate IDs, names, and party affiliations
void displayCandidates(const struct Candidate candidates[], int candidateCount) {
    printf("\n%-5s | %-25s | %-20s\n", "ID", "Candidate Name", "Party Affiliation");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%-5d | %-25s | %-20s\n", 
               candidates[i].id, 
               candidates[i].name, 
               candidates[i].party);
    }
}

// Process a single vote and thank the voter
void castVote(struct Candidate candidates[], int candidateCount, int *totalVotes) {
    int candidateID;

    printf("\n--- CAST YOUR VOTE ---\n");
    displayCandidates(candidates, candidateCount);

    printf("\nEnter the Candidate ID you wish to vote for: ");
    if (scanf("%d", &candidateID) != 1) {
        printf("Invalid entry! Vote canceled.\n");
        while (getchar() != '\n');
        return;
    }

    // Check if ID matches a valid candidate
    if (candidateID >= 1 && candidateID <= candidateCount) {
        candidates[candidateID - 1].votes++;
        (*totalVotes)++;

        // Thank you message for voters
        printf("\n=========================================\n");
        printf(" THANK YOU FOR CASTING YOUR VOTE!       \n");
        printf(" Your ballot for %s (%s) has been recorded.\n", 
               candidates[candidateID - 1].name, 
               candidates[candidateID - 1].party);
        printf("=========================================\n");
    } else {
        printf("Error: Candidate ID %d does not exist. Vote rejected.\n", candidateID);
    }
}

// Display vote tallies and declare the current leader/winner
void checkVoteResults(const struct Candidate candidates[], int candidateCount, int totalVotes) {
    printf("\n=========================================\n");
    printf("          CURRENT ELECTION TALLY         \n");
    printf("=========================================\n");
    printf("Total Votes Cast: %d\n\n", totalVotes);

    if (totalVotes == 0) {
        printf("No votes have been cast yet.\n");
        return;
    }

    int winningIndex = 0;
    int maxVotes = -1;

    printf("%-5s | %-20s | %-15s | %-10s | %-10s\n", "ID", "Name", "Party", "Votes", "Percentage");
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i < candidateCount; i++) {
        double percentage = ((double)candidates[i].votes / totalVotes) * 100.0;
        printf("%-5d | %-20s | %-15s | %-10d | %6.2f%%\n",
               candidates[i].id,
               candidates[i].name,
               candidates[i].party,
               candidates[i].votes,
               percentage);

        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winningIndex = i;
        }
    }

    printf("------------------------------------------------------------------------\n");
    printf("CURRENT LEADER / WINNER: %s (%s) with %d votes!\n",
           candidates[winningIndex].name,
           candidates[winningIndex].party,
           candidates[winningIndex].votes);
}