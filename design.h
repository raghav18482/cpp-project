#pragma once
#include <iostream>
#include <windows.h>
#include<iomanip>
#include<termmgr.h>

using namespace std;
 HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);  

void line(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout <<endl<< "-----------------------------------------------------------------" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void curveLine(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout <<endl<< "=================================================================" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void getRow(string label,string value){
    cout<<"| "<<setw(15)<<setiosflags(ios::left)<<label<<"| "<<setw(25)<<setiosflags(ios::left)<<value<<" |";
    line(5);
}
void getRow(string item1,string item2,string item3,int size1=8,int size2=25,int size3=25){
    cout<<"| "<<setw(size1)<<setiosflags(ios::left)<<item1<<"| "<<setw(size2)<<setiosflags(ios::left)<<item2<<" |"<<setw(size3)<<setiosflags(ios::left)<<item3<<" |";
    line(5);
}


void setTextColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
