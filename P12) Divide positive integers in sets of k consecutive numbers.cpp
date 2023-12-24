-----------------------------

P12) Divide positive integers in sets of k consecutive numbers
- Recursion

Given an array of positive integers nums and a positive integer k, check whether it is possible to divide nums into sets of k consecutive numbers.
Write a recursive function to solve this problem. 
Return true if it is possible. Otherwise, return false. 

The input has 2 lines. 
The first line is the array of positive integers nums. 
The second line is the positive integer k.

Example 1
Input:
1 2 3 3 4 5 5 6
4

Output:
false

Explanation: Array can be divided into [1,2,3,4] and [3,5,5,6]. However, [3,5,5,6] is not a set of 4 consecutive numbers.

Example 2
Input:
1 2 2 3
2

Output:
true

Explanation: Array can be divided into [1,2] and [2,3].

Example 3:
Input:
1 2 3 4 5
2

Output:
false

Explanation: Array cannot be divided into sets of size 2.

-----------------------------

#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

bool kSubsets(priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>& freq, int k){
  if (freq.empty()){
    return true;
  }

  if (freq.top().second == 0){
    freq.pop();
  }
  
  pair<int,int> currMin = freq.top();

  vector<int> tempArr;
  tempArr.push_back(currMin.first);
  
  freq.pop();
  currMin.second--;

  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> addIn;

  for (int i = 1; i < k; i++){
    pair<int,int> nextVal = freq.top();

    if (nextVal.first != currMin.first + i){
      return false;
    }
    else {
      tempArr.push_back(nextVal.first);
      nextVal.second--;               
      freq.pop();                   
      if (nextVal.second != 0){          
        addIn.push(nextVal);             
      } 
    }
  }

  if (currMin.second != 0) {
      freq.push(currMin);
  }
  
  pair<int,int> curr;
  while (!addIn.empty()){
    curr = addIn.top();
    freq.push(curr);
    addIn.pop();
  }

  return kSubsets(freq, k);
}

bool isPossible(priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>& freq, int pqSize, int k){
  if (pqSize % k != 0 ){
    return false;
  }
  return kSubsets(freq, k);
}



int main() {

  priority_queue<int, vector<int>, greater<int>> pq;

  int k;
  int element;
  int pqSize = 0;

  string str;
  getline(cin, str);
  stringstream s(str);

  
  while (s >> element)
	{
		pq.push(element);
    pqSize++;
	}

  cin >> k;

priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> freq;

  int curr;
  int currEl;
  int count = 0;

  while (!pq.empty()){
    curr = pq.top();
    currEl = pq.top();
    
    while(currEl == curr && !pq.empty()){
      count++;
      pq.pop();
      currEl = pq.top();
    }
    freq.push(make_pair(curr, count));
    count = 0;
  }

  bool result = isPossible(freq, pqSize, k);
  if (result){
    cout << "true";
  }
  else {
    cout << "false";
  }

  return 0;
}
