// Project Euler 54. Poker hands.
//
// In the card game poker, a hand consists of five cards and are ranked, from
// lowest to highest, in the following way:
//
// High Card: Highest value card.
// One Pair: Two cards of the same value.
// Two Pairs: Two different pairs.
// Three of a Kind: Three cards of the same value.
// Straight: All cards are consecutive values.
// Flush: All cards of the same suit.
// Full House: Three of a kind and a pair.
// Four of a Kind: Four cards of the same value.
// Straight Flush: All cards are consecutive values of same suit.
// Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
// The cards are valued in the order:
// 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.
//
// If two players have the same ranked hands then the rank made up of the
// highest value wins; for example, a pair of eights beats a pair of fives
// (see test 1 below). But if two ranks tie, for example, both players
// have a pair of queens, then highest cards in each hand are compared (see
// test 4 below); if the highest cards tie then the next highest cards
// are compared, and so on.
//
// The file, poker.txt, contains one-thousand random hands dealt to two players.
// Each line of the file contains ten cards (separated by a single space): the
// first five are Player 1's cards and the last five are Player 2's cards. You
// can assume that all hands are valid (no invalid characters or repeated
// cards), each player's hand is in no specific order, and in each hand there
// is a clear winner.
//
// How many hands does Player 1 win?
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// Read cards from a space-delimited file of cards.
//
// Each card is a "2H" format, value + suit.
//
// \param filename: Name of file.
// \return: deck of cards as vector of strings.
std::vector<std::string> read_cards_from_file(std::string filename)
{
    std::vector<std::string> v;
    std::ifstream ifs(filename);
    while (ifs.good())
    {
        std::string s;
        ifs >> s;
        if (!s.empty())
        {
            v.push_back(std::move(s));
        }
    }
    return v;
}

// Number value for cards. Valid range: [2 - 14].
//
// Possible values:
//  - 2-10: Number value
//  - 11: Jack
//  - 12: Queen
//  - 13: King
//  - 14: Ace
using CardValue = int16_t;

constexpr int16_t CARD_VALUE_ACE = 14;

// Sort a vector by frequency, then value, in descending order.
//
// Examples:
//   {1, 2, 3, 4, 5} -> {5, 4, 3, 2, 1} // Unique values, simply descend.
//   {1, 2, 1, 2, 1} -> {1, 1, 1, 2, 2} // Three 1s come before two 2s.
//   {1, 4, 5, 9, 5} -> {5, 5, 9, 4, 1} // Two 5s beat single digits.
//
// \param card_values: Values of cards. Modified in-place to be sorted in
//                     descending order.
void frequency_sort_descending(std::vector<CardValue> &card_values)
{
    struct ValCount
    {
        int16_t val;
        uint8_t count;
    };
    std::vector<ValCount> val_counts;
    for (const auto val : card_values)
    {
        auto it = std::find_if(val_counts.begin(), val_counts.end(), [=](const auto &vc) {
            return val == vc.val;
        });
        if (it == val_counts.end())
        {
            ValCount vc = {val, 1};
            val_counts.push_back(vc);
        }
        else
        {
            it->count += 1;
        }
    }
    std::sort(val_counts.begin(), val_counts.end(), [](const auto &vc1, const auto &vc2) {
        if (vc1.count > vc2.count)
        {
            return true;
        }
        return vc1.count == vc2.count && vc1.val > vc2.val;
    });
    size_t i = 0;
    for (const auto &vc : val_counts)
    {
        for (size_t count = 0; count < vc.count; ++count)
        {
            card_values.at(i++) = vc.val;
        }
    }
    assert(i == card_values.size());
}

// Get string from a vector of types that are supported by ostringstream::operator<<()
template <class T>
std::string vec_to_string(const std::vector<T> v)
{
    std::ostringstream oss;
    oss << '{';
    for (const auto i : v)
    {
        oss << i << ',';
    }
    oss << "\b}";
    return oss.str();
}

int test_frequency_sort_descending()
{
    struct TestCase
    {
        std::vector<CardValue> vals;
        std::vector<CardValue> expected;
    };
    TestCase testCases[] = {
        {{}, {}},
        {{2}, {2}},
        {{2, 3}, {3, 2}},
        {{2, 2}, {2, 2}},
        {{3, 2}, {3, 2}},
        {{0, 1, 1}, {1, 1, 0}},
        {{1, 2, 1}, {1, 1, 2}},
        {{1, 2, 3}, {3, 2, 1}},
        {{3, 2, 1}, {3, 2, 1}},
        {{3, 3, 3}, {3, 3, 3}},
        {{5, 5, 6, 7, 10}, {5, 5, 10, 7, 6}},
        {{2, 3, 8, 8, 10}, {8, 8, 10, 3, 2}},
        {{5, 8, 9, 10, 14}, {14, 10, 9, 8, 5}},
        {{2, 9, 14, 14, 14}, {14, 14, 14, 9, 2}},
        {{9, 10, 10, 9, 14}, {10, 10, 9, 9, 14}},
        {{3, 3, 3, 9, 9}, {3, 3, 3, 9, 9}},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        auto actual = tc.vals;
        frequency_sort_descending(actual);
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(vals: " << vec_to_string(tc.vals) << ")"
                      << ", expected: " << vec_to_string(tc.expected)
                      << ", actual: " << vec_to_string(actual) << "\n";
        }
    }
    return num_fails;
}

// Rank of a poker hand.
enum class Rank
{
    high_card,
    one_pair,
    two_pairs,
    three_of_a_kind,
    straight,
    flush,
    full_house,
    four_of_a_kind,
    straight_flush,
    royal_flush,
};

// Information about a poker hand, useful for determining which hand wins.
struct PokerHandInfo
{
    Rank rank = Rank::high_card;

    // Card values, sorted descended fist by frequency (4 of a kind, 3 of a
    // kind, etc), then by value. Suitable for breaking a tie in rank.
    std::vector<CardValue> card_values;
};

constexpr bool operator<(const PokerHandInfo &p1, const PokerHandInfo &p2)
{
    if (static_cast<int>(p1.rank) < static_cast<int>(p2.rank))
    {
        return true;
    }
    return p1.rank == p2.rank && p1.card_values < p2.card_values;
}

int test_poker_hand_info_lt()
{
    struct TestCase
    {
        PokerHandInfo p1;
        PokerHandInfo p2;
        bool expected;
    };
    TestCase testCases[] = {
        {{Rank::one_pair, {5, 5, 13, 7, 6}}, {Rank::one_pair, {8, 8, 10, 3, 2}}, true},
        {{Rank::high_card, {14, 11, 9, 8, 5}}, {Rank::high_card, {12, 8, 7, 5, 2}}, false},
        {{Rank::three_of_a_kind, {14, 14, 14, 9, 2}}, {Rank::flush, {11, 9, 8, 5, 2}}, true},
        {{Rank::flush, {11, 9, 8, 5, 2}}, {Rank::three_of_a_kind, {14, 14, 14, 9, 2}}, false},
        {{Rank::one_pair, {12, 12, 9, 6, 4}}, {Rank::one_pair, {12, 12, 7, 6, 3}}, false},
        {{Rank::full_house, {4, 4, 4, 2, 2}}, {Rank::full_house, {3, 3, 3, 9, 9}}, false},
        {{Rank::one_pair, {8, 8, 10, 3, 2}}, {Rank::one_pair, {8, 8, 10, 3, 2}}, false},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = tc.p1 < tc.p2;
        if (tc.expected != actual)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(p1: " << vec_to_string(tc.p1.card_values)
                      << ", p2: " << vec_to_string(tc.p2.card_values) << ")"
                      << ", expected: " << tc.expected
                      << ", actual: " << actual << "\n";
        }
    }
    return num_fails;
}

// Get card value from card.
//
// \param card: string representing a card. E.g. "2H"
// \return: CardValue of card.
CardValue get_value_from_card(std::string card)
{
    switch (card.at(0))
    {
    case 'T':
        return 10;
    case 'J':
        return 11;
    case 'Q':
        return 12;
    case 'K':
        return 13;
    case 'A':
        return CARD_VALUE_ACE;
    default:
        break;
    }
    const CardValue card_value = card.at(0) - '0';
    assert(card_value >= 2 && card_value <= CARD_VALUE_ACE);
    return card_value;
}

// Get card values from cards.
std::vector<CardValue> get_card_values(std::vector<std::string> cards)
{
    std::vector<CardValue> card_values;
    for (const auto card : cards)
    {
        card_values.emplace_back(get_value_from_card(card));
    }
    return card_values;
}

// True if cards are all the same suit.
bool cards_are_flush(const std::vector<std::string> &cards)
{
    if (cards.empty())
    {
        return false;
    }

    const char suit = cards[0].at(1);
    const std::string valid_suits = "CDHS";
    assert(valid_suits.find(suit) != std::string::npos);
    return std::all_of(cards.begin() + 1, cards.end(), [=](const auto &card) {
        return suit == card.at(1);
    });
}

// True if a straight for descending cards.
bool card_values_are_straight(const std::vector<CardValue> &card_values)
{
    for (size_t i = 0; i + 1 < card_values.size(); ++i)
    {
        if (card_values.at(i) != card_values.at(i + 1) + 1)
        {
            return false;
        }
    }
    return true;
}

// Get poker hand scoring information for a hand.
//
// \param hand: 5 cards as "2H" strings.
// \return: Poker hand scoring information.
PokerHandInfo get_poker_hand_info(std::vector<std::string> cards)
{
    assert(cards.size() == 5);
    PokerHandInfo phi;
    phi.card_values = get_card_values(cards);
    frequency_sort_descending(phi.card_values);
    const bool is_flush = cards_are_flush(cards);
    const bool is_straight = card_values_are_straight(phi.card_values);
    if (is_flush && is_straight)
    {
        if (phi.card_values.front() == CARD_VALUE_ACE)
        {
            phi.rank = Rank::royal_flush;
            return phi;
        }
        else
        {
            phi.rank = Rank::straight_flush;
            return phi;
        }
    }
    if (phi.card_values[0] == phi.card_values[1])
    {
        if (phi.card_values[0] == phi.card_values[2])
        {
            if (phi.card_values[0] == phi.card_values[3])
            {
                phi.rank = Rank::four_of_a_kind;
                return phi;
            }
            if (phi.card_values[3] == phi.card_values[4])
            {
                phi.rank = Rank::full_house;
                return phi;
            }
        }
    }
    if (is_flush)
    {
        phi.rank = Rank::flush;
        return phi;
    }
    if (is_straight)
    {
        phi.rank = Rank::straight;
        return phi;
    }
    if (phi.card_values[0] == phi.card_values[1])
    {
        if (phi.card_values[0] == phi.card_values[2])
        {
            phi.rank = Rank::three_of_a_kind;
            return phi;
        }
        if (phi.card_values[2] == phi.card_values[3])
        {
            phi.rank = Rank::two_pairs;
            return phi;
        }
        phi.rank = Rank::one_pair;
        return phi;
    }
    phi.rank = Rank::high_card;
    return phi;
}

int test_get_poker_hand_info()
{
    struct TestCase
    {
        std::vector<std::string> cards;
        Rank expected;
    };
    TestCase testCases[] = {
        {{"4H", "5C", "6S", "7S", "KD"}, Rank::high_card},
        {{"5H", "5C", "6S", "7S", "KD"}, Rank::one_pair},
        {{"7H", "5C", "6S", "7S", "6D"}, Rank::two_pairs},
        {{"7H", "5C", "6S", "7S", "7D"}, Rank::three_of_a_kind},
        {{"KH", "QC", "TS", "JS", "9D"}, Rank::straight},
        {{"2H", "QH", "TH", "JH", "9H"}, Rank::flush},
        {{"7H", "7C", "6S", "7S", "6D"}, Rank::full_house},
        {{"7H", "7C", "6S", "7S", "7D"}, Rank::four_of_a_kind},
        {{"KC", "QC", "TC", "JC", "9C"}, Rank::straight_flush},
        {{"KC", "QC", "TC", "JC", "AC"}, Rank::royal_flush},
    };
    int num_fails = 0;
    for (const auto &tc : testCases)
    {
        const auto actual = get_poker_hand_info(tc.cards);
        if (tc.expected != actual.rank)
        {
            ++num_fails;
            std::cerr << "FAIL, " << __FUNCTION__ << "(cards: " << vec_to_string(tc.cards) << ")"
                      << ", expected: " << static_cast<int>(tc.expected)
                      << ", actual: " << static_cast<int>(actual.rank)
                      << ", actual card values: " << vec_to_string(actual.card_values) << "\n";
        }
    }
    return num_fails;
}

int main()
{
    const auto cards = read_cards_from_file("p054_poker.txt");
    assert(cards.size() == 10'000);
    int num_player_one_wins = 0;
    for (size_t i = 0; i < cards.size(); i += 10)
    {
        std::vector<std::string> hand1(cards.begin() + i, cards.begin() + i + 5);
        std::vector<std::string> hand2(cards.begin() + i + 5, cards.begin() + i + 10);
        if (get_poker_hand_info(hand2) < get_poker_hand_info(hand1))
        {
            ++num_player_one_wins;
        }
    }
    std::cout << num_player_one_wins << "\n";

    const int num_fails = test_frequency_sort_descending() + test_poker_hand_info_lt() + test_get_poker_hand_info();
    return num_fails == 0 ? 0 : 1;
}
