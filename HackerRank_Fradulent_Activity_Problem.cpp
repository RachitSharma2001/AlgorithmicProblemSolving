// Link: https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

void remove_val(multiset<double>& m, double element){
  multiset<double>::iterator iter = m.lower_bound(element);

  m.erase(iter);
}

int main(){
  int n, d;
  cin >> n >> d;

  double* exp = new double[n];
  double* first_half = new double[d];
  for(int i = 0; i < n; i++){
    cin >> exp[i];
    if(i < d) first_half[i] = exp[i];
  }

  sort(first_half, first_half + d);

  multiset<double> left_set;
  for(int i = 0; i < d/2; i++){
    left_set.insert(first_half[i]);
  }

  multiset<double> right_set;
  for(int i = d/2 + (d%2); i < d; i++){
    right_set.insert(first_half[i]);
  }

  
  double median = 0;

  if(d % 2 == 0){
    median = (*(left_set.rbegin()) + *(right_set.begin()))/2;
  }else{
    median = first_half[d/2];
  }
  
  //cout << left_set.size() << " " << right_set.size() << " " << median << endl;

  int ans = 0;
  for(int j = d; j < n; j++){
    if(exp[j] >= median*2){
      ans += 1;
    }

    if(j == n-1) break;

    double removed_val = exp[j - d];
    double added_val = exp[j];

    if(d % 2 == 1){
      if(added_val < median){
        left_set.insert(added_val);
      }else{
        right_set.insert(added_val);
      }

      if(removed_val < median){
        remove_val(left_set, removed_val);
      }else if(removed_val > median){
        remove_val(right_set, removed_val);
      }else{
        median = -1;
      }

      if(left_set.size() < right_set.size()){
        double save_median = median;

        median = *right_set.begin();

        remove_val(right_set, *right_set.begin());

        if(save_median != -1){
          left_set.insert(save_median);
        }
      }else if(right_set.size() < left_set.size()){
        double save_median = median;

        median = *left_set.rbegin();

        remove_val(left_set, *left_set.rbegin());

        if(save_median != -1){
          right_set.insert(save_median);
        } 
      }
    }else{
      if(removed_val < median){
        remove_val(left_set, removed_val);
      }else{
        remove_val(right_set, removed_val);
      }
      
      if(left_set.size() < right_set.size()){
        if(added_val > *right_set.begin()){
          right_set.insert(added_val);
          int extract = *right_set.begin();
          remove_val(right_set, extract);
          left_set.insert(extract);
        }else{
          left_set.insert(added_val);
        }
      }else{
        if(added_val < *left_set.rbegin()){
          left_set.insert(added_val);
          int extract = *left_set.rbegin();
          remove_val(left_set, extract);
          right_set.insert(extract);
        }else{
          right_set.insert(added_val);
        }
      }

      median = (*(left_set.rbegin()) + *(right_set.begin()))/2;
    }
    //cout << left_set.size() << " " << right_set.size() << " " << median << endl;
  }

  cout << ans << endl;
}

//7 3 3 7 2 2 3 4 8
// 8 5 8 2 11 15 7 6 5 11
// 8 4 8 2 11 15 7 6 5 11