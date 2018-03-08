// algo_LRU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include <iostream.h>
#include <string.h>
/*void setm(int a[][],int m,int n)
{ int i,j;
for(i=0;i<n;i++)
{a[m-1][i]=1;
}
for(j=0;j<n;j++)
{a[i][m-1]=0;}
};*/
int **martrix;
int i,j;
void setm(int m,int n)
{
    for(i=0;i<n;i++)
    {
        martrix[m][i]=1;
        martrix[i][m]=0;
    }
}
char * current;
void print(int n)
{
    int p,q;
    for(p=0;p<n;p++)
    {
        for(q=0;q<n;q++)
        {
            cout<<martrix[p][q]<<" ";
        }
        cout<<"**"<<current[p];
        cout<<"\n";
    }
}
int mini(int *b)
{
    int i=0;
    int n,m,flag;
    n=0;
    while(b[i]>=0&&b[i]<=9){n++;i++;}
    m=b[0];flag=0;
    for(j=1;j<n;j++)
    {
        if(m>b[j]) {m=b[j];flag=j;}
    }
    return flag;
}
void main()
{
    int n;
    char sequence[255];
    cout<<"请输入页架数:";
    cin>>n;
    cout<<"请输入访问序列:";
    cin>>sequence;
    cout<<"*****ALL RIGHT RESERVED BY 英雄*****"<<endl;
    martrix=new int * [n];
    for( i=0;i<n;i++)
        martrix[i]=new int[n];
    current=new char [n];
    for(i=0;i<n;i++)
        current[i]=' ';
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            martrix[i][j]=0;
    int k;
    int len=strlen(sequence);
    //setm(0,n);print(n);cout<<endl;
    //setm(1,n);print(n);cout<<endl;
    //setm(2,n);print(n);
    //for(i=1;i<=len;i++)
    //{ if(i<=n) {setm(i-1,n);print(n);cout<<endl;}
    //}
    int flag;
    int f;
    int *total;
    int g;
    int count=0;
    char c;
    total=new int[n];
    for(i=0;i<n;i++)
        total[i]=0;
    for(k=1;k<=len;k++)
    {
        cout<<endl; 
        cout<<sequence[k-1]<<"要求进入"<<endl;
        if(k<=n)
        {
            current[k-1]=sequence[k-1];setm(k-1,n);print(n);cout<<"缺页"<<endl;count++;
        }
        else 
        {     for(i=0;i<n;i++)
        {      if(current[i]==sequence[k-1]) {flag=i;  break;}
        }
        if(i==n) { 
            for(f=0;f<n;f++)
            { for(g=0;g<n;g++)
            {total[f]+=martrix[f][g];}
            } 
            c=current[mini(total)];
            current[mini(total)]=sequence[k-1];
            setm(mini(total),n);print(n);cout<<"缺页,置换前一次"<<c<<"的那行"<<endl;
            cout<<endl;
            count++;
        }            
        else
        {setm(flag,n);print(n);cout<<endl;}
        }
        for(i=0;i<n;i++)
            total[i]=0;
    }
    cout<<"总共有"<<count<<"次缺页"<<endl;
    cout<<"请按任意键并回车退出"<<endl;
    cin>>c;
}