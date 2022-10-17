// optimized versions of matrix A^T*A operation
#include "matvec.h"
#include <stdlib.h>

int matata_VER1(matrix_t mat, matrix_t ans) {
  int numrows = mat.rows;               //number of rows
  int numcols = mat.cols;               //number of columns
  int tik = 0;                          //declare tik and mkj now so they don't need to be redeclared every loop iteration
  int mkj = 0;
  int *arr = malloc(sizeof(int)*numcols*numrows);
  int *orig = malloc(sizeof(int)*numcols*numrows);
  int counter = 0;

  for(int i = 0; i < numrows; i++){       //loads orig array with values from mat for easy sequential access
    for(int j =0; j < numcols; j++){
      orig[counter] = MGET(mat,i,j);    
      arr[counter] = 0;                   //zero out values in arr
      counter++;
    }
  }

  for(int i=0; i<numcols; i++){           //performs all the multiplication and addition to fill arr with the right values for each cell in output matrix       
    for(int j=0; j<numrows; j++){
      for(int k = 0; k<=j;k++){           //only iterates through lower triangular half of the matrix since output matrix is symetrical along diagonal
        tik = orig[i*numrows+k];
        mkj = orig[i*numrows+j];
        arr[j*numrows+k] += tik*mkj;
      }
    } 
  }

  for(int i = 0; i < numrows; i++){       //loads ans with values from arr
    for(int j =0; j < numcols; j++){
      int val = arr[i*numrows+j];
      MSET(ans,i,j,val);
      MSET(ans,j,i,val);
    }
  }



  // YOUR CODE HERE
  // vector_free_data(&vec);
  free(arr);
  free(orig);
  return 0;
}

// ADDITIONAL VERSIONS HERE

int matata_OPTM(matrix_t mat, matrix_t ans) {
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matata_VER1(mat, ans);
  // return matata_VER2(mat, ans);
}
