#include <stdio.h>
//function to input employee ids and salary
void input_details(int n,int empid[],int salary[]) 
{
    printf("Enter the employee id:");
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&empid[i]);
    }
    printf("Enter the salary:");
    for(int i=0;i<n;i++) 
    {
        scanf("%d",&salary[i]);
    }
}

//function for bubble sort---------------------------
void bubble_sort(int n, int empid[], int salary[]) 
{
    int swap=0,comparison=0;
    int bubble_empid[n], bubble_salary[n];
    //use another temporary array for sorting------------------
    for (int i=0;i<n;i++) 
    {
        bubble_empid[i]= empid[i];
        bubble_salary[i]= salary[i];
    }
    for (int i=0;i<n-1;i++) 
    {
        for (int j=0;j<n-i-1;j++) 
        {
            comparison++;
            if (bubble_salary[j] < bubble_salary[j + 1] ||
                (bubble_salary[j] == bubble_salary[j + 1] && bubble_empid[j] < bubble_empid[j + 1])) 
                {
                //swap salary and employee id---------------
                int temp_salary= bubble_salary[j];
                bubble_salary[j]= bubble_salary[j + 1];
                bubble_salary[j+1]= temp_salary;
                int temp_empid= bubble_empid[j];
                bubble_empid[j]= bubble_empid[j + 1];
                bubble_empid[j+1]= temp_empid;
                swap++;
            }
        }
    }
    printf("Bubble sort output: ");
    for(int i=0;i<n;i++) 
    {
        printf("%d ",bubble_empid[i]);
    }
    printf("\nSwap:%d,Comparison: %d\n",swap,comparison);
}
//function to perform Selection Sort------------------
void selection_sort(int n,int empid[],int salary[]) 
{
    int swap=0, comparison=0;
    int selection_empid[n], selection_salary[n];
    //copy original data to temporary arrays for sorting------------
    for (int i=0;i<n;i++) 
    {
        selection_empid[i]= empid[i];
        selection_salary[i]= salary[i];
    }
    for (int i=0;i<n-1;i++) 
    {
        int max_idx= i;
        for (int j=i+1;j<n;j++) 
        {
            comparison++;
            if (selection_salary[j] > selection_salary[max_idx] ||
                (selection_salary[j] == selection_salary[max_idx] && selection_empid[j] > selection_empid[max_idx])) 
                {
                max_idx = j;
            }
        }
        if (max_idx != i) 
        {
            //swap salary and employee ids----------------
            int temp_salary= selection_salary[i];
            selection_salary[i]= selection_salary[max_idx];
            selection_salary[max_idx]= temp_salary;
            int temp_empid= selection_empid[i];
            selection_empid[i]= selection_empid[max_idx];
            selection_empid[max_idx]= temp_empid;
            swap++;
        }
    }
    printf("Selection sort output:");
    for (int i=0;i<n;i++) 
    {
        printf("%d",selection_empid[i]);
    }
    printf("\nSwap: %d,Comparison: %d\n",swap,comparison);
}
//function to perform Insertion Sort---------------------
void insertion_sort(int n, int empid[], int salary[]) {
    int swap= 0, comparison= 0;
    int insertion_empid[n],insertion_salary[n];
    //use another temporary array for sorting---------------
    for(int i = 0; i < n; i++) 
    {
        insertion_empid[i]= empid[i];
        insertion_salary[i]= salary[i];
    }
    for(int i=1;i<n;i++) 
    {
        int temp_empid= insertion_empid[i];
        int temp_salary= insertion_salary[i];
        int j=i-1;
        while (j >= 0 && (insertion_salary[j] < temp_salary ||
                          (insertion_salary[j] == temp_salary && insertion_empid[j] < temp_empid))) 
                          {
            comparison++;
            insertion_empid[j+1]= insertion_empid[j];
            insertion_salary[j+1]= insertion_salary[j];
            j--;
            swap++;
        }
        insertion_empid[j+1]= temp_empid;
        insertion_salary[j+1]= temp_salary;
    }
    printf("Insertion sort output:");
    for (int i=0;i<n;i++) 
    {
        printf("%d",insertion_empid[i]);
    }
    printf("\nSwap:%d,Comparison:%d\n",swap,comparison);
}
int main() 
{
    int n;
    //input the number of employees--------------------
    printf("Enter the number of employees:");
    scanf("%d",&n);
    int empid[n],salary[n];
    //take input for employee IDs and salaries--------------------
    input_details(n,empid,salary);
    //perform sorting------------------------
    bubble_sort(n,empid,salary);
    selection_sort(n,empid,salary);
    insertion_sort(n,empid,salary);
    return 0;
}
