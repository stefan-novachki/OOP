// Lab 1 - 3

#include <stdio.h>

typedef struct FootballPlayer {
    char name[20];
    int number;
    int goals;
} FootballPlayer;

typedef struct FootballTeam {
    char name[20];
    FootballPlayer players[11];
} FootballTeam;

int sumGoals(FootballTeam team) {
    int sum = 0;

    for (int i = 0; i < 11; i++) {
        sum += team.players[i].goals;
    }

    return sum;
}

void bestTeam(FootballTeam *teams, int n) {
    int maxGoals = 0;
    int indexOfBestTeam = 0;

    for (int i = 0; i < n; i++) {
        if (sumGoals(teams[i]) > maxGoals) {
            maxGoals = sumGoals(teams[i]);
            indexOfBestTeam = i;
        }
    }

    printf("Najdobar tim e: %s", teams[indexOfBestTeam].name);
}

void readPlayer(FootballPlayer *player) {
    scanf("%s %d %d", player->name, &player->number, &player->goals);
}

int main() {
    int n;
    scanf("%d", &n);

    FootballTeam teams[n];

    for (int i = 0; i < n; ++i) {
        scanf("%s", teams[i].name);

        for (int j = 0; j < 11; j++) {
            readPlayer(&teams[i].players[j]);
        }
    }

    bestTeam(teams, n);
    return 0;
}