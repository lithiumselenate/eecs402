#include<iostream>
#include<cstdio>
using namespace std;
int main(){ 
    int a[10][10];
    int x;
    printf("Input start number: ");
    scanf("%d",&x);
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            a[i][j] = x + i*j;
    printf("Hello World!\n");
    for (int i=0;i<10;i++){
        for (int j=0;j<10;j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
    string s;
    cin>>s;
    cout<<"String: "<<s<<endl;
    return 0;
}