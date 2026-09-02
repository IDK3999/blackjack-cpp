#include <vector>

using namespace std;

// Groups card ranks into 10 buckets: 0=Ace, 1..8 = values 2..9, 9 = value 10 (10/J/Q/K)
static int rankBucket(int card){
    int rank = card % 13;
    return rank >= 9 ? 9 : rank;
}

// Counts remaining (undealt) cards per rank bucket, using the global `deck` tracker
static void remainingRankCounts(int counts[10], int &totalRemaining){
    for(int i = 0; i < 10; i++) counts[i] = 0;
    totalRemaining = 0;
    for(int card = 0; card < 52; card++){
        if(deck[card]) continue;
        counts[rankBucket(card)]++;
        totalRemaining++;
    }
}

// Recursively computes the dealer's final outcome distribution: probability of
// busting, and probability of finishing on each total from 17 to 21
static void dealerDistRecursive(vector<int> hand, int counts[10], int totalRemaining,
                                 double prob, double p17to21[5], double &bust){
    int total = calculateHand(hand);
    if(total > 21){ bust += prob; return; }
    if(total >= 17){ p17to21[total - 17] += prob; return; }
    if(totalRemaining == 0) return; // no cards left to resolve the hand (shouldn't happen)

    for(int bucket = 0; bucket < 10; bucket++){
        if(counts[bucket] == 0) continue;
        double childProb = prob * counts[bucket] / totalRemaining;
        vector<int> newHand = hand;
        newHand.push_back(bucket);
        int newCounts[10];
        for(int i = 0; i < 10; i++) newCounts[i] = counts[i];
        newCounts[bucket]--;
        dealerDistRecursive(newHand, newCounts, totalRemaining - 1, childProb, p17to21, bust);
    }
}

static void dealerDistribution(int dealerUpCard, int counts[10], int totalRemaining,
                                double p17to21[5], double &bust){
    for(int i = 0; i < 5; i++) p17to21[i] = 0.0;
    bust = 0.0;
    dealerDistRecursive({dealerUpCard}, counts, totalRemaining, 1.0, p17to21, bust);
}

// Expected value (win=+1, lose=-1, tie=0) of standing right now with playerTotal
static double standEV(int playerTotal, const double p17to21[5], double bust){
    double ev = bust; // dealer busts => win
    for(int total = 17; total <= 21; total++){
        double p = p17to21[total - 17];
        if(playerTotal > total) ev += p;
        else if(playerTotal < total) ev -= p;
        // equal totals are a tie, contributing 0
    }
    return ev;
}

// Expected value of hitting once, then standing on whatever total results
static double hitOnceEV(const vector<int> &hand, int dealerUpCard, int counts[10], int totalRemaining){
    if(totalRemaining == 0) return -1.0;
    double ev = 0.0;
    for(int bucket = 0; bucket < 10; bucket++){
        if(counts[bucket] == 0) continue;
        double prob = static_cast<double>(counts[bucket]) / totalRemaining;
        vector<int> newHand = hand;
        newHand.push_back(bucket);
        int newTotal = calculateHand(newHand);
        if(newTotal > 21){
            ev += prob * -1.0;
            continue;
        }
        int newCounts[10];
        for(int i = 0; i < 10; i++) newCounts[i] = counts[i];
        newCounts[bucket]--;
        double p17to21[5];
        double bust;
        dealerDistribution(dealerUpCard, newCounts, totalRemaining - 1, p17to21, bust);
        ev += prob * standEV(newTotal, p17to21, bust);
    }
    return ev;
}

// Returns 1 if the player should stand, 0 if the player should hit, comparing the
// expected value of standing now against hitting once, using the cards played so far
int shouldStand(const vector<int> &playerHand, int dealerUpCard){
    int playerTotal = calculateHand(playerHand);
    if(playerTotal >= 21) return 1;

    int counts[10];
    int totalRemaining;
    remainingRankCounts(counts, totalRemaining);

    double p17to21[5];
    double bust;
    dealerDistribution(dealerUpCard, counts, totalRemaining, p17to21, bust);
    double standNow = standEV(playerTotal, p17to21, bust);
    double hitNow = hitOnceEV(playerHand, dealerUpCard, counts, totalRemaining);

    return standNow >= hitNow ? 1 : 0;
}
