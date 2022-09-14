#include <stdio.h>
#include <stdbool.h>

#define EMPTY 0
#define RED 1
#define YELLOW -1

#define SIZE_TO_WIN 4

#define BOARD_SIZE 7

typedef struct Move
{
    int num;
    int turn;
    struct Move* next;
} Move;

void viewBoard(int board[][BOARD_SIZE]);
void goBack(int board[][BOARD_SIZE], Move** head);
Move* createMove(int board[][BOARD_SIZE], int turn, int playerMove);
void addMove(Move** head, Move* moveToAdd);
bool checkWin(int board[][BOARD_SIZE], int turn);
char convert(int turn);

int main()
{
    int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
    int col = 0, turn = RED;
    bool isWin = false;
    Move* headMove = NULL;
    viewBoard(board);
    while (!isWin)
    {
        printf("\n%c, please enter a col(1-7): ", convert(turn));
        scanf("%d", &col);
        if (col == -1)
        {
            goBack(board, &headMove);
        }
        else
        {
            col--;
            addMove(&headMove, createMove(board, turn, col));
        }
        viewBoard(board);
        isWin = checkWin(board, turn);
        turn *= -1;
    }
    printf("\n%c won!", convert(-turn));
    return 0;
}


void viewBoard(int board[][BOARD_SIZE])
{
    int i = 0, j = 0;
    printf("\n 1 2 3 4 5 6 7\n");
    for (i = 0; i < BOARD_SIZE; i++)
    {
        printf("|");
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == EMPTY)
            {
                printf("* ");
            }
            if (board[i][j] == RED)
            {
                printf("X ");
            }
            if (board[i][j] == YELLOW)
            {
                printf("O ");
            }
        }
        printf("|\n");
    }
    printf(" --------------");
}

void goBack(int board[][BOARD_SIZE], Move** head)
{
    Move* first = *head;
    struct Move* temp = *head;
    struct Move* previous = NULL;
    int i = 0;

    // if there are no nodes in Linked List can't delete
    if (*head == NULL)
    {
        printf("\n---No back move available---\n");
        return;
    }

    // if Linked List has only 1 node
    if (temp->next == NULL)
    {
        *head = NULL;
        board[BOARD_SIZE - 1][temp->num] = EMPTY;
        return;
    }

    // else traverse to the last node
    while (temp->next != NULL)
    {
        // store previous link node as we need to change its next val
        printf("temp->num: %d\n", temp->num);
        previous = temp;
        temp = temp->next;
    }
    // Curr assign 2nd last node's next to Null
    // delete the last node
    // 2nd last now becomes the last node


    i = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][temp->num] != EMPTY)
        {
            board[i][temp->num] = EMPTY;
            i = BOARD_SIZE;
        }
    }
    viewBoard(board);
    previous->next = NULL;
    free(temp);
}

Move* createMove(int board[][BOARD_SIZE], int turn, int playerMove)
{
    int i = 0;
    Move* move = (Move*)malloc(sizeof(Move));
    move->next = NULL;
    move->num = playerMove;
    bool validMove = false;

    while (true)
    {
        if (board[0][move->num] != EMPTY)
        {
            printf("\nFull, %d\n", board[0][move->num]);
            printf("\n%c, please enter a col(1-7): ", convert(turn));
            scanf("%d", &move->num);
        }
        else if (move->num < 0 || move->num > 6)
        {
            printf("\nMove not in the area");
            printf("\n%c, please enter a col(1-7): ", convert(turn));
            scanf("%d", &move->num);
        }
        else
        {
            for (i = 0; i < BOARD_SIZE; i++)
            {
                if (board[BOARD_SIZE - 1][move->num] == EMPTY)
                {
                    move->turn = turn;
                    board[BOARD_SIZE - 1][move->num] = turn;
                    return move;
                }
                if (board[i][move->num] != EMPTY)
                {
                    board[i - 1][move->num] = turn;

                    return move;
                }
            }
        }
    }
}

void addMove(Move** head, Move* moveToAdd)
{

    if (!*head)
    {
        *head = moveToAdd; // adding the frame
    }
    else
    {
        addMove(&(*head)->next, moveToAdd);
    }
}

//bool putTurn(int board[][BOARD_SIZE], int col, int turn, Move** head) // going to next move
//{
//    int i = 0;
//    Move* move = (Move*)malloc(sizeof(Move));
//    move->next = NULL;
//    if (board[0][col] != EMPTY)
//    {
//        printf("\nFull, %d\n", board[0][col]);
//        return false;
//    }
//    if (board[BOARD_SIZE - 1][col] == EMPTY)
//    {
//        move->num = col;
//        *(head)->next = move;
//        board[BOARD_SIZE - 1][col] = turn;
//        return true;
//    }
//    else
//    {
//        for (i = 0; i < BOARD_SIZE; i++)
//        {
//            if (board[i][col] != EMPTY)
//            {
//                board[i - 1][col] = turn;
//                return true;
//            }
//        }
//    }
//
//}

bool checkWin(int board[][BOARD_SIZE], int turn)
{
    int i = 0, j = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < SIZE_TO_WIN; j++)
        {
            if (board[i][j] == turn && board[i][j + 1] == turn && board[i][j + 2] == turn && board[i][j + 3] == turn)
            {
                return true;
            }
        }
    }
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < SIZE_TO_WIN; j++)
        {
            if (board[j][i] == turn && board[j + 1][i] == turn && board[j + 2][i] == turn && board[j + 3][i] == turn)
            {
                return true;
            }
        }
    }
    for (i = 0; i < SIZE_TO_WIN; i++)
    {
        for (j = 0; j < SIZE_TO_WIN; j++)
        {
            if (board[j][i] == turn && board[j + 1][i + 1] == turn && board[j + 2][i + 2] == turn && board[j + 3][i + 3] == turn)
            {
                return true;
            }
        }
    }
    for (i = 0; i < SIZE_TO_WIN; i++)
    {
        for (j = 0; j < SIZE_TO_WIN; j++)
        {
            if (board[j][i + 3] == turn && board[j + 1][i + 2] == turn && board[j + 2][i + 1] == turn && board[j + 3][i] == turn)
            {
                return true;
            }
        }
    }
    return false;
}

char convert(int turn)
{
    return turn == RED ? 'X' : 'O';
}
