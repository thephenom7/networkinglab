#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
struct array
{
    int begin,end;
    int *a;
};
 void merge(int *arr,int l,int m,int r)
 {
     int n1=m-l+1;
     int n2=r-m;
     int le[n1];
     int ri[n2];
     int i,j;
    for(i=0;i<n1;i++)
    {
        le[i]=arr[l+i];
    }
    for(i=0;i<n2;i++)
    {
        ri[i]=arr[m+1+i];
    }  
    i=0;
    j=0;
    int k=l;
    while(i<n1 && j<n2)
    {
        if(le[i]<=ri[j])
        {
            arr[k]=le[i];
           // cout<<"\n"<<le[i]<<"<"<<ri[j]<<"\t"<<arr[k];
            
            i++;
        }
        else
        {
            arr[k]=ri[j];
           // cout<<"\n"<<le[i]<<">"<<ri[j]<<"\t"<<arr[k];

            j++;
        }
        k++;
        
    }
    while(i<n1)
    {
        arr[k]=le[i];
        k++;
        i++;

    }
    while(j<n2)
    {
        arr[k]=ri[j];
        j++;
        k++;

    }

 }
 void mergesort(int *arr,int l,int r)
 {
     if(l<r)
     {
         int m=(l+r)/2;
         mergesort(arr,l,m);
         mergesort(arr,m+1,r);
         merge(arr,l,m,r);
     }
     else
     {
         return;
     }
     
 }
void *sort(void *ptr)
{
    struct array *ob3=(struct array *)ptr;
    int l=ob3->begin;
    int u=ob3->end;
    mergesort(ob3->a,l,u);
    for(int i=l;i<=u;i++)
    {
        printf("\n%d               %d",l,*(ob3->a+i));
    }

}
void main()
{
    pthread_t t1,t2;
    int arr[20],i,j,n;
    printf("Enter the array size \n");
    scanf("%d",&n);
    printf("Enter the array elements \n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    struct array ob1,ob2;
    ob1.begin=0;
    ob1.end=(n-1)/2;
    ob1.a=arr;
    ob2.begin=((n-1)/2)+1;
    ob2.end=(n-1);
    ob2.a=arr;
    pthread_create(&t1,NULL,sort,&ob1);
    pthread_create(&t2,NULL,sort,&ob2);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    merge(arr,0,(n-1)/2,n-1);
    for(i=0;i<n;i++)
    {
        printf("\nans   %d",arr[i]);
    }



}