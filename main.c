#include <stdio.h>
#include <time.h>

typedef struct
{
    char *token;
    long price;
	time_t time;
} TRADE;

typedef struct TradeNode
{
    TRADE trade;
    struct TradeNode *next;
} TradeNode;

typedef struct
{
    char *token;
    int  trades;
    double last_price;
    double sum_price;
    double sum_price_sq;
} TokenStats;

typedef struct TokenNode
{
    TokenStats stats;
    TradeNode *first_trade;
	TradeNode *last_trade;
	struct TokenNode *next;
} TokenNode;

void printTrade(TRADE *trade)
{
    printf("Token: %s\n", trade->token);
    printf("Price: %ld\n", trade->price);
    printf("Time: %ld\n", trade->time);
}

double averagePrice(TokenStats *stats)
{
    if (stats->trades == 0)
        return 0;

    return stats->sum_price / stats->trades;
}

double priceVolatility(TokenStats *stats)
{
	double mean;
	double mean_sq;
	double variance;

	if(stats->trades == 0)
		return 0;

	mean = averagePrice(stats);
	mean_sq = stats->sum_price_sq / stats->trades;
	variance = mean_sq - mean * mean;

	if(variance <= 0)
		variance = 0;

	return sqrt(variance);
}

void updateStats(TokenStats *stats, TRADE *trade)
{
    stats->trades++;
    stats->sum_price += trade.price;
    stats->sum_price_sq += (double) trade.price * trade.price;
	stats->last_price = (double) trade.price;
}

void printStats(TokenStats *stats, int decimals)
{
    printf("Token: %s\n", stats->token);
    printf("Trades: %d\n", stats->trades);
	printf("Average price: %.*lf\n", decimals, averagePrice(stats));
	printf("Volatility: %.*lf\n", decimals, priceVolatility(stats));
}

void removeStats(TokenStats *stats, TRADE *trade)
{
	stats->trades--;
	stats->sum_price -= trade->price;
	stats->sum_price_sq -= (double) trade->price * trade->price;
}

int main(void)
{

    return 0;
}
