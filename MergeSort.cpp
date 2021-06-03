#include <iostream>
#include <cstdlib>
#include <ctime>
#include<windows.h>
using namespace std;

void user_reverse(int a[], int l, int r)
{

    int i = l;
    int j = r;
    while(i<j)
    {
        swap(a[i],a[j]);
        i++;
        j--;
    }

}

void exchange(int a[], int l, int m, int r)
{
    /*cout<<l<<" "<<m<<" "<<r<<":";
    for(int q = l; q <= r; q++)
    {
        cout<<a[q]<<" ";
    }
    cout<<"------->";*/
    user_reverse(a, l, m-1);
    user_reverse(a, m, r);
    user_reverse(a,l,r);
    /*for(int q = l; q <= r; q++)
    {
        cout<<a[q]<<" ";
    }
    cout<<endl;*/
}

void merge_in_space(int a[], int l, int m, int r)
{
    int lf = l;
    int ri = m+1;
    while((lf < ri)  && (ri <= r))
    {
        int step = 0;
        while((lf < ri) && (a[lf] <= a[ri]))
        {
            lf++;
        }
        while((ri <= r) && (a[ri] <= a[lf]))
        {
            ri++;
            step++;
        }
        exchange(a, lf, ri-step, ri-1);
        lf = lf + step;
    }
}

void mergeSort_in_place(int a[], int low, int high)
{
    if(low < high)
    {
        mergeSort_in_place(a, low, (low+high)/2);
        mergeSort_in_place(a, (low+high)/2+1, high);
        merge_in_space(a, low, (low+high)/2, high);
    }
}

void merge_with_assistant_array(int a[], int b[], int l, int m, int r)
{
    int i = l;
    int lf = l;
    int ri = m+1;
    while((lf <= m) && (ri <= r ))
    {
        if(a[lf] <= a[ri])
        {
            b[i++] = a[lf++];
        }
        else
        {
            b[i++] = a[ri++];
        }
    }
    if(lf>m)
    {
        for(int q = ri; q <= r; q++)
        {
            b[i++] = a[q];
        }
    }
    else
    {
        for(int q = lf; q <= m; q++)
        {
            b[i++] = a[q];
        }
    }
    for(int q = l; q <= r; q++)
    {
        a[q] = b[q];
    }
}
void mergeSort_with_assistant_array(int a[], int b[], int low, int high)
{
    if(low < high)
    {
        mergeSort_with_assistant_array(a, b, low, (low+high)/2);
        mergeSort_with_assistant_array(a, b, (low+high)/2+1, high);
        merge_with_assistant_array(a, b, low, (low+high)/2, high);
    }
}

int main()
{
    srand((int)time(0));
    int array_size = 100000;
    int number[array_size];
    int number1[array_size];
    int b[array_size];
    for(int i = 0; i < array_size; i++)
    {
        number[i] = rand()%array_size;
        number1[i] = number[i];
        //cout<<number[i]<<' ';
    }
    cout<<"------->原始数组,随机生成"<<array_size<<"个整数"<<endl;
    DWORD start_time = GetTickCount();
    mergeSort_with_assistant_array(number, b, 0, array_size-1);
    DWORD end_time = GetTickCount();
    /*for(int i = 0; i < array_size; i++)
    {
        cout<<number[i]<<' ';
    }*/
    cout<<"------->带辅助数组归并排序结果,运行时间为："<<end_time-start_time<<"ms"<<endl;
    DWORD start_time1 = GetTickCount();
    mergeSort_in_place(number1, 0, array_size-1);
    DWORD end_time1 = GetTickCount();
    cout<<"------->原地归并排序结果,运行时间为："<<end_time1-start_time1<<"ms"<<endl;
    int sum = 0;
    for(int i = 0; i < array_size; i++)
    {
        if(number1[i]-number[i]!=0)
        {
            sum += 1;
        }

    }
    if(sum==0)
    {
        cout<<"两种排序方法结果一致"<<endl;
    }

}

