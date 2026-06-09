#include <stdio.h>

typedef struct
{
    char *token;
    char *type;
    double price;
    int time;
} TRADE;

void print_trade(TRADE *trade)
{
    printf("Token: %s\n", trade->token);
    printf("Type: %s\n", trade->type);
    printf("Price: %lf\n", trade->price);
    printf("Time: %d\n", trade->time);
}

int main(void)
{
    return 0;
}
