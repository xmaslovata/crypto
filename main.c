#include <stdio.h>

typedef struct
{
    char *token;
    char *type;
    int amount;
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

typedef struct
{
    char *token;
    int  trades;
    double total_volume;
    double min_price;
    double max_price;
    double last_price;
    double sum_price;
} TokenStats;

void updateStats(TokenStats *stats, TRADE trade)
{
    stats->trades++;
    stats->total_volume += trade.amount;
    stats->sum_price += trade.price;
    stats->last_price = trade.price;
    if(stats->trades == 1)
    {
        stats->min_price = trade.price;
        stats->max_price = trade.price;
    }
    if(trade.price < stats->min_price)
        stats->min_price = trade.price;
    if(trade.price > stats->max_price)
        stats->max_price = trade.price;
}

int main(void)
{
    return 0;
}
