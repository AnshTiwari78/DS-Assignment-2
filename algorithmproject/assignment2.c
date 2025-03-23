#include<stdio.h>
#include<string.h>
struct Student{char name[100];float height;};
void linear_Search(struct Student students[],int n,float limit)
{
  printf("\nPerforming Linear Search...\n");
  int count=0;
  for(int i=0;i<n;i++)
  {
    count++;
    if(students[i].height>limit)
    {
      printf("Name: %s, Height: %.2f feet\n",students[i].name,students[i].height);
    }
  }
  printf("Linear Search Iterations: %d\n",count);
}
void binary_Search(struct Student students[],int n,float limit)
{
  printf("\nPerforming Binary Search...\n");
  struct Student temp;
  for(int i=0;i<n-1;i++)
  {
    for(int j=i+1;j<n;j++)
    {
      if(students[i].height>students[j].height)
      {
        temp=students[i];
        students[i]=students[j];students[j]=temp;
      }}}
int left=0,right=n-1,count=0;
  while(left<=right)
  {
    count++;
    int mid=left+(right-left)/2;
    if(students[mid].height>limit)
    {
      for(int i=mid;i<n;i++)
      {
        printf("Name: %s, Height: %.2f feet\n",students[i].name,students[i].height)
          ;
      }
      break;
    }
    else
    {
      left=mid+1;
    }
  }
  if(left>right)
  {
    printf("No student found with height more than %.2f feet.\n",limit);
  }
  printf("Binary Search Iterations: %d\n",count);
}
int main()
{
  int n;
  printf("Enter the number of students: ");
  scanf("%d",&n);
  getchar();
  struct Student students[n];
  for(int i=0;i<n;i++)
  {
    printf("Enter details for student %d:\n",i+1);
    printf("Enter name: ");
    
//agar next input fgets() se lenge, toh wo \n ko read kar lega!
    fgets(students[i].name,sizeof(students[i].name),stdin);
    size_t len=strlen(students[i].name);
    if(len>0&&students[i].name[len-1]=='\n')
    {
      students[i].name[len-1]='\0';
    }
    printf("Enter height (in feet): ");
    scanf("%f",&students[i].height);
//isiliye getchar(); use karte hain taaki \n ko buffer se hata sake.
    getchar();
  }
linear_Search(students,n,5.0);
binary_Search(students,n,5.0);
  return 0;
}
