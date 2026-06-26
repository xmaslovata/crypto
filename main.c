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

TokenNode *findToken(TokenNode *list, char *token)
{
	TokenNode *node;

	node = list;

	while(node != NULL)
	{
		if(strcmp(node->stats.token, token) == 0)
			return node;

	node = node->next;
	}

	return NULL;
}

TokenNode *newToken(char *token)
{
    TokenNode *node;

    node = malloc(sizeof(TokenNode));

    if(node == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(ALLOCATION_ERROR);
    }

    node->stats.token = malloc(strlen(token) + 1);

    if(node->stats.token == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(ALLOCATION_ERROR);
    }

    strcpy(node->stats.token, token);

    node->stats.trades = 0;
    node->stats.last_price = 0;
    node->stats.sum_price = 0;
    node->stats.sum_price_sq = 0;

    node->first_trade = NULL;
    node->last_trade = NULL;
    node->next = NULL;

    return node;
}

void addTrade(TokenNode **list, TRADE *trade)
{
    TokenNode *node;
    TradeNode *trade_node;

    node = findToken(*list, trade->token);

    if(node == NULL)
    {
        node = newToken(trade->token);
        node->next = *list;
        *list = node;
    }

    updateStats(&node->stats, trade);

    trade_node = malloc(sizeof(TradeNode));

    if(trade_node == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(ALLOCATION_ERROR);
    }

    trade_node->trade = *trade;
    trade_node->trade.token = node->stats.token;
    trade_node->next = NULL;

    if(node->last_trade == NULL)
        node->first_trade = trade_node;
    else
        node->last_trade->next = trade_node;

    node->last_trade = trade_node;
}

void removeOldTrades(TokenNode **list, time_t now, int window_seconds)
{
    TokenNode *node;
    TokenNode *prev;
    TokenNode *next_node;
    TradeNode *old_trade;

    prev = NULL;
    node = *list;

    while(node != NULL)
    {
        while(node->first_trade != NULL && now - node->first_trade->trade.time >= window_seconds)
        {
            old_trade = node->first_trade;

            removeStats(&node->stats, &old_trade->trade);

            node->first_trade = old_trade->next;

            if(node->first_trade == NULL)
                node->last_trade = NULL;

            free(old_trade);
        }

        next_node = node->next;

        if(node->stats.trades == 0)
        {
            if(prev == NULL)
                *list = next_node;
            else
                prev->next = next_node;

            freeToken(node);
        }
        else
            prev = node;

        node = next_node;
    }
}

int nextRemovalWait(TokenNode *list, time_t now, int window_seconds)
{
    TokenNode *node;
    int wait;
    int found;
    int candidate;

    found = 0;
    wait = 0;

    for(node = list; node != NULL; node = node->next)
    {
        if(node->first_trade == NULL)
            continue;

        candidate = (int) (node->first_trade->trade.time + window_seconds - now);

        if(candidate < 0)
            candidate = 0;

        if(!found || candidate < wait)
        {
            wait = candidate;
            found = 1;
        }
    }

    if(!found)
        return -1;

    return wait;
}


int main(void)
{

    return 0;
}
