#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double get_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char** argv)
{
    srand(time(NULL)*12345);
    if (argc != 3) {
    printf("usage: %s N\n", argv[0]);
    return -1;
    }

  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  int count=0;
  double timeS=0,sumS=0,timeSS=0,sumSS=0;

  while(count<m){
      double* a = (double*)malloc(n * n * sizeof(double)); // Matrix A
      double* b = (double*)malloc(n * n * sizeof(double)); // Matrix B
      double* c = (double*)malloc(n * n * sizeof(double)); // Matrix C

  // Initialize the matrices to some values.
  int i, j, l;
  for(i=0;i<n;i++){
      for(j=0;j<n;j++){
          a[i*n+j]=(double)rand()/RAND_MAX;
          b[i*n+j]=(double)rand()/RAND_MAX;
      }
  }
  
  /*for(i=0;i<n;i++){
      for(j=0;j<n;j++){
          printf("a[%d][%d]=%lf\n",i,j,a[i*n+j]);
      }
  }
  for(i=0;i<n;i++){
      for(j=0;j<n;j++){
          printf("b[%d][%d]=%lf\n",i,j,b[i*n+j]);
      }
  }*/

  double begin = get_time();

  for(i=0;i<n;i++){
      for(j=0;j<n;j++){
          for(l=0;l<n;l++){
              c[i*n+j]+=a[i*n+l]*b[l*n+j];
          }
      }
  }

  double end = get_time();
  timeS+=end-begin;
  timeSS+=(end-begin)*(end-begin);
  //printf("time: %.6lf sec\n", end - begin);

  // Print C for debugging. Comment out the print before measuring the execution time.
  double sum = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      sum += c[i * n + j];
      //printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
    }
  }
  // Print out the sum of all values in C.
  // This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
  //printf("sum: %.6lf\n", sum);

  sumS+=sum;
  sumSS+=sum*sum;
  free(a);
  free(b);
  free(c);
  count++;
  }
  printf("time average : %.6lf\nsum average : %.6lf\n",timeS/m,sumS/m);
  //printf("time V : %lf\nsum V : %lf\n",timeSS/m-(timeS/m)*(timeS/m),sumSS/m-(sumS/m)*(sumS/m));
  return 0;
}