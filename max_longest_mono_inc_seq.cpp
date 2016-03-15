 
// 最长递增子序列
#include<iostream>
#include<stack>
#include<vector>
 
using namespace std;
 
int main(){

   // int arr[]={1,9,3,8,11,4,5,6,4,1,9,7,1,7};
    int arr[] = {1, 5, 8, 2, 3, 4};
    int len = sizeof(arr)/sizeof(int);
    vector<int> vec(&arr[0],&arr[len]);
 
    vector<int> monoseqlen(len,1);
    vector<int> preindex(len,-1);
    int maxmonoseqlen=-1;
    int maxmonoindex=-1;
 
    for(int i=1;i<len;i++){
        int curr=vec[i];
        for(int j=0;j<i;j++){
            if(vec[j]<vec[i]){
                int msl=monoseqlen[j]+1;
                if(msl>monoseqlen[i]){
                    monoseqlen[i]=msl;
                    preindex[i]=j;
                }
            }
        }
    }
 
    for(int i=0;i<len;++i){
        if(monoseqlen[i]>maxmonoseqlen){
            maxmonoseqlen=monoseqlen[i];
            maxmonoindex=i;
        }
    }
 
    stack<int> st;
    while(maxmonoindex>=0){
        st.push(vec[maxmonoindex]);
        maxmonoindex=preindex[maxmonoindex];
    }
 
    vector<int> rect;
    while(!st.empty()){
        rect.push_back(st.top());
        st.pop();
    }   
 
    vector<int>::iterator itr=rect.begin();
    while(itr!=rect.end()){
        cout<<*itr++<<"\t";
    }
    cout<<endl;
    return 0;
}
