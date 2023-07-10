/* 罗思佳 2021201679 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */

#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 32)
    {
        int i,j,m,n,a1,a2,a3,a4,a5,a6,a7,a8;
        for(i = 0; i < N; i += 8)
          for(j = 0; j < M; j += 8)
          {
            if(i != j)
            {
              for(m = i; m < i+8; m++)
               for(n = j; n < j+8; n++)
                  B[n][m] = A[m][n];  
            }
            else
            {
              for(m = i; m < i+8; m++)
              {
                a1 = A[m][j];
                a2 = A[m][j+1];
                a3 = A[m][j+2];
                a4 = A[m][j+3];
                a5 = A[m][j+4];
                a6 = A[m][j+5];
                a7 = A[m][j+6];
                a8 = A[m][j+7];

                B[j][m] = a1;
                B[j+1][m] = a2;
                B[j+2][m] = a3;
                B[j+3][m] = a4;
                B[j+4][m] = a5;
                B[j+5][m] = a6;
                B[j+6][m] = a7;
                B[j+7][m] = a8;

              }
              
            }  
          }        

    }
    else if(M == 64)
    {
        int i,j,m,n,a1,a2,a3,a4,a5,a6,a7,a8;
        for(i = 0; i < N; i += 8)
          for(j = 0; j < M; j += 8)
          {
            for(m = i; m < i+4; m++)//处理前四行
            {
              a1 = A[m][j];
              a2 = A[m][j+1];
              a3 = A[m][j+2];
              a4 = A[m][j+3];
              a5 = A[m][j+4];
              a6 = A[m][j+5];
              a7 = A[m][j+6];
              a8 = A[m][j+7];

              B[j][m] = a1;
              B[j+1][m] = a2;
              B[j+2][m] = a3;
              B[j+3][m] = a4;
              B[j][m+4] = a5;
              B[j+1][m+4] = a6;
              B[j+2][m+4] = a7;
              B[j+3][m+4] = a8;
            }
            for(n = j; n < j + 4; n++)//逐行进行后4行前四列的转置
            {
              a1 = A[i+4][n];
              a2 = A[i+5][n];
              a3 = A[i+6][n];
              a4 = A[i+7][n];

              a5 = B[n][i+4];
              a6 = B[n][i+5];
              a7 = B[n][i+6];
              a8 = B[n][i+7];

              B[n][i+4] = a1;
              B[n][i+5] = a2;
              B[n][i+6] = a3;
              B[n][i+7] = a4;

              B[n+4][i] = a5;
              B[n+4][i+1] = a6;
              B[n+4][i+2] = a7;
              B[n+4][i+3] = a8;
            }
            for(m = i+4; m < i+8; m++)//进行后四行后四列的转置
            {
              a1 = A[m][j+4];
              a2 = A[m][j+5];
              a3 = A[m][j+6];
              a4 = A[m][j+7];

              B[j+4][m] = a1;
              B[j+5][m] = a2;
              B[j+6][m] = a3;
              B[j+7][m] = a4;
            }

          }
    }
    else
    {
       int step = 18;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];
        
       }
    }
    
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

char trans_try1_desc[] = "try1";//32:343; 64:4723
void trans_try1(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 32)//343
    {
       int i,j,m,n;
       for( i = 0; i < N; i+=8)
         for(j = 0; j < M; j+=8)
           for(m = i; m < i+8; m++)
             for(n = j; n < j+8; n++)
                 B[n][m] = A[m][n];
    }
    else if(M == 64)//4723
    {
       int i,j,m,n;
       for( i = 0; i < N; i+=8)
         for(j = 0; j < M; j+=8)
           for(m = i; m < i+8; m++)
             for(n = j; n < j+8; n++)
                 B[n][m] = A[m][n];
    }
  
}

char trans_try2_desc[] = "try2";//32:287; 64:1699
void trans_try2(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 32)//287
    {
       int i,j,m,n,a1,a2,a3,a4,a5,a6,a7,a8;
        for(i = 0; i < N; i += 8)
          for(j = 0; j < M; j += 8)
          {
            if(i != j)
            {
              for(m = i; m < i+8; m++)
               for(n = j; n < j+8; n++)
                  B[n][m] = A[m][n];  
            }
            else
            {
              for(m = i; m < i+8; m++)
              {
                a1 = A[m][j];
                a2 = A[m][j+1];
                a3 = A[m][j+2];
                a4 = A[m][j+3];
                a5 = A[m][j+4];
                a6 = A[m][j+5];
                a7 = A[m][j+6];
                a8 = A[m][j+7];

                B[j][m] = a1;
                B[j+1][m] = a2;
                B[j+2][m] = a3;
                B[j+3][m] = a4;
                B[j+4][m] = a5;
                B[j+5][m] = a6;
                B[j+6][m] = a7;
                B[j+7][m] = a8;

              }
              
            }  
          }
    }
    else if(M == 64)//4分块
    {
    int i, j, k, a1, a2, a3, a4;
		for (i = 0; i < M; i += 4)
			for(j = 0; j < M; j += 4)
				for(k = i; k < (i + 4); ++k)
				{
					a1 = A[k][j];
					a2 = A[k][j+1];
					a3 = A[k][j+2];
					a4 = A[k][j+3];
					B[j][k] = a1;
					B[j+1][k] = a2;
					B[j+2][k] = a3;
					B[j+3][k] = a4;
				}
    }
}

char trans_try3_desc[] = "try3";// 64:1651
void trans_try3(int M, int N, int A[N][M], int B[M][N])
{
    if(M == 64)
    {
        int i,j,m,n,a1,a2,a3,a4;
        for(i = 0; i < N; i += 8)
          for(j = 0; j < M; j += 4)
          {
            if(j-i != 0 && j-i != 4)
            {
              for(m = i; m < i+8; m++)
               for(n = j; n < j+4; n++)
                  B[n][m] = A[m][n];
            }
            else
            {
              for(m = i; m < i+8; m++)
              {
                a1 = A[m][j];
                a2 = A[m][j+1];
                a3 = A[m][j+2];
                a4 = A[m][j+3];

                B[j][m] = a1;
                B[j+1][m] = a2;
                B[j+2][m] = a3;
                B[j+3][m] = a4;
              }


            }


          }      
          
    }
}


char trans_try4_desc[] = "try4";
void trans_try4(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 4;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try5_desc[] = "try5";
void trans_try5(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 5;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try6_desc[] = "try6";
void trans_try6(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 6;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try7_desc[] = "try7";
void trans_try7(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 7;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try8_desc[] = "try8";
void trans_try8(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 8;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try9_desc[] = "try9";
void trans_try9(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 9;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try10_desc[] = "try10";
void trans_try10(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 10;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try11_desc[] = "try11";
void trans_try11(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 11;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try12_desc[] = "try12";
void trans_try12(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 12;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try13_desc[] = "try13";
void trans_try13(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 13;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try14_desc[] = "try14";
void trans_try14(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 14;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try15_desc[] = "try15";
void trans_try15(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 15;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try16_desc[] = "try16";
void trans_try16(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 16;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try17_desc[] = "try17";
void trans_try17(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 17;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try18_desc[] = "try18";
void trans_try18(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 18;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try19_desc[] = "try19";
void trans_try19(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 19;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

char trans_try20_desc[] = "try20";
void trans_try20(int M, int N, int A[N][M], int B[M][N])
{
  if(M == 61)
    {
      int step = 20;
      int i,j,m,n;
      for(i = 0; i < N; i+=step)
       for(j = 0; j < M; j += step)
       {
        int min_1 = (i+step) > N ? N : (i+step);
        int min_2 = (j+step) > M ? M : (j+step);  
        for(m = i; m < min_1; m++)
           for(n = j; n < min_2;n++)
             B[n][m] = A[m][n];   
       } 
    }
}

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}


/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    //registerTransFunction(trans_try1, trans_try1_desc);
    //registerTransFunction(trans_try2, trans_try2_desc); 
    //registerTransFunction(trans_try3, trans_try3_desc);
  /*
    registerTransFunction(trans_try4, trans_try4_desc); 
    registerTransFunction(trans_try5, trans_try5_desc);
    registerTransFunction(trans_try6, trans_try6_desc);
    registerTransFunction(trans_try7, trans_try7_desc);
    registerTransFunction(trans_try8, trans_try8_desc);
    registerTransFunction(trans_try9, trans_try9_desc);
    registerTransFunction(trans_try10, trans_try10_desc);
    registerTransFunction(trans_try11, trans_try11_desc);
    registerTransFunction(trans_try12, trans_try12_desc);
    registerTransFunction(trans_try13, trans_try13_desc);
    registerTransFunction(trans_try14, trans_try14_desc);
    registerTransFunction(trans_try15, trans_try15_desc);
    registerTransFunction(trans_try16, trans_try16_desc);
    registerTransFunction(trans_try17, trans_try17_desc);
    registerTransFunction(trans_try18, trans_try18_desc);
    registerTransFunction(trans_try19, trans_try19_desc);
    registerTransFunction(trans_try20, trans_try20_desc);
  */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

