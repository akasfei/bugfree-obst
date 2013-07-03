typedef struct OBST_result
{
  float ** C;
  float ** W;
  int ** R;
  int n;
}OBST_result;

OBST_result OBST (float * P, float * Q, int n)
{
  int i, m, j, l, minl;
  float minC;
  OBST_result result;
  // Allocate memery for C, W, R
  float ** C = (float **)malloc( (n + 1) * sizeof(float *));
  float ** W = (float **)malloc( (n + 1) * sizeof(float *));
  int ** R = (int **)malloc( (n + 1) * sizeof(int *));

  // Init 2d arrays
  for (i = 0; i <= n; i++)
  {
    C[i] = (float *)malloc( (n + 1) * sizeof(float));
    W[i] = (float *)malloc( (n + 1) * sizeof(float));
    R[i] = (int *)malloc( (n + 1) * sizeof(int));
    for (j = 0; j <= n; j++)
    {
      C[i][j] = W[i][j] = 0;
      R[i][j] = 0;
    }
  }

  for (i = 0; i < n; i++)
  {
    // Initial values
    W[i][i] = Q[i];
    R[i][i] = 0;
    C[i][i] = 0;

    W[i][i+1] = C[i][i+1] = Q[i] + Q[i+1] + P[i+1];
    R[i][i+1] = i + 1;
  }

  W[n][n] = Q[n];
  R[n][n] = C[n][n] = 0;

  for (m = 2; m <= n; m++)
  {
    for (i = 0; i <= n-m; i++)
    {
      j = i + m;
      W[i][j] = W[i][j-1] + P[j] + Q[j];

      //Knuth conclusion
      minl = R[i][j-1];
      minC = C[i][minl-1] + C[minl][j];
      for (l = R[i][j-1]; l <= R[i+1][j]; l++)
      {
        if (minC < C[i][l-1] + C[l][j])
        {
          minC = C[i][l-1] + C[l][j];
          minl = l;
        }
      }
      /*
      for (l = R[i][j-1]; i <= R[i+1][j]; i++)
      {
        if (minC < C[i][l-1] + C[l][j])
        {
          minC = C[i][l-1] + C[l][j];
          minl = l;
        }
      }
      */

      C[i][j] = W[i][j] + C[i][minl - 1] + C[minl][j];
      R[i][j] = minl;
    }
  }

  result.C = C;
  result.W = W;
  result.R = R;
  result.n = n;

  return result;
}

void constructOBST_subtree(int i, int j, int parent, int pos, BinTreeClass * T, int** R, DataObject * obj)
{
  int t;
  if (i <= j)
  {
    t = R[i][j];
    printf("\nAdding %s child %d of %d", pos == 1 ? "left" : "right", obj[t].dataInt, obj[parent].dataInt);
    BinTreeInsert(T, pos, obj[t]);
    BinTreeSelect(T, pos);
    constructOBST_subtree(i, t - 1, t, 1, T, R, obj);
    constructOBST_subtree(t + 1, j, t, 2, T, R, obj);
  }
}

BinTreeClass* constructOBST(OBST_result src, DataObject * obj)
{
  BinTreeClass * obstree = malloc( sizeof(BinTreeClass) );
  BinTreeInit(obstree);
  int root = src.R[1][src.n];
  printf("\nBuilding root: %d", obj[root].dataInt);
  BinTreeInsert(obstree, 0, obj[root]);
  constructOBST_subtree(1, root-1, root, 1, obstree, src.R, obj);
  constructOBST_subtree(root+1, src.n, root, 2, obstree, src.R, obj);
  return obstree;
}
