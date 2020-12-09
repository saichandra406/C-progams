#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"

int isEmptyCard(card_t * p){
  if(p->suit == 0 && p->value == 0)
    return 1;
  else
    return 0;
}

void copyCard(card_t * dest, card_t * src){
  dest->suit = src->suit;
  dest->value = src->value;
}

void add_future_card(future_cards_t * fc, size_t index, card_t * ptr){
  deck_t * cur_deck;
  if(fc == NULL){
    fc = malloc(sizeof(*fc));
    fc->n_decks = 0;
    fc->decks = NULL;
  }
  if(fc->n_decks <= index){
    fc->decks = realloc(fc->decks, (index + 1) * sizeof(*fc->decks));
    fc->n_decks = index + 1;
    fc->decks[index].n_cards = 0;
    fc->decks[index].cards = NULL;
  }
  cur_deck = &fc->decks[index];
  cur_deck->n_cards++;
  cur_deck->cards = realloc(cur_deck->cards, \
			   cur_deck->n_cards * sizeof(*cur_deck->cards));
  cur_deck->cards[cur_deck->n_cards - 1] = ptr;
}

void replace_future_card(future_cards_t * fc, size_t index, card_t * ptr) {
  deck_t cur_deck = fc->decks[index];
  if(cur_deck.n_cards > 0){
    //current cards are not replaced.
    for(size_t j = 0; j < cur_deck.n_cards; j++){
      copyCard(cur_deck.cards[j], ptr);
    }
  }
  //if its not empy card do nothing
}

void future_cards_from_deck(deck_t * deck, future_cards_t * fc){
  if(deck == NULL || fc == NULL){
    fprintf(stderr, "passed NULL arguments\n");
  }
  else if(deck->n_cards != fc->n_decks){
    fprintf(stderr, "cards: %lu, decks: %lu. unequal lengths\n",\
	    deck->n_cards, fc->n_decks);
  }
  else{
    for(size_t i = 0; i < deck->n_cards; i++){
      replace_future_card(fc, i,deck->cards[i]);
    }
  }
}
