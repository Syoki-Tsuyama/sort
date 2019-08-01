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

void quick_sort(int A[], int n){
  // 真ん中の要素をピボットとする
  int pivot = A[n/2];
  A[n/2] = A[0];
  A[0] = pivot;
  int j; // pivotのひとつ右のindex
  int i;
  for(i = j = 1; i < n; i++) {
    if(A[i] <= pivot) {
      swap(A+i, A+j);
      j++;
    }
  }
  swap(A, A+j-1);
  if (n > 1) {
    quick_sort(A, j-1);
    quick_sort(A+j, n - j);
  }
}

/**
 * xを基準とした分割を作る
 * Aはxより小さい要素の配列Bとx以上要素の配列Cに分割される
 * @return {int} Bの要素数
 */
int partition2(int A[], int n, int x) {
  int i=0, j=n-1;
  int p, q;
  while(1) {
    for(p=i; p<n; p++) if (A[p] >= x) break;
    for(q=j; q>=0; q--) if (A[q] < x) break;
    if (p >= q) break;
    swap(A+p, A+q);
    i=p+1; j=q-1;
  }
  int l;
  for(l=0; l<n; l++) if (A[l] >= x) break;
  return l;
}

// xを基準とした分割を作る
void partition3(int A[], int n, int x) {
  int i=0, j=n-1, p, q;
  while(1) {
    for(p=i; p<n; p++) if (A[p] >= x) break;
    for(q=j; q>=0; q--) if (A[q] < x) break;
    if (p >= q) break;
    swap(A+p, A+q);
    i=p+1; j=q-1;
  }
  i=0; j=n-1;
  while(1) {
    for(p=i; p<n; p++) if (A[p] > x) break;
    for(q=j; q>=0; q--) if (A[q] == x) break;
    if (p >= q) break;
    swap(A+p, A+q);
    i=p+1; j=q-1;
  }
}

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/
int qselect(int A[], int n, int k) {
  // 真ん中の値をピボットとする
  int pivot = A[n/2];
  partition3(A, n, pivot);
  int l, r;
  for(l=0; l<n; l++) if(A[l] >= pivot) break;
  for(r=l; r<n; r++) if(A[r] > pivot) break;
  if(l == k) return pivot;
  else if (l == 0) return k < r ? pivot : qselect(A+r, n-r, k-r);
  else if(l < k) return qselect(A+l, n-l, k-l);
  else return qselect(A, l, k);
}

// クイックセレクトにより中央値を求める
int median(int A[], int n) {
  return qselect(A, n, ((n+1)/2-1));
}

/**
 * 中央値の中央値を求める
 */
int medOfMed(int A[], int n) {
  int tmp[N] = {};
  int i, j = 0;
  for(i=0; i < n; i+=5) {
    tmp[j] = median(A+i, 5 < n-i ? 5 : n-i);
    j++;
  }
  return median(tmp, j);
}

int quick_select(int A[], int n, int k){
  if (n <= 5) {
    quick_sort(A, n);
    return A[k];
  }
  int pivot = medOfMed(A, n);
  int r = partition2(A, n, pivot);
  if (r == k) return pivot;
  else if (r < k) return quick_select(A+r, n-r, k-r);
  else return quick_select(A, r, k);
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 17; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    int c = quick_select(A, N, i);
    if(c != i) printf("ERROR %d %d\n", i, c);
    printf("%d th element is %d\n", i, c);
  }
  return 0;
}
