#include<iostream>
#include<cstdio>
#include<fstream>
#include<sys/stat.h>
#include<sys/types.h>
#include<bits/stdc++.h>
#include<conio.h>
#include<unistd.h>
using namespace std;
int makeFolder(string firstName, string lastName, string action){
        string foldername="data/"+action+"/"+firstName+lastName;
        mkdir(foldername.c_str());
}