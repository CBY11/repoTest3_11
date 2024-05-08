#include<stdio.h>
#include<iostream.h>
using namespace std;
bool isTrue(unsigned short x , unsigned short y)
{
  if(x +y<x)
  return false;
  return true;
}
int main()
{
  unsigned short x;
  unsigned short y;
  x=65535;
  y=65536;
  cout<<isTrue(x,y);
}
