#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float determinant(float** a,float k);
float** cofactor(float**,float);
float** transpose(float** num,float** fac,float r);
float** inverse(float** a);
float** matrixMult(float** a, float** b, int lenA, int lenB);
void modifyLambda(float** lambda, int w);

int main()
{
	int i, j, w;
	float sum = 0;
	float matrix[5][5] = {{0.92, 0.02, 0.02, 0.01, 0.02},{0.02, 0.94, 0.02, 0.01, 0.03},{0.01, 0.01, 0.90, 0.01, 0.02},{0.02, 0.02, 0.02, 0.95, 0.01}, {0.03, 0.01, 0.04, 0.02, 0.92}};
	float** X = malloc(sizeof(float*) * 5);
	for(i = 0; i < 5; i++)
		X[i] = malloc(sizeof(float) * 1);
	while(sum<1)
	{
		sum=0;
		printf("Enter the Xo Matrix \n");
		for(i = 0; i < 5; i++)
		{
			scanf("%f", &X[i][0]);
		
			sum += X[i][0];
			
			if(sum >= 1 && i != 4)
			{
				printf("Invalid entry");
				sum=0;
				break;
			}
		}
	}
	
	printf("An in-depth analysis of the present market reveals the following trends for the five brands - PUMA, NIKE, REEBOK, ADIDAS and SLAZENGER : \n");
	printf("PUMA	NIKE	REEBOK	ADIDAS	SLAZENGER\n");
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%.2f	", matrix[i][j]);
		printf("\n");
	}
	
	printf("\nEach cell (j, i) represents the percentage of customers who migrate from brand j to brand i, where j is the column and i is the row.\nFor example, matrix[2][4] = 0.02\nThis implies that 2 out of every hundred people loyal to the brand SLAZENGER have swayed their following to the brand REEBOK.");
			
	float **lambda=malloc(sizeof(float*)*5);
	for(i=0;i<5;i++)
		lambda[i]=calloc(5,sizeof(float));	
	lambda[0][0]=0.999999;
	lambda[1][1]=0.901939;
	lambda[2][2]=0.919999;
	lambda[3][3]=0.927093;
	lambda[4][4]=0.880967;
	
	float** S=malloc(sizeof(float*)*5);

	for(i=0;i<5;i++)
		S[i]=calloc(5,sizeof(float));

	S[0] =(float[5]){-0.377265,-0.795776,-0.209019,-0.247341,-0.070346};
	S[1] =(float[5]){-0.529695,-0.154330,-0.766406,-0.670115,0.133884};
	S[2] =(float[5]){-0.238807, 0.362716, 0.139346, 0.052522, 0.726811};
	S[3] = (float[5]){-0.551289, 0.154330, 0.418039, 0.670115, -0.133884};
	S[4] = (float[5]){-0.464912, 0.433060, 0.418031, 0.194819, -0.056464};

	float** inverseS = inverse(S);
	
	printf("The matrix S is : \n");
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%.3f	", S[i][j]);
		printf("\n");
	}

	printf("The matrix Lambda is : \n");
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%.3f	", lambda[i][j]);
		printf("\n");
	}
	
	printf("The matrix S Inverse is : \n");
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%.3f	", inverseS[i][j]);
		printf("\n");
	}
	
	printf("Enter the number of weeks after which the customer following for each brand is to be known : ");
	scanf("%d", &w);
	
	modifyLambda(lambda, w);
//
	printf("The matrix Lambda after %d weeks : \n", w);
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf("%.3f	", lambda[i][j]);
		printf("\n");
	}	
//
	
	float** final = matrixMult(matrixMult(matrixMult(S, lambda, 5, 5), inverseS, 5, 5), X, 5, 1);
	
	printf("The final matrix, X after %d weeks is : \n", w);
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 1; j++)
			printf("%.6f	", final[i][j]);
		printf("\n");
	}
	
	return 0;
}

void modifyLambda(float** lambda, int w)
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			if(i == j)
				lambda[i][j] = pow(lambda[i][j], w);
		
	}
}

float** inverse(float** a)
{
  float d;

  d=determinant(a,5);
  printf("\nDeterminant of the Matrix = %f\n",d);

  return(cofactor(a,5));
}

//For calculating Determinant of the Matrix
float determinant(float** a,float k)
{
   int i,j,m,n,c;
  float s=1,det=0;
  
  float** b = malloc(sizeof(float*) * 5);
  for(i = 0 ; i < 5; i++)
  	b[i] = calloc(5, sizeof(float));
 
  if (k==1)
    {
     return (a[0][0]);
    }
  else
    {
     det=0;
     for (c=0;c<k;c++)
       {
        m=0;
        n=0;
        for (i=0;i<k;i++)
          {
            for (j=0;j<k;j++)
              {
                b[i][j]=0;
                if (i != 0 && j != c)
                 {
                   b[m][n]=a[i][j];
                   if (n<(k-2))
                    n++;
                   else
                    {
                     n=0;
                     m++;
                     }
                   }
               }
             }
          det=det + s * (a[0][c] * determinant(b,k-1));
          s=-1 * s;
          }
    }

    return (det);
}

float** cofactor(float** num,float f)
{
 int p,q,m,n,i,j;
 
   float** b = malloc(sizeof(float*) * 5);
  for(i = 0 ; i < 5; i++)
  	b[i] = calloc(5, sizeof(float));
  
    float** fac = malloc(sizeof(float*) * 5);
  for(i = 0 ; i < 5; i++)
  	fac[i] = calloc(5, sizeof(float));
 
 for (q=0;q<f;q++)
 {
   for (p=0;p<f;p++)
    {
     m=0;
     n=0;
     for (i=0;i<f;i++)
     {
       for (j=0;j<f;j++)
        {
          if (i != q && j != p)
          {
            b[m][n]=num[i][j];
            if (n<(f-2))
             n++;
            else
             {
               n=0;
               m++;
               }
            }
        }
      }
      fac[q][p]=pow(-1,q + p) * determinant(b,f-1);
    }
  }

  return(transpose(num,fac,f));
}
//Finding transpose of matrix
float** transpose(float** num,float** fac,float r)
{
  int i,j;
  float d;
  
    float** b = malloc(sizeof(float*) * 5);
  for(i = 0 ; i < 5; i++)
  	b[i] = calloc(5, sizeof(float));
  
  float**inverse = calloc(5, sizeof(float*));
  for(i = 0; i < 5; i++)
  	inverse[i] = calloc(5, sizeof(float));
  
  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
         b[i][j]=fac[j][i];
        }
    }
  d=determinant(num,r);
  for (i=0;i<r;i++)
    {
     for (j=0;j<r;j++)
       {
        inverse[i][j]=b[i][j] / d;
        }
    }
     
     return inverse;
}

float** matrixMult(float** a, float** b, int m, int p)
{
int i,j,k;
float sum;
float**c=malloc(sizeof(float*)*m);
for(i=0;i<m;i++)
	c[i]=malloc(sizeof(float)*p);
	
for(i=0;i<m;i++)
      for(j=0;j<p;j++)
           c[i][j]=0;
    
      for(i=0;i<m;i++){ //row of first matrix
      for(j=0;j<p;j++){  //column of second matrix
           sum=0;
           for(k=0;k<5;k++)
               sum=sum+a[i][k]*b[k][j];
           c[i][j]=sum;
      }
      }
	return c;
}
