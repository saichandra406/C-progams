#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  FILE *f;
  size_t n_trials = 10000, tmp;
  size_t n_hands = 0;
  unsigned *counts; //win counts
  future_cards_t *fc = malloc(sizeof(*fc));
  deck_t **hands, *remain, *cur_winner;
  int tie = 0, res, cur_hand;

  if(!(argc == 2 || argc == 3)){
    fprintf(stderr, "Does not have 1 or 2 arguments\n");
    return EXIT_FAILURE;
  }

  f = fopen(argv[1], "r");
  if(f == NULL){
    fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  if(argc == 3){
    n_trials = atoi(argv[2]);
  }
  fc->n_decks = 0;
  fc->decks = NULL;
  hands = read_input(f, &n_hands, fc);
  fclose(f);
  counts = malloc((n_hands + 1) * sizeof(*counts));
  for(int i = 0; i < n_hands + 1; i++){
    counts[i] = 0;
  }
  remain = build_remaining_deck(hands, n_hands);
  shuffle(remain);

  //Monte-Carlo simulaiton
  for(size_t i = 1; i <= n_trials; i++){
    shuffle(remain);

    //assign cards to fc
    tmp = remain->n_cards;
    remain->n_cards = fc->n_decks;
    future_cards_from_deck(remain, fc);
    remain->n_cards = tmp;

    cur_winner = hands[0];
    cur_hand = 0;
    for(size_t j=1; j < n_hands; j++){
      res = compare_hands(cur_winner, hands[j]);
	//res > 0 , current winner does not change
	if(res < 0){
	  cur_winner = hands[j];
	  cur_hand = j;
	  tie = 0; // if tie flag previously 1
	}
        else if(res == 0){
	  tie = 1;
	}

    }

    if(!tie){
      counts[cur_hand] ++;
    }
    else{
      counts[n_hands] ++;//tie counts
    }
  }

  for(size_t i = 0; i < n_hands; i++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, counts[i],\
	   (unsigned) n_trials, (float)counts[i] * 100/ n_trials);
  }
  printf("And there were %u ties\n", counts[n_hands]);

  for(int i=0; i< n_hands; i++){
    free_deck(hands[i]);
  }
  free_deck(remain);
  free(hands);
  
  free_future_cards(fc);
  free(counts);
  
  return EXIT_SUCCESS;
}
