#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i,j,k,n;
    float c;
    float sum=0.0;
    printf("\nEnter the order of matrix: ");
    scanf("%d",&n);
    float* x = malloc(sizeof(float)*(n+1));
    float** A = malloc(sizeof(float*)*(n+2));
    for(i = 1;i <= (n+1);i++)
	A[i] = malloc(sizeof(float)*(n+2));
    printf("\nEnter the elements of augmented matrix row-wise:\n");
    for(i=1; i<=n; i++)
        for(j=1; j<=(n+1); j++)
            scanf("%f",&A[i][j]);

    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c=A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                    A[i][k]=A[i][k]-c*A[j][k];
            }
        }
    }

    x[n]=A[n][n+1]/A[n][n];
    
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
            sum=sum+A[i][j]*x[j];

        x[i]=(A[i][n+1]-sum)/A[i][i];
    }

    printf("\nThe solution is: \n");

    for(i=1; i<=n; i++)
        printf("\nx%d = %f\t\n\n",i,x[i]); 

    return 0;
}

/* Input

4
.92 .03 .02 .01 .04
.02 .94 .02 .01 .32
.01 .01 .90 .01 .18
.05 .02 .06 .97 .10



.04
.32
.18
.10
*/
