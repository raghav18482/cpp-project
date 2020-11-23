// CPP program to print current date and time 
// using chronos. 
#include <chrono> 
#include <ctime> 
#include <iostream> 

using namespace std; 

int main() 
{ 
	// Here system_clock is wall clock time from 
	// the system-wide realtime clock 
	auto timenow = chrono::system_clock::to_time_t(chrono::system_clock::now()); 
    string temp=ctime(&timenow);
    string temp2[5];
    int count=0;
    int counter=0;
    cout<<temp;
    string temp3;
    for (int i = 0; i < temp.length(); i++)
    {
        if(temp[i]==' '){
            count++;
            temp2[count]=temp3;
            temp3='\0';
            counter=0;
            i++;
        }
        if(temp[i]=='\n'){
            cout<<"meow";
            cout<<i;
        }
        temp3+=temp[i];
        counter++;
    }

    for (int i = 0; i < 5; i++)
    {
        cout<<temp2[i]<<endl;
    }
    
    
    
} 
