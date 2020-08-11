#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>
#include <iterator>
using namespace std;

void minimum(int *array, int *tid, int *size, int *result)
{
  int first = *tid * 2;
  int second = first + 1;
  
  /* for odd test, the last number gets missed
    out, so extra comparison */
  if (second == *size - 2)
    if (*result > array[second + 1]){
      *result = array[second + 1];
      return;
    }


  // Check pair, compare small with prev small (arr[0])
  if (array[first] > array[second]){
    if (array[second] < *result)
      *result = array[second];
  }else{
    if (array[first] < *result)
      *result = array[first];
  }
}

void maximum(int *array, int *tid, int *size, int *result)
{
  int first = *tid * 2;
  int second = first + 1;
  
  /* for odd test, the last number gets missed
    out, so extra comparison */
  if (second == *size - 2)
    if (*result < array[second + 1]){
      *result = array[second + 1];
      return;
    }

  // Check pair, compare big with prev big (arr[0])
  if (array[first] < array[second]){
    if (array[second] > *result)
      *result = array[second];
  }else{
    if (array[first] > *result)
      *result = array[first];
  }
}

void summation(int *array, int *tid, int *size, int *result)
{
  int first = *tid * 2;
  int second = first + 1;
  
  if(*tid == 0){
    *result += array[first] + array[second];
    return;
  }

  if (second == *size - 2){
    *result += array[second + 1];
    return;
  }

  *result += array[first] + array[second];
}

void average(int *array, int *tid, int *size, double *result)
{
  int first = *tid * 2;
  int second = first + 1;

  if (second == *size - 2){
    *result = (*result + array[second + 1]) / 2;
    return;
  }

  *result = (*result + (array[first] + array[second]) / 2) / 2;
}

void standardDeviation(int *array, int *tid, int *size, float *xBar, double *result)
{
  int first = *tid * 2;
  int second = first + 1;

  if(*tid == 0){
    *result = pow(array[first] - *xBar, 2) + pow(array[second] - *xBar, 2);
    return;
  }

  if (second == *size - 2){
    *result +=  pow(array[second + 1] - *xBar, 2);
    return;
  }

  *result += pow(array[first] - *xBar, 2) + pow(array[second] - *xBar, 2);
}

int main()
{
  int n;
  int RANG = 1000;
  int minCPU = 1001;
  int maxCPU = 0;
  int sumCPU = 0;

  cin >> n;
  int array[n];

  for (int i = 0; i < n; i++)
  {
    cin >> array[i];

    if (array[i] > maxCPU)
      maxCPU = array[i];

    if (array[i] < minCPU)
      minCPU = array[i];

    sumCPU += array[i];
  }

  int arraySize = n * sizeof(int);

  clock_t start = clock();

  //*************** Store array in pointer ****************/
  int *arrPointer;
  arrPointer = (int *)malloc(arraySize);
  arrPointer = array;

  //*************** Minimum operation ********************/
  int minResult = 10000;

  for (int i = 0; i < n / 2; i++)
  {
    minimum(arrPointer, &i, &n, &minResult);
  }

  printf("The minimum of the array CPU :: %d", minCPU);
  printf("\nThe minimum of the array GPU :: %d \n", minResult);

  //*************** Maximum operation ********************/
  int maxResult = 0;

  for (int i = 0; i < n/2 ; i++)
  {
    maximum(arrPointer, &i, &n, &maxResult);
  }

  printf("\nThe maximum of the array CPU :: %d", maxCPU);
  printf("\nThe maximum of the array GPU :: %d\n", maxResult);

  //*************** Summation operation ********************/
  int sumResult = 0;

  for (int i = 0; i < n / 2; i++)
  {
    summation(arrPointer, &i, &n, &sumResult);
  }

  printf("\nThe summation of the array CPU :: %d", sumCPU);
  printf("\nThe summation of the array GPU :: %d\n", sumResult);

  //*************** Average operation ********************/
  double avgResult = 0;

  for (int i = 0; i < n / 2; i++)
  {
    average(arrPointer, &i, &n, &avgResult);
  }

  printf("\nThe average of the array CPU :: %d", sumCPU / n);
  printf("\nThe average of the array GPU :: %lf\n", avgResult);

  //*************** Summation operation ********************/
  double result = 0;
  float xBar = (float) sumCPU / n;

  for (int i = 0; i < n / 2; i++)
  {
    standardDeviation(arrPointer, &i, &n, &xBar, &result);
  }

  printf("\nThe standard deviation of the array GPU :: %lf\n", sqrt(result / n));



  clock_t end = clock();
  printf("\n\nThe time taken :: %lf s \n", (double)(end - start) / CLOCKS_PER_SEC);

  return 0;
}
