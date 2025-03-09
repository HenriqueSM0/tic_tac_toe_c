# include <stdio.h>
# include <string.h>
# include <Windows.h>

# define BLUE "\x1b[34m"
# define RED "\x1b[31m"
# define YELLOW "\x1b[33m"
# define RESET "\x1b[0m"

# define AIR 'A'
# define P1 '1'
# define P2 '2'

typedef struct {
    char spaces[3][3];
    int round;
    char current_player;
} table;

void print_char (char C) {
    if (C == AIR) {
        printf("o");
    } else if (C == P1) {
        printf("%so%s", BLUE, RESET);
    } else {
        printf("%so%s", RED, RESET);
    }
}

void table_init (table * T) {
    T->round = 0;
    T->current_player = P1;
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            T->spaces[i][j] = AIR;
        }
    }
}

void print_table (table * T) {
    if (T->current_player == P1) {
        printf("%s P1 %s\n\n", BLUE, RESET);
    } else {
        printf("%s P2 %s\n\n", RED, RESET);
    }
    printf(" A  B  C\n");
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" ");
            print_char(T->spaces[i][j]);
            printf(" ");
        }
        printf(" %d\n", i + 1);
    }
    printf("\n");
}

void position_select (table * T) {
    char answer[2];
    printf("Write where you want to put your ball\n");
    int valid_answer = 0;
    scanf("%[^\n]%*c", answer);
    if ((strcmp(answer, "A1") == 0) && (T->spaces[0][0] == AIR)) {
        T->spaces[0][0] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "B1") == 0) && (T->spaces[0][1] == AIR)) {
        T->spaces[0][1] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "C1") == 0) && (T->spaces[0][2] == AIR)) {
        T->spaces[0][2] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "A2") == 0) && (T->spaces[1][0] == AIR)) {
        T->spaces[1][0] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "B2") == 0) && (T->spaces[1][1] == AIR)) {
        T->spaces[1][1] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "C2") == 0) && (T->spaces[1][2] == AIR)) {
        T->spaces[1][2] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "A3") == 0) && (T->spaces[2][0] == AIR)) {
        T->spaces[2][0] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "B3") == 0) && (T->spaces[2][1] == AIR)) {
        T->spaces[2][1] = T->current_player;
        valid_answer = 1;
    } else if ((strcmp(answer, "C3") == 0) && (T->spaces[2][2] == AIR)) {
        T->spaces[2][2] = T->current_player;
        valid_answer = 1;
    }
    if (valid_answer == 1) {
        if (T->current_player == P1) {
            T->current_player = P2;
        } else {
            T->current_player = P1;
        }
        T->round++;
    } else {
        printf("%s Invalid answer  !!! %s\n", YELLOW, RESET);
        Sleep(1000);
    }
}

int analyze_x (table * T, char C) {
    int i;
    for (i = 0; i < 3; i++) {
        if ((T->spaces[i][0] == C) && (T->spaces[i][1] == C) && (T->spaces[i][2] == C)) {
            return 1;
        }
    }
    return 0;
}

int analyze_y (table * T, char C) {
    int j;
    for (j = 0; j < 3; j++) {
        if ((T->spaces[0][j] == C) && (T->spaces[1][j] == C) && (T->spaces[2][j] == C)) {
            return 1;
        }
    }
    return 0;
}

int analyze_d_1 (table * T, char C) {
    if ((T->spaces[0][0] == C) && (T->spaces[1][1] == C) && (T->spaces[2][2] == C)) {
        return 1;
    }
    return 0;
}

int analyze_d_2 (table * T, char C) {
    if ((T->spaces[2][0] == C) && (T->spaces[1][1] == C) && (T->spaces[0][2] == C)) {
        return 1;
    }
    return 0;
}

int analyse_winner (table T) {
    if (analyze_x(&T, P1) || analyze_y(&T, P1) || analyze_d_1(&T, P1) || analyze_d_2(&T, P1)) {
        printf("%sPlayer 1 wins%s\n", BLUE, RESET);
        return 1;
    }
    if (analyze_x(&T, P2) || analyze_y(&T, P2) || analyze_d_1(&T, P2) || analyze_d_2(&T, P2)) {
        printf("%sPlayer 2 wins%s\n", RED, RESET);
        return 1;
    }
    return 0;
}

void main () {
    table T;
    table_init(&T);
    int game_work = 1;
    while (game_work) {
        print_table(&T);
        if (analyse_winner(T)) {
            game_work = 0;
        } else if (T.round == 9) {
            game_work = 0;
        } else {
            position_select(&T);
        }
    }
}

