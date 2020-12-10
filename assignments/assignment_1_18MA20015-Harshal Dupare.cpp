#include <iostream>
using namespace std;

int main()
{
    // counting the number of primes beteen 2 & n ( both inclusive )
    
    // I have used int here hence need to take care that inputs dont overflow
    // int can be changed to long to increase the range
    
    // give the input n here, n > 1
    int n=100; 
    
    // to store the number of primes encounted so far, hence 0 at start
    int count=0; 
    
    // i loops from 2 to n 
    for (int i=2; i<n+1; i++) 
    {
        // a bool variable to store if the number i is prime or not 
        // at start we assume that it is prime hence true
        bool isprime=true;
        
        // d only needs to loop from 2 to sqrt(i) as if none of them devide i then i is surely prime
        for(int d=2; d*d<=i; d++)
        {
            if(i%d==0)
            {
                // as d divides i, i is not a prime
                isprime=false;
                
                // no need to loop for other numbers as i is not prime
                break;
            }
        }
        
        // if the number i is prime we add 1 to the count
        if(isprime)
        {
            count++;
        }
    }

    // printing the count of number of primes between 2 and n
    cout<<"Number of primes between 2 and "<<n<<" is "<<count<<endl;
    
    return 0;
}