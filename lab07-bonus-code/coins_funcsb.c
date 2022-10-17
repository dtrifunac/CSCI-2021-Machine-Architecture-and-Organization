// #include "coinsb.h"
// // NOTE: Comment out or Uncomment the below functions as you would
// // perform `make coins_hybrid` depending on which assembly functions
// // you are working on.

// // Calculate number of quarters, dimes, nickels, pennies of
// // change. Param cents is the number of cents, 0-99. Return value
// // coins is a packed structure which will have its fields set to the
// // number of coins of each type. If cents is out of range, returns a
// // coins_t with all fields set to -1.
// coins_t set_coinsb(int cents){
//   coins_t coins;

//   if(cents < 0 || cents > 99){
//     coins.quarters = -1;
//     coins.dimes = -1;
//     coins.nickels = -1;
//     coins.pennies = -1;
//     return coins;
//   }

//   coins.quarters = cents / 25;
//   cents = cents % 25;

//   coins.dimes = cents / 10;
//   cents = cents % 10;

//   coins.nickels = cents / 5;
//   cents = cents % 5;

//   coins.pennies = cents;

//   return coins;
// }

// // Returns the total number of cents in the given coins struct.
// int total_coinsb(coins_t *coins){
//   int tot = 0;
//   tot += coins->quarters * 25;
//   tot += coins->dimes * 10;
//   tot += coins->nickels * 5;
//   tot += coins->pennies;
//   return tot;
// }
