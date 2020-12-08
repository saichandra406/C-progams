#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv){
  FILE * f = fopen(argv[1], "r");
  size_t n_hands = 0, fut_hands = 0;
  future_cards_t *fc = malloc(sizeof(*fc));
  deck_t **hands, **future;
  fc->n_decks = 0;
  fc->decks = NULL;
  hands = read_input(f, &n_hands, fc);
  fclose(f);
  f = fopen(argv[2], "r");
  future = read_input(f, &fut_hands, fc);
  future_cards_from_deck(future[0], fc);
  for(int i=0; i< n_hands; i++){
      print_hand(hands[i]);
      printf("\n");
      free_deck(hands[i]);
  }
  free_deck(future[0]);
  free(hands);
  free(future);
  for(size_t i=0; i < fc->n_decks; i++){
    //free only card pointers not cards in them
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  free(fc);
  fclose(f);
  return EXIT_SUCCESS;
}
