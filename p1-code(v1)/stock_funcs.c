// stock_funcs.c: support functions for the stock_main program.

#include "stock.h"

// PROBLEM 1: Allocate a new stock struct and initialize its fields.
// Integer fields like 'count' and 'lo_index' should be initialied to
// -1.  Pointer fields like 'prices' should be initialized to
// NULL. The stock should be heap-allocated using malloc() and
// returned.  Since this is an allocation function, no use of 'free()'
// should appear.
stock_t *stock_new(){
  // WRITE ME
  stock_t *new = malloc(sizeof(stock_t));   
  new->data_file = NULL;         
  new->count =-1;                  
  new->prices = NULL;              
  new->lo_index =-1;               
  new->hi_index =-1;             
  new->best_buy =-1;                 
  new->best_sell =-1;             
  return new;
}

// PROBLEM 1: Free a stock. Check the 'data_file' and 'prices' fields:
// if they are non-NULL, then free them. Then free the pointer to
// 'stock' itself.
void stock_free(stock_t *stock){
  // WRITE ME
  if(stock->data_file != NULL || stock->prices != NULL){
    free(stock->data_file);
    free(stock->prices);
    free(stock);
  }
  return;
}

// PROBLEM 1: Prints data about a stock that is passed in via a
// pointer. Uses the syntax ptr->field to access fields of the struct
// pointed by 'stock'.  Output follows the general convention:
//
// ==STOCK DATA==
// data_file: data/stock-jagged.txt                      
// count: 15
// prices: [103.00, 250.00, 133.00, ...]
// lo_index:  8
// hi_index:  11
// best_buy:  8
// best_sell: 11
// profit:    232.00
//
// Each line prints a field of the stock_t struct. In all cases,
// floating point numbers are printed with 2 decimal digits of
// accuracy.
//
// NULLS FOR FIELDS
// The fields 'data_file' and 'prices' may be NULL in which case they
// will be printed specially as in
// 
// data_file: NULL
// prices: NULL
//
// This requires a manual if/else check for NULL values for these
// pointers.
// 
// PRICES FIELD
// When printing the 'prices' field, if the 'count' field is 0 to 3,
// print the entire array as in
//
// prices: []                        # count == 0
// prices: [70.00]                   # count == 1
// prices: [50.00, 90.00]            # count == 2
// prices: [59.00, 45.00, 103.00]    # count == 3
//
// Otherwise, print the first 3 elements with a ... at the end as in
//
// prices: [10.00, 20.00, 30.00, ...] # count > 3
//
// PROFIT
// There is no 'profit' field in the struct. Instead, calculate the
// profit as the difference between the price at the 'best_sell' index
// and 'best_buy' index.  If these indices are -1 indicating the best
// buy/sell time is not known or not viable, print a proit of 0.0
void stock_print(stock_t *stock){
  // WRITE ME
  float profit = 0.0;
  if(stock->best_buy != -1 && stock->best_sell != -1){
    profit = stock->prices[stock->best_buy] - stock->prices[stock->best_sell];
  }
  if(stock->count ==0){
    printf("data_file: %s\ncount: %d\n prices: []\nlo_index:  %d\nhi_index:  %d\nbest_buy:  %d\nbest_sell: %d\nprofit:    %2f", 
    stock->data_file, stock->count, stock->lo_index, stock->hi_index, stock->best_buy, stock->best_sell, profit);
  }
  else if(stock->count == 1){
    printf("data_file: %s\ncount: %d\n prices: [%2f]\nlo_index:  %d\nhi_index:  %d\nbest_buy:  %d\nbest_sell: %d\nprofit:    %2f", 
    stock->data_file, stock->count, stock->prices[0], stock->lo_index, stock->hi_index, stock->best_buy, stock->best_sell, profit);
  }
  else if(stock->count == 2){
    printf("data_file: %s\ncount: %d\n prices: [%2f, %2f]\nlo_index:  %d\nhi_index:  %d\nbest_buy:  %d\nbest_sell: %d\nprofit:    %2f", 
    stock->data_file, stock->count, stock->prices[0], stock->prices[1], stock->lo_index, stock->hi_index, stock->best_buy, stock->best_sell, profit);
  }
  else if(stock->count == 3){
    printf("data_file: %s\ncount: %d\n prices: [%2f, %2f, %2f]\nlo_index:  %d\nhi_index:  %d\nbest_buy:  %d\nbest_sell: %d\nprofit:    %2f", 
    stock->data_file, stock->count, stock->prices[0], stock->prices[1], stock->prices[2], stock->lo_index, stock->hi_index, stock->best_buy, stock->best_sell, profit);
  }
  else{
    printf("data_file: %s\ncount: %d\n prices: [%2f, %2f, %2f, ...]\nlo_index:  %d\nhi_index:  %d\nbest_buy:  %d\nbest_sell: %d\nprofit:    %2f", 
    stock->data_file, stock->count, stock->prices[0], stock->prices[1], stock->prices[2], stock->lo_index, stock->hi_index, stock->best_buy, stock->best_sell, profit);
  }
  return;
}


// PROBLEM 1: Sets the index of 'lo_index' and 'hi_index' fields of
// the stock to be the positions in 'prices' of the lowest and highest
// values present in it. Uses a simple loop over the array 'prices'
// which is 'count' elements long to examine each for high/low. If
// 'count' is zero, makes no changes to 'lo_index' and 'hi_index'.
void stock_set_hilo(stock_t *stock){
  // WRITE ME
  int low = stock->prices[0];
  int high = 0;
  if (stock->count == 0){
    return;
  }
  for(int i = 0; i < stock->count ; i++){
    if (stock->prices[i] < low){
      stock->lo_index = i;
    }
    if (stock->prices[i] > high){
      stock->hi_index = i;
    }
  }
  return;
}
  
// PROBLEM 2: Sets the 'best_buy' and 'best_sell' fields of 'stock'.
// This corresponds to the pair which produces the best profit. On
// determining the best buy/sell indices which produce a positive
// profit, sets these fields in 'stock' and returns 0. If there is no
// buy/sell point which would result in a positive profit, sets the
// 'best_buy' and 'best_sell' indices to -1 and returns -1. Always
// calculates the earliest buy/sell pair of indices that would get the
// best profit: if 5,8 and 5,9 and 7,10 all give the same, maximal
// profit, the best buy/sell indices are set to 5,7.
// 
// ALGORITHM NOTES
// One intuitive algorithm to compute this is to try every possible
// buy index (outer loop) and every possible sell index after it
// (inner loop) looking for the maximum profit produced in it. This is
// a O(N^2) algorithm with N=count.  Using this algorithm is a good
// start. Some MAKEUP CREDIT will be awarded for implementing a more
// efficient, O(N) algorithm here. See the specification for more details.
int stock_set_best(stock_t *stock){
  // WRITE ME
  if (stock->lo_index < stock->hi_index){
    stock->best_buy = stock->lo_index;
    stock->best_sell = stock->hi_index;
  }
  int best = 0;
  int current = 0;
  int beststart = -1;
  int bestend = -1;
  int start = 0;
  for (int end = 0; end < stock->count; end++){
    current += stock->prices[end];
    if(current > best){
      best = current;
      beststart = start;
      bestend = end;
    }
    else if(current < 0){
      start = end+1;
      current = 0;
    }
  }
  return 1;
}

// PROBLEM 2: Opens file named 'filename' and counts how many times
// the '\n' newline character appears in it which corresponds to how
// many lines of text are in it.  Makes use of either fscanf() with
// the %c format to read single characters or alternative I/O
// functions like fgetc(). Closes the file before returning a count of
// how many lines are it it.  If for any reason the file cannot be
// opened, prints a message like
//
// Could not open file 'not-there.txt'
//
// and returns -1 to indicate failure.
int count_lines(char *filename){
  // WRITE ME
  FILE *file_handle = fopen(filename, "r");
  if(file_handle == NULL){
    printf("Could not open file '%s'\n",filename);
    fclose(file_handle);
    return -1;
  }
  char c;
  int count = 0;
  while(c != EOF){
    fscanf(file_handle, "%c", &c);
    if(c == '\\'){
      fscanf(file_handle, "%c", &c);
      if(c == 'n'){
        count++;
      }
    }
  }
  fclose(file_handle);
  return count;
}

// PROBLEM 2: Loads a stock from file 'filename' into 'stock' filling
// its 'prices' and 'count' fields in. Makes use of the count_lines()
// function to determine how many lines are in the file which will
// dictate 'count' and the length of 'prices'. Allocates space in the
// heap for the stock's 'prices' array, opens the 'filename' and
// iterates through reading prices into the array. The data format for
// prices files is
//
// time_03 133.00
// time_04 143.00
// time_05 168.00
// time_06 91.00
// 
// where each line has a time as as single string and a price which is
// floating point number. The times can be ignored which can be
// accomplished with a fscanf() call with format "%*s" to read a
// string but ignore/discard it.
// 
// Assigns the 'datafile' field to be a duplicated string of
// 'filename' for which 'strdup()' is extremely useful. This string
// must be free()'d later likely in 'stock_free()'
// 
// On successfully loading the stock, returns 0.
//
// If 'filename' cannot be opened, prints the message 
// 
// Unable to open stock file 'some-stock.txt', bailing out
//
// with 'filename' substituted in for the name of the stock and
// returns -1.
int stock_load(stock_t *stock, char *filename){
  // WRITE ME
  FILE *file_handle = fopen(filename, "r");
  if(file_handle == NULL){
    printf("Unable to open stock file '%s', bailing out\n",filename);
    fclose(file_handle);
    return -1;
  }
  int *count = malloc(sizeof(int));
  *count = count_lines(filename);
  stock->count = *count;
  float num;
  for(int i =0; i < *count; i++){
    fscanf(file_handle, "%*s");
    fscanf(file_handle, "%f", &num);
    stock->prices[i] = num;
  }
  fclose(file_handle);
  free(count);
  return 1;
}

// PROBLEM 2: Plots a graphical representation of stock
// information. First calculates and prints plot which is in the
// following format:
//
// ==PLOT DATA==
// start/stop:  0 15
// max_height:  14
// price range: 309.00
// plot step:   22.07
//            +--B=S----------+
//     300.93 |    H   *      |
//     278.86 | *  H   *      |
//     256.79 | *  H   *      |
//     234.71 | *  H   *      |
//     212.64 |**  H   *      |
//     190.57 |**  H * *      |
//     168.50 |**  H** *  *  *|
//     146.43 |**  H** *  ****|
//     124.36 |**  H****  ****|
//     102.29 |**  H****  ****|
//      80.21 |** *H***** ****|
//      58.14 |** *H***** ****|
//      36.07 |** *H***** ****|
//      14.00 |****H*****L****|
//            +^----^----^----+
//             0    5    10   
// 
// Here brief notes on the format with more detail in the project
// specification.
// - Parameters start, stop, and max_height are printed first along with
//   calculated information like the price_range (uses hi_index and
//   lo_index)
// - The main body of the plot is exactly max_height characters high. The
//   lowest line is the price at lo_index; the highest is hi_index minus
//   plot_step
// - The vertical axis prices can be printed with the format specifier
//   %10.2f to give the correct leading whitespace with 2 digits of
//   accuracy
// - If the hi and lo prices appear in the range, their bar is printed
//   with an H or an L while all other stocks are printed with a *
// - The top axis may include a B and an S at the positions of the
//   best_buy and best_sell index with a = between these to show the
//   period of ownership.
// - The bottom axis shows tic marks as ^ and below them index labels at
//   values divisible by 5. For the numeric index labels, it is easiest
//   to print spaces to a value divisible by 5 then use the format
//   specifier %-5d to print integers: this aligns left and prints
//   whitespace padding on the right to width 5. In a loop, one can
//   advance by +5 each time a label is printed.
void stock_plot(stock_t *stock, int max_height, int start, int stop){
  // WRITE ME
  int high = stock->prices[stock->hi_index];
  int low =  stock->prices[stock->lo_index];
  float plot_step = (high-low)/max_height;
  printf("==PLOT DATA==\n");
  printf("start/stop:  %d %d\n", start, stop);
  printf("max_height:  %d\n", max_height);
  printf("price range: %2d\n", high-low );
  printf("plot step:   %2f\n", plot_step);
  printf("%10s + ","" );
  for(int i = 0; i < start- stop; i++){
    if(i == stock->best_buy){
      printf("B");
    }
    else if(i == stock->best_sell){
      printf("S");
    }
    if(i > stock->best_buy && i < stock->best_sell){
      printf("=");
    }
    else{
      printf("-");
    }
  }

  printf("+\n");
  
  for(int s = max_height-1; s >= 0;s--){
    float threshhold = low + plot_step*s;
    printf("%10.2f |", threshhold);
    for(int j = 0; j< start-stop; j++){
      if(stock->prices[j]>= threshhold){
        if(stock->hi_index == j){
          printf("H");
        }
        else if(stock->lo_index == j){
          printf("L");
        }
        else{
          printf("*");
        }
      }
      else{
        printf(" ");
      }
    }
    printf("|\n");
  }

  printf("%10s + ","" );
  for(int i = 0; i < start- stop; i++){
    if(i%5 ==0){
      printf("^");
    }
    else{
      printf("-");
    }
  }
  printf("+\n");
  printf("%11s","" );
  for(int i = start; i < stop; i+=5){
    if(i%5 ==0){
      printf("%d", i);
    }
    else{
      printf(" ");
    }
  }
  printf("\n");
  return;
}
}


