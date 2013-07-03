#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"
#include "models.h"
#include "bintree.h"
#include "coreio.h"
#include "obst.h"

void printMatrix(void ** target, int n, int isint)
{
  int i, j, ** _this;
  float ** _fthis;
  if (isint)
  {
    _this = (int **) target;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        printf("%d\t", _this[i][j]);
      printf("\n");
    }
  } else {
    _fthis = (float **) target;
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        printf("%.4f\t", _fthis[i][j]);
      printf("\n");
    }
  }

}

int main()
{
  DataObject * objects = readData("data.txt");
  //float p[] = {0, 3.0/16, 3.0/16, 1.0/16, 1.0/16}, q[] = {2.0/16, 3.0/16, 1.0/16, 1.0/16, 1.0/16};
  float p[] = {0, 0.5, 0.1, 0.05}, q[] = {0.15, 0.1, 0.05, 0.05};
  OBST_result result = OBST(p, q, 3);
  BinTreeClass *obstree = constructOBST(result, objects);
  printf("Printing C:\n");
  printMatrix((void **)result.C, 4, 0);
  printf("Printing W:\n");
  printMatrix((void **)result.W, 4, 0);
  printf("Printing R:\n");
  printMatrix((void **)result.R, 4, 1);
  printf("OBST has been constructed.\n");
  return 0;
}
