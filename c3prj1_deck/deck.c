#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t ** cp = hand->cards;// use (hand->cards) for cp
  for(size_t i=0; i < hand->n_cards; i++){
    print_card(**cp);
    printf(" ");
    cp++; //omit if used card = *cp[i]
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** cp = d->cards;
  for(size_t i = 0; i < d->n_cards; i++){
    if(*(cp)->value == c.value && *(cp)->suit == c.suit)
      return 1;
    cp++; // value also = cp[i]->value
  }
  //default else after going through all deck cards
  return 0;
}

void shuffle(deck_t * d){
   This function takes in a deck an shuffles
   it, randomly permuting the order of the cards.
   There are MANY valid ways to shuffle a deck
   of cards---we will leave the specifics
   of the algorithm design up to you.  However,
   you will want to use random() to generate
   pseudo-random numbers.  (Pseudo-random
   numbers are quite sufficient here,
   since they are not used for security
   purposes). Note that you should not need to
   use the 'srand' function.

      We will note that in trying to devise
   this algorithm, you should not
   try to shuffle a deck of cards "normally".
   Instead, you should take a small number
   of cards, and think about ways
   to shuffle them that involve using
   random numbers to swap their order,
   or pick positions for them, or
   similar principles.
}

void assert_full_deck(deck_t * d) {
  This function should check that
  the passed in deck contains ever
  valid card exactly once.  If
  the deck has any problems, this function
  should fail an assert.  This will
  be used to help you test your deck
  shuffling: we will shuffle
  a full deck, then call assert_full_deck,
  so that you can identfiy problems with
  the deck.  You can print
  any error messages you want
  if there is a problem.
  Hint: you already wrote deck_contains.

}
