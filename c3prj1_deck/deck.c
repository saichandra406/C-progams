#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  if(hand != NULL){
    card_t ** cp = hand->cards;// use (hand->cards) for cp
    for(size_t i=0; i < hand->n_cards; i++){
      print_card(**cp);
      printf(" ");
      cp++; //omit if used card = *cp[i]
    }
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

void add_card_to(deck_t * deck, card_t c){
  deck->n_cards++;
  deck->cards = realloc(deck->cards, deck->n_cards * sizeof(*deck->cards));
  deck->cards[deck->n_cards - 1] = malloc(sizeof(**deck->cards));
  deck->cards[deck->n_cards - 1]->value = c.value;
  deck->cards[deck->n_cards - 1]->suit = c.suit;
}

card_t * add_empty_card(deck_t * deck){
  card_t empty_c = {0,0};
  add_card_to(deck, empty_c);
  return deck->cards [deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * ans = malloc(sizeof(*ans));
  card_t cur_c;
  ans->n_cards = 0;
  ans->cards = NULL;
  int no_exclusion = 0;
  if(excluded_cards == NULL || excluded_cards->n_cards == 0)
    no_exclusion = 1;

  for(unsigned i=0; i < 52; i++){
    cur_c = card_from_num(i);
    if(no_exclusion || !deck_contains(excluded_cards, cur_c)){
      add_card_to(ans, cur_c);
    }
  }
  free_deck(excluded_cards);
  return ans;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * exclude = malloc(sizeof(*exclude));
  deck_t * cur_hand = NULL;
  exclude->n_cards = 0;
  exclude->cards = NULL;
  for(size_t i = 0; i < n_hands; i++){
    cur_hand = hands[i];
    if(cur_hand == NULL){
      continue;
    }
    for(size_t j = 0; j < cur_hand->n_cards; j++){
      add_card_to(exclude, *(cur_hand->cards[j]));
    }
  }
  return make_deck_exclude(exclude);
}

void free_deck(deck_t * deck) {
  if(deck != NULL){
    for(size_t i = 0; i < deck->n_cards; i++){
      free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
  }
}
