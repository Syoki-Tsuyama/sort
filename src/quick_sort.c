#include <stdio.h>

// 素数
#define N 2999

int A[N];

// *p と *q の値を入れ替える関数
void swap(int *p, int *q){
  int tmp;
  tmp = *p;
  *p = *q;
  *q = tmp;
}

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
  if (n == 0) return ;
  // 真ん中の要素をピボットとする
  int pivot = A[n/2];

  int l=0, r=n-1;
  int i=l, j=r;
  while(1) {
    for(i=l; i < n ; i++) {
      if (A[i] >= pivot) {
        break;
      }
    }
    l = i;

    for(j=r; j >= 0; j--) {
      if (A[j] <= pivot) {
        break;
      }
    }
    r = j;

    if (l >= r) break;
    swap(A + l, A + r);
    l++; r--;
  }
  if (n > 1) {
    quick_sort(A, i);
    quick_sort(A+i, n-i);
  }
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
