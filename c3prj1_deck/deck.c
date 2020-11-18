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
    if((*cp)->value == c.value && (*cp)->suit == c.suit)
      return 1;
    cp++; // value also = cp[i]->value
  }
  //default else after going through all deck cards
  return 0;
}

void shuffle(deck_t * d){
  card_t *temp;
  int y;
  for ( int i = 0 ; i < d->n_cards ; i ++ ){
    y = rand()%d->n_cards;
    temp = (d->cards)[i] ;
    (d->cards)[i] = (d->cards)[y];
    (d->cards)[y] = temp;
  }
}

void assert_full_deck(deck_t * d) {
  for(unsigned i=2; i <= 14; i++)
    for (suit_t j = SPADES; j <= CLUBS; j++)
      assert(deck_contains(d, (card_t){i, j}));
}
