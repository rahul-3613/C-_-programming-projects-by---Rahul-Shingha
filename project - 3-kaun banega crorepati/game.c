#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

const char *COLOR_END = "";
const char *RED = "";
const char *GREEN = "";
const char *YELLOW = "";
const char *BLUE = "";
const char *PINK = "";
const char *AQUA = "";

typedef struct
{
    char text[MAX_QUES_LEN];
    char options[4][MAX_OPTION_LEN];
    char correct_option;
    int timeout;
    int prize_money;
} Question;

int read_questions(char *file_name, Question **questions);
void print_formatted_question(Question question);
void play_game(Question *questions, int no_of_questions);
int use_lifeline(Question *question, int *lifeline);
void print_banner();

int main()
{
    srand(time(NULL));
    print_banner();

    Question *questions;
    int no_of_questions = read_questions("questions.txt", &questions);
    play_game(questions, no_of_questions);
    return 0;
}

void print_banner()
{
    printf("\n\n***********************************************\n");
    printf("*     Chalo Kehlte hain KAUN BANEGA CROREPATI *\n");
    printf("*           Developed by Rahul Shingha         *\n");
    printf("***********************************************\n\n");
}

void play_game(Question *questions, int no_of_questions)
{
    int money_won = 0;
    int lifeline[] = {1, 1};

    for (int i = 0; i < no_of_questions; i++)
    {
        print_formatted_question(questions[i]);

        printf("\nEnter your answer (A, B, C, D or L for lifeline): ");
        char ch = toupper(getch());
        printf("%c\n", ch);

        if (ch == 'L')
        {
            int value = use_lifeline(&questions[i], lifeline);
            if (value != 2)
            {
                i--;
            }
            continue;
        }

        if (ch == questions[i].correct_option)
        {
            printf("\nCorrect!");
            money_won = questions[i].prize_money;
            printf("\nYou have won: Rs %d\n", money_won);
        }
        else
        {
            printf("\nWrong! Correct answer is %c.", questions[i].correct_option);
            break;
        }
    }
    printf("\n\nGame Over! Your total winnings are: Rs %d\n", money_won);
}

int use_lifeline(Question *question, int *lifeline)
{
    printf("\n\nAvailable Lifelines:");
    if (lifeline[0])
        printf("\n1. Fifty-Fifty (50/50)");
    if (lifeline[1])
        printf("\n2. Skip the Question");
    printf("\nChoose a lifeline or 0 to return: ");

    char ch = getch();
    printf("%c\n", ch);

    switch (ch)
    {
    case '1':
        if (lifeline[0])
        {
            lifeline[0] = 0;
            int removed = 0;
            while (removed < 2)
            {
                int num = rand() % 4;
                if ((num + 'A') != question->correct_option &&
                    question->options[num][0] != '\0')
                {
                    question->options[num][0] = '\0';
                    removed++;
                }
            }
            return 1;
        }
        break;
    case '2':
        if (lifeline[1])
        {
            lifeline[1] = 0;
            return 2;
        }
        break;
    default:
        printf("\nReturning to the Question.");
        break;
    }
    return 0;
}

void print_formatted_question(Question question)
{
    printf("\n\n%s", question.text);
    for (int i = 0; i < 4; i++)
    {
        if (question.options[i][0] != '\0')
        {
            printf("%c. %s", ('A' + i), question.options[i]);
        }
    }
}

int read_questions(char *file_name, Question **questions)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("\nUnable to open the questions bank.");
        exit(0);
    }
    char str[MAX_QUES_LEN];
    int no_of_lines = 0;
    while (fgets(str, MAX_QUES_LEN, file))
    {
        no_of_lines++;
    }
    int no_of_questions = no_of_lines / 8;
    *questions = (Question *)malloc(no_of_questions * sizeof(Question));
    rewind(file);
    for (int i = 0; i < no_of_questions; i++)
    {
        fgets((*questions)[i].text, MAX_QUES_LEN, file);
        for (int j = 0; j < 4; j++)
        {
            fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
        }
        char option[10];
        fgets(option, 10, file);
        (*questions)[i].correct_option = option[0];

        char timeout[10];
        fgets(timeout, 10, file);
        (*questions)[i].timeout = atoi(timeout);

        char prize_money[10];
        fgets(prize_money, 10, file);
        (*questions)[i].prize_money = atoi(prize_money);
    }
    fclose(file);
    return no_of_questions;
}
