#include<iostream>
#include<vector>      
#include<chrono>
#include<algorithm>
#include<random>

#include<ska/hashtable.hpp>
#include<boost/sort/pdqsort/pdqsort.hpp>

using namespace std;
using namespace ska;

#define nl "\n"
#define ll "long long"
#define print(x) for (auto i : x) cout<<i<<" ";cout<<nl;
#define all(x) x.begin(), x.end()

void fast_io(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); //cout.tie(0);
    #ifndef ONLINE_JUDGE 
    freopen("INPUT.txt", "r", stdin); 
    freopen("OUTPUT.txt", "w", stdout); 
    #endif 
}

void array_shuffle(int a[], int n){
    shuffle(a, a+n, default_random_engine(0));
}

const int n = 500000000;
int a[n];

void array_generator(){
    fast_io();
    int var;
    int minn = -100000;
    int maxx = 100000;
    srand(static_cast<unsigned int>(time(0))); 
    for (int i = 0; i < n; ++i){
        var = (rand()%(maxx-minn+1)) + minn;
        a[i] = var;
    }   
}

void ORIGINAL_algorithm(int a[], int n){
    boost::sort::pdqsort(a, a+n);
}

void MODIFIED_algorithm(int a[], int size){
    int var, k = 0;
    vector<int> unique;
    flat_hash_map<int,int> hashtable; 
    
    for (int i = 0; i < size; ++i)
        hashtable[a[i]]++;
    for (auto &i : hashtable)
        unique.emplace_back(i.first);
    
    boost::sort::pdqsort(all(unique));
    
    for(int i : unique){
        var = hashtable[i];
        while(var--){
            a[k] = i;
            k++;
        }
    }
}   

int32_t main(){
    
    array_generator();

    sort(a,a+n);
    reverse(a,a+n);
   
    cout<<"input size = "<<n<<nl;
    
    double start_t3 = double(clock())/CLOCKS_PER_SEC;
    ORIGINAL_algorithm(a, n);
    double end_t4 = double(clock())/CLOCKS_PER_SEC;
    cout<<"original = "<<(end_t4 - start_t3)<<" s\n";
  
    reverse(a,a+n);
    
    double start_t1 = double(clock())/CLOCKS_PER_SEC;
    MODIFIED_algorithm(a, n);
    double end_t2 = double(clock())/CLOCKS_PER_SEC;
    cout<<"modified = "<<(end_t2 - start_t1)<<" s\n";
    
    
    cout<<(end_t4 - start_t3)/(end_t2 - start_t1)<<" times faster\n";
    cout<<"\nOVERALL RUNTIME = "<<(double(clock())/CLOCKS_PER_SEC)<<" ms";
    
}




