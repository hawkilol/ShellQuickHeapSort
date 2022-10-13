#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int getBig(int *a, int i, int right, int pivot)
{
    for (int k = i; k <= right; k++)
    {
        if (a[k] > pivot)
            return k;
    }
    return right + 1;
}

int getSmall(int *a, int j, int left, int pivot)
{
    for (int k = j; k >= left; k--)
    {
        if (a[k] < pivot)
            return k;
    }
    return -1;
}

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void random_quick(int *a, int left, int right)
{
    if (left >= right)
        return;
    int index = left + (rand() % (right - left)), i = left, j = right;
    int pivot_index = index;
    int pivot = a[index];
    i = getBig(a, i, right, pivot);
    j = getSmall(a, j, left, pivot);
    while (i <= j)
    {
        swap(&a[i], &a[j]);
        i = getBig(a, i, right, pivot);
        j = getSmall(a, j, left, pivot);
    }

    if (pivot_index > j && pivot_index > i)
    {
        swap(&a[i], &a[pivot_index]);
        random_quick(a, left, i - 1);
        random_quick(a, i + 1, right);
    }
    else if (pivot_index < j && pivot_index < i)
    {
        swap(&a[j], &a[pivot_index]);
        random_quick(a, left, j - 1);
        random_quick(a, j + 1, right);
    }
    else
    {
        
        random_quick(a, left, pivot_index - 1);
        random_quick(a, pivot_index + 1, right);
    }
}

  


//heapsort
 


//void swap(int* a, int* b)
//{
 
//    int temp = *a;
 
//    *a = *b;
 
//    *b = temp;
//}
 
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    if (left < N && arr[left] > arr[largest])
 
        largest = left;
    if (right < N && arr[right] > arr[largest])
 
        largest = right;
    if (largest != i) {
 
        swap(&arr[i], &arr[largest]);
 
        heapify(arr, N, largest);
    }
}
 

void heapSort(int arr[], int N)
{
 
    // max heap
    for (int i = N / 2 - 1; i >= 0; i--)
 
        heapify(arr, N, i);
 
    // Heap sort
    for (int i = N - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}


//shellsort

void shellSort(int array[], int n) {
  // Rearrange elements at each n/2, n/4, n/8, ... intervals
  for (int interval = n / 2; interval > 0; interval /= 2) {
    for (int i = interval; i < n; i += 1) {
      int temp = array[i];
      int j;
      for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
        array[j] = array[j - interval];
      }
      array[j] = temp;
    }
  }
}

int main(){
  FILE *fpt;
  int n = 10000;
  int arr1[n];
  double timesShell[n];
  double timesQuick[n];
  double timesHeap[n];
  for(int i = 0; i < n; i++){
    timesShell[i] = 0;
    timesQuick[i] = 0;
    timesHeap[i] = 0;

  }

  int arr[n];

  clock_t start;
  clock_t stop;
  double end;
  
  for(int i = 0; i<n; i++){
    arr1[i] = rand()%10000;
    //arr1[i] = 1;
    printf("%d\n", arr1[i]);
  }
  //Ja ordenado !
  //random_quick(arr1, 0, n-1);
  //reverse
  int temp;
  //for(int i = 0; i<n/2; i++){
  //    temp = arr1[i];
  //    arr1[i] = arr1[n-i-1];
  //    arr1[n-i-1] = temp;
  //    printf("%d\n", arr1[i]);
  //}
  
  int avgCount = 10;

  for(int k = 0; k < avgCount; k++){

    for(int i = 0; i<n; i++){

      for(int j = 0; j<i; j++){
        arr[j] = arr1[j];
      }

      start = clock();

    
      random_quick(arr, 0, i -1);
      stop = clock();

      end = (double) (stop - start) / CLOCKS_PER_SEC;
      timesQuick[i] = timesQuick[i] + end;

      for(int j = 0; j<i; j++){
        arr[j] = arr1[j];
      }
      start = clock();
      shellSort(arr, i);
      stop = clock();
    
      end = (double) (stop - start) / CLOCKS_PER_SEC;
      timesShell[i] = timesShell[i] + end;
    
      for(int j = 0; j<i; j++){
        arr[j] = arr1[j];
      }
      start = clock();
    
      heapSort(arr,i);
      stop = clock();
    
      end = (double) (stop - start) / CLOCKS_PER_SEC;
      timesHeap[i] = timesHeap[i] + end;

      printf("%d\n", i);

    }
    
    
  }
  //double avgShell[n];
  //double avgQuick[n];
  //double avgHeap[n];
  

  for(int i = 0; i<n; ++i){
    timesShell[i] = timesShell[i] / avgCount;
    timesQuick[i] = timesQuick[i] / avgCount;
    timesHeap[i] = timesHeap[i] / avgCount;
  }

  

  fpt = fopen("TimeSorts.csv", "w+");
  fprintf(fpt,"Shell,Quick,Heap\n");
    for(int i = 0; i<n; i++){
      fprintf(fpt,"%f,%f,%f\n", timesShell[i], timesQuick[i], timesHeap[i]);
    }

  fclose(fpt);
}
