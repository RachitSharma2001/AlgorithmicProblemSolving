// Problem link: http://codeforces.com/problemset/problem/1490/D

#include <iostream>
#include <math.h>
using namespace std;
 
class Pair{
 public:
 int x, y;
 Pair(int one, int two){
   x = one;
   y = two;
 }
};
 
class SegmentTree{
 public:
 SegmentTree(int n, int* values){
   arr = new int[(int) (n*(1+log2(n)))];
   ind_arr = new int[(int) (n*(1+log2(n)))];
   numNodes = n;
   buildSegmentTree(0, n-1, 0, values);
 }
 
 Pair buildSegmentTree(int l, int r, int arrInd, int* values){
   if(l == r){
     arr[arrInd] = values[l];
     ind_arr[arrInd] = l;
     return Pair(arr[arrInd], ind_arr[arrInd]);
   }else{
     Pair leftMax = buildSegmentTree(l, (l+r)/2, arrInd*2 + 1, values);
     Pair rightMax = buildSegmentTree((l+r)/2 + 1, r, arrInd*2 + 2, values);
     Pair max = maximum(leftMax, rightMax);
     arr[arrInd] = max.x;
     ind_arr[arrInd] = max.y;
     return max;
   }
 }
 
 Pair maxInRange(int arrInd, int l_ind, int r_ind, int target_l, int target_r){
   if(target_l > r_ind || target_r < l_ind) return Pair(-(1<<30), -1);
 
   if(target_l <= l_ind && r_ind <= target_r){
     return Pair(arr[arrInd], ind_arr[arrInd]);
   }
 
   Pair leftVal = maxInRange(arrInd*2 + 1, l_ind, (l_ind + r_ind)/2, target_l, target_r);
  
   Pair rightVal = maxInRange(arrInd*2 + 2, 1 + (l_ind + r_ind)/2, r_ind, target_l, target_r);
 
   return maximum(leftVal, rightVal);
 }
 
 int getMax(int l, int r){
   return maxInRange(0, 0, numNodes-1, l, r).y;
 }
 private:
 Pair& maximum(Pair& one, Pair& two){
   return (one.x > two.x ? one : two);
 }
 int numNodes;
 int* arr;
 int* ind_arr;
};
 
void dfs(int level, int l, int ind, int r, int* ans, SegmentTree* tree){
 if(ind < 0) return;
 ans[ind] = level;
 if(l == ind && r == ind){
   return;
 }
 int leftMaxInd = (*tree).getMax(l, ind-1);
 int rightMaxInd = (*tree).getMax(ind+1, r);
 dfs(level+1, l, leftMaxInd, ind-1, ans, tree);
 dfs(level+1, ind+1, rightMaxInd, r, ans, tree);
}
 
int main() {
 int t;
 cin >> t;
 
 int* vals;
 int* ans;
 SegmentTree* tree;
 while(t-- > 0){
   int n;
   cin >> n;
  
   vals = new int[n];
   ans = new int[n];
  
   for(int i = 0; i < n; i++){
     cin >> vals[i];
     ans[i] = 0;
   }
 
   tree = new SegmentTree(n, vals);
  
 
   dfs(0, 0, (*tree).getMax(0, n-1), n-1, ans, tree);
 
   for(int i = 0; i < n; i++) cout << ans[i] << " ";
   cout << endl;
 }
 
}

