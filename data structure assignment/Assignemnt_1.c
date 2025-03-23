#include<stdio.h>
#include<limits.h>
//function to find the max value in the array------------------------
int find_max(int arr[], int size)
{
    int max_val= arr[0];
    for(int i=1;i<size;i++)
    {
        if(arr[i] > max_val)
        {
            max_val= arr[i];
        }
    }
    return max_val;
}
//function to find the min value in the array----------------------
int find_min(int arr[], int size)
{
    int min_val= INT_MAX;
    for(int i=0;i<size;i++)
    {
        if(arr[i]>0 && arr[i]<min_val)
        {
            min_val=arr[i];
        }
    }
    return min_val;
}
int main(){
    //input size from user--------------------
    int size;
    printf("Enter the size of the array:");
    scanf("%d", &size);
    //for positive int------------------
    int arr[size];
    printf("Enter positive integers:\n");
    for(int i=0;i<size;i++)
    {
        do{
            scanf("%d",&arr[i]);
            if(arr[i]<=0)
            {
                printf("Please enter a positive integer: ");
            }
        }while(arr[i]<=0);
    }
    int iter=0;
    while(1){
        int max_val=find_max(arr, size);
        if(max_val == 0)
        {
            break;
        }
        int min_val=find_min(arr,size);
        for(int i=0;i<size;i++)
        {
            if(arr[i]==max_val)
            {
                arr[i]=max_val%min_val;
                break;
            }
        }
        iter++;
    }
    printf("Number of iterations: %d\n",iter);
    return 0;
}