#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

deck_t * hand_from_string(const char * str, future_cards_t * fc){
  size_t idx = 0;
  int count = 0, tmp;
  deck * ans = NULL;
  card_t *p;
  char * sub;

  ans = malloc(sizeof(*ans));
  ans->cards = NULL;
  ans->n_cards = 0;
  stripNewLine(str);
  while((sub = strtok(str + idx, " ")) != NULL){
    count++;
    tmp = strlen(sub);
    idx = tmp + 1;
    if(sub[0] == '?'){
      tmp = atoi(sub+1);//index in fc
      p = add_empty_card(ans);
      add_future_card(fc, idx, p);
    }
    else{
      add_card_to(ans, card_from_letters(sub[0], sub[1]));
    }
  }
  return ans;
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc){

  char * line = NULL;
  size_t sz = 0;
  deck_t ** ans = NULL;
  while(getline(&line, &sz, f) > 0){
    ans = realloc(ans, (*n_hands + 1) * sizeof(*ans));
    ans[*n_hands] = hand_from_string(line , fc);
    *n_hands = *n_hands + 1;
  }
  free(line);
  return ans;
}
