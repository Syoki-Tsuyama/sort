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

// xを基準とした分割を作る
void partition3(int A[], int n, int x) {
  int i=0, j=n-1;
  while(1) {
    for(i=i; i<n; i++) if (A[i] >= x) break;
    for(j=j; j>=0; j--) if (A[j] < x) break;
    if (i >= j) break;
    swap(A+i, A+j);
    i++; j--;
  }
  i=0; j=n-1;
  while(1) {
    for(i=i; i<n; i++) if (A[i] > x) break;
    for(j=j; j>=0; j--) if (A[j] == x) break;
    if (i >= j) break;
    swap(A+i, A+j);
    i++; j--;
  }
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int quick_select(int A[], int n, int k){
  int pivot = A[n/2];
  partition3(A, n, pivot);
  int l, r;
  for(l=0; l<n; l++) if(A[l] >= pivot) break;
  for(r=l; r<n; r++) if(A[r] > pivot) break;
  if(l == k) return pivot;
  else if (l == 0) return k < r ? pivot : quick_select(A+r, n-r, k-r);
  else if(l < k) return quick_select(A+l, n-l, k-l);
  else return quick_select(A, l, k);
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
