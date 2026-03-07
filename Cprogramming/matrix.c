#include <stdio.h>  //including standard library
#include <stdlib.h>
#include <string.h> 

//defining variables
int n, m, p, q;
#define MAX 100
int first[MAX][MAX], second[MAX][MAX], result[MAX][MAX];

//defining functions
void matrixmultiply();
void matrixaddition();
void matrixsubtraction();
void matrixscalling();
int main(void)
{
   //user input
    printf("Choose the operation to perform:\n");
    printf("1. Matrix Multiplication\n");
    printf("2. Matrix Addition\n");
    printf("3. Matrix Subtraction\n");
    printf("4. Matrix Scaling\n");
    int choice;
    scanf("%d", &choice);
    if(choice == 4)  //special case where only single matrix is needed
    { printf("Enter rows and columns of matrix: ");
      scanf("%d %d", &n, &m);

      printf("Enter elements of matrix:\n");
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &first[i][j]);
        matrixscalling();
        return 0;

    }
    if(choice != 1,2,3,4)  //invalid input case
    {
        printf("Invalid choice! Please select a valid operation (1-4).\n");
        return 1;
    }
    //asking user for matrix dimensions
    printf("Enter rows and columns of first matrix: ");
    scanf("%d %d", &n, &m);
    printf("Enter rows and columns of second matrix: ");
    scanf("%d %d", &p, &q);


   
    //asking user for elements of matrices
    printf("Enter elements of first matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &first[i][j]);

    printf("Enter elements of second matrix:\n");
    for (int i = 0; i < p; i++)
        for (int j = 0; j < q; j++)
            scanf("%d", &second[i][j]);

    // Initialize result matrix to zero
    for (int i = 0; i < n; i++)
        for (int j = 0; j < q; j++)
            result[i][j] = 0;

   //calculating based on user input
    switch (choice) {
        case 1:
        
            if (m != p) {
                printf("Error! column of first matrix not equal to row of second.\n");
                return 1;
    }
            matrixmultiply();
            break;
        case 2:
            if (n != p || m != q) {
                printf("Error! Matrices must have the same dimensions for addition.\n");
                return 1;
            }
            matrixaddition();
            break;
        case 3:
            if (n != p || m != q) {
                printf("Error! Matrices must have the same dimensions for subtraction.\n");
                return 1;
            }
            matrixsubtraction();
            break;
        
    }
            

    return 0;
}

//function definitions
void matrixscalling()
{
    int scalar;
    printf("Enter the scalar value: ");
    scanf("%d", &scalar);

    // Scale the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = first[i][j] * scalar;
        }
    }

    // Print the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

void matrixsubtraction()
{
    // Subtract matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = first[i][j] - second[i][j];
        }
    }

    // Print the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

void matrixaddition()
{
    // Add matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[i][j] = first[i][j] + second[i][j];
        }
    }

    // Print the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}
void matrixmultiply()
{
    // Multiply matrices
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += first[i][k] * second[k][j];
            }
        }
    }

    // Print the result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}