#include <stdio.h>

typedef struct
{
    char *token;
    char *type;
    int amount;
    double price;
    int time;
} TRADE;

void printTrade(TRADE *trade)
{
    printf("Token: %s\n", trade->token);
    printf("Type: %s\n", trade->type);
    printf("Amount: %d\n", trade->amount);
    printf("Price: %.2lf\n", trade->price);
    printf("Time: %d\n", trade->time);
}

double averagePrice(TokenStats *stats)
{
    if (stats->trades == 0)
        return 0;

    return stats->sum_price / stats->trades;
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

void printStats(TokenStats *stats)
{
    printf("Token: %s\n", stats->token);
    printf("Trades: %d\n", stats->trades);
    printf("Total volume: %.2lf\n", stats->total_volume);
    printf("Min price: %.2lf\n", stats->min_price);
    printf("Max price: %.2lf\n", stats->max_price);
    printf("Last price: %.2lf\n", stats->last_price);
    printf("Sum price: %.2lf\n", stats->sum_price);
}

typedef struct TokenNode
{
    TokenStats stats;
    struct TokenNode *next;
} TokenNode;

int main(void)
{

    return 0;
}
