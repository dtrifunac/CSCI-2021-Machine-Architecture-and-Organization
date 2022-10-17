// Complete this main to benchmark the search algorithms outlined in
// the project specification

#include "search.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(int argc, char *argv[]){
  int run_linear_array = 0;
  int run_linkedlist_search = 0;
  int run_binary_array_search = 0;
  int run_binary_tree_search = 0;
  int repetitions = atoi(argv[3]);
  int maxpow = atoi(argv[2]);
  int minpow = atoi(argv[1]);
  int init = 1<<minpow;
  clock_t begin, end;           // Variables for timing
  double cpu_time;


  
  printf(" %10s","LENGTH");
  printf(" %10s","SEARCHES");
  // int i = 4;


  if(argc > 4){
    for(int i = 4; i < argc; i++){
      if( strcmp(argv[i],"la")==0 ){
        run_linear_array = 1;
      }
      if(strcmp(argv[i],"ll")==0){
        run_linkedlist_search = 1;
      }
      if( strcmp(argv[i],"bl")==0){
        run_binary_array_search = 1;
      }
      if(strcmp(argv[i],"bt")==0){
        run_binary_tree_search = 1;
      }
    }
    if( run_linear_array == 1){
        printf(" %10s", "array");
      }
    if(run_linkedlist_search == 1){
      printf(" %10s","list");
    }
    if( run_binary_array_search == 1){
      printf(" %10s","binary");
    }
    if(run_binary_tree_search == 1){
      printf(" %10s","tree");
    }
  }
  
  else{
    run_linear_array = 1;
    run_linkedlist_search = 1;
    run_binary_array_search = 1;
    run_binary_tree_search = 1;
    printf(" %10s", "array");
    printf(" %10s","list");
    printf(" %10s","binary");
    printf(" %10s","tree");
  }


  for(int len = init; len<(1<<maxpow); len*=2){
    printf("\n %10d %10d", len, 2*len);

    if(run_linear_array){
      int *evens_array = make_evens_array(len);
      begin = clock();
      for(int i = 0; i < repetitions; i++){
        for(int j =0; j < 2*len-1; j++){
          linear_array_search(evens_array, len, j);
        }
      }
      end = clock();
      cpu_time = (double)(end - begin)/CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      free(evens_array);
    }

    if(run_linkedlist_search){
      list_t *evens_list = make_evens_list(len);;
      begin = clock();
      for(int i = 0; i < repetitions; i++){
        for(int j =0; j < 2*len-1; j++){
          linkedlist_search(evens_list, len, j);
        }
      }
      end = clock();
      cpu_time = (double)(end - begin)/CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      list_free(evens_list);
    }

    if(run_binary_array_search){
      int *evens_array = make_evens_array(len);
      begin = clock();
      for(int i = 0; i < repetitions; i++){
        for(int j =0; j < 2*len-1; j++){
          binary_array_search(evens_array, len, j);
        }
      }
      end = clock();
      cpu_time = (double)(end - begin)/CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      free(evens_array);
    }

    if(run_binary_tree_search){
      bst_t *evens_tree = make_evens_tree(len);
      begin = clock();
      for(int i = 0; i < repetitions; i++){
        for(int j =0; j < 2*len-1; j++){
          binary_tree_search(evens_tree, len, j);
        }
      }
      end = clock();
      cpu_time = (double)(end - begin)/CLOCKS_PER_SEC;
      printf(" %10.4e", cpu_time);
      bst_free(evens_tree);
    }

    printf("\n");


  }

  

  return 0;
}
