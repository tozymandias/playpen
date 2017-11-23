#include <stdio.h>
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std;

class card {

public:

    card()
    {
        suit = "";
        number = "";
    };
    card(string suit_, string number_)
        : suit(suit_),
          number(number_)
    {
    };

    string suit;
    string number;
};

class deck_empty_exception: public exception
{
    virtual const char* what() const throw()
    {
        return "The deck is empty";
    }
} deck_empty_ex;

class deck {

private:

    void add_suit(string suit_name) 
    {
        for (unsigned int i = 1; i <= NUM_SUIT_CARDS; i++) {

            string tmp_num = "";
            if (i == 1) tmp_num = "A";
            else if (i == 11) tmp_num = "J";
            else if (i == 12) tmp_num = "Q";
            else if (i == 13) tmp_num = "K";
            else tmp_num = std::to_string(i);
            card* tmp_card = new card(suit_name, tmp_num); 
            cards[offset++] = *tmp_card;
        }
    };

    static const unsigned int NUM_SUIT_CARDS = 13;

    static const unsigned int NUM_MAX_CARDS = NUM_SUIT_CARDS * 4;

    unsigned int offset;

    std::array<card, NUM_MAX_CARDS> cards;

public:

    deck() 
        : cards()
    {
        // Initialize offset
        offset = 0;

        // Create deck of cards
        add_suit("HEARTS");
        add_suit("SPADES");
        add_suit("DIAMONDS");
        add_suit("CLUBS");

        // Reset offset
        offset = 0;
    };

    // template< class RandomIt >
    // void random_shuffle( RandomIt first, RandomIt last )
    // {
    //     typename std::iterator_traits<RandomIt>::difference_type i, n;
    //     n = last - first;
    //     for (i = n-1; i > 0; --i) {
    //         using std::swap;
    //         swap(first[i], first[std::rand() %
    //         (i+1)]);
    //     }
    // }
    void shuffle() 
    {
        std::random_shuffle(cards.begin()+offset, cards.end());
    };

    card deal()
    {
        if (offset >= NUM_MAX_CARDS) {
            // throw excp
            throw deck_empty_ex;
        }
        return cards[offset++];;
    };

    void reset()
    {
        offset = 0;
    };

    unsigned int get_size()
    {
        return (NUM_MAX_CARDS - offset);
    };
};

int main (int argc, char *argv[]) 
{
    cout << "Hello World!" << endl;

    // Create deck
    deck* my_deck = new deck();
    
    // Deal default
    cout << "Deal all default" << endl;
    while (my_deck->get_size()) {
        card my_card = my_deck->deal();
        cout << "Dealt card " << my_card.suit << ", " << my_card.number << endl;
    }

    // Deal expect exception
    cout << endl;
    cout << "Deal with exception" << endl;
    try {
        my_deck->deal();
    }
    catch (std::exception& e) {
        cout << e.what() << endl;
    }

    // Reset
    my_deck->reset();

    // Deal some
    cout << endl;
    cout << "Deal 5 after reset" << endl;
    for (unsigned int i = 0; i < 5; i++) {
        card my_card = my_deck->deal();
        cout << "Dealt card " << my_card.suit << ", " << my_card.number << endl;
    }

    // Shuffle rest
    cout << endl;
    cout << "Shuffle and deal rest" << endl;
    my_deck->shuffle();

    // Deal rest
    while (my_deck->get_size()) {
        card my_card = my_deck->deal();
        cout << "Dealt card " << my_card.suit << ", " << my_card.number << endl;
    }

    // Reset shuffle and deal all
    cout << endl;
    cout << "Reset shuffle and deal all" << endl;
    my_deck->reset();
    my_deck->shuffle();
    while (my_deck->get_size()) {
        card my_card = my_deck->deal();
        cout << "Dealt card " << my_card.suit << ", " << my_card.number << endl;
    }
};
