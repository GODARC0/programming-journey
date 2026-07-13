#include <iostream>
using namespace std;


int main(){
// sum   
    int i=0;
    int n;
    int count;
    cout<<"give a number: ";
    cin>>n;
    int sum =0;
    while (count <=n)
    {
        cout<<count<<" ";
        count++;

    }
    cout<<"\n";



    for (int i = 1; i <= n; i++)
    {
         sum = sum+i;
        if (i>=10){
            break;
        }
        
    }
    cout<<"\n";
    cout<<"sum is :"<<sum;

    while( i <= n){
        break;  //turent loop se bahar
        sum=sum+i;
        i++;
        
    }
    



    for (int i = 0; i <= n ; i++){
        if (i%2!=0)
        {
            // cout<< i<<"+";
            sum += i;
        }
        
    }



    while (i<=n){
        if (i%2!=0)
        {
            sum = sum+i;
            
        }
        i++;
    }
    cout<<"\n";
    cout<<"sum of odd no. is :"<<sum;




//prompting again and again until getting right input
     string a;
    do
    {
       
        cout<<"give me 5: ";
        cin>>a;
    } while (a != "5");

    //identifying prime
    int prime;
    cout<<"enter a number: ";
    cin>>prime;
// ye logic galat hai kyuki itteration thik se nahi ho rahi to badhi values check  nahi ho pa rahi..
    for(int i = 2 ; i<prime ; i++){
        if(prime%i==0){
            cout<<prime<<" is not a prime number";

        }
        else{
            cout<<prime<<" is a prime number.";
            
        }
        return 0;
    }



    //this method is much better


     bool isPrime = true;

    for (int i = 2; i*i < prime; i++) {
        if (prime % i == 0) {
            isPrime = false;
            break;
        }
    }

    if (isPrime == true)
        cout << prime << " is a prime number";
    else
        cout << prime << " is not a prime number";

    return 0;

}