#include <iostream>
using namespace std;

int main(){
    // for(int i = 0 ; i<=5 ; i++ ){
    //     cout<<"*****"<<"\n";

    // }

    int r; int c;
    cout<<"no. of rows ";
    cin>>r;

    cout<<"no. of column ";
    cin>>c;
    // cout<<"give row and column"<<r<<c<<"\n";
    for (int i = 0 ;i< r; i++){
        for(int j = 0 ; j <  c ; j++ ){
            cout<<"*";
        }
        cout<<"\n";

    }

    return 0;
}