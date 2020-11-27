#pragma once
#include <iostream>
#include <windows.h>
#include<iomanip>

using namespace std;

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


void setTextColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
