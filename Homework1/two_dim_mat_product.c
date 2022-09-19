/* Usage : ./main testbench0*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void f(FILE *fin, FILE *fout);                                  // file processing
void two_product(int *mat1, int *mat2, int* mat3, int col1, int col2, int row1);     // two-dimension matrix production

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Usage: ./main filename1 filename2 ...\n");
        return 1;
    }
    FILE *fp1, *fp2;
    // Output File
    fp2 = fopen("out.txt", "w");
    if(fp2 == NULL){
        printf("Failed to open out.txt\n");
        return 2;
    }
    // File Processing
    for (int i = 1; i < argc; i++){
        fp1 = fopen(argv[i], "r");
        if(fp1==NULL){
            printf("Failed to open %d.\n", argv[i]);
            return 2;
        }
        f(fp1, fp2);
        fclose(fp1);
    }
    fclose(fp2);
    return 0;
}

void f(FILE *fin, FILE *fout)
{
    char str[10];
    char filename[11];  //testbenchx
    int row1, row2, col1, col2;
    int *mat1, *mat2;
    int i;
    fscanf(fin, "%*[^#]#####%s", filename);
    printf("Process file: %s. ", filename);
    // Matrix X
    while(fgetc(fin) != ':');
    fscanf(fin, "%d x %d )", &row1, &col1);   // size of matrix 
    printf("X = %d, %d ; ", row1, col1);
    mat1 = (int*)malloc( (row1*col1)*sizeof(int) );
    if(mat1 ==NULL){
        printf("Matrix 1 allocate failed. \n");
        exit(1);
    }
    else{
        for(i=0; i<row1*col1; i++){
            fscanf(fin, "%s", str);
            mat1[i] = atoi(str);
        }
    }
   // Matrix Y
    while(fgetc(fin) != ':');
    fscanf(fin, "%d x %d )", &row2, &col2);    
    printf("Y = %d, %d\n", row2, col2);
    mat2 = (int*)malloc( row2*col2*sizeof(int) );
    if(mat2 ==NULL){
        printf("Matrix 2 allocate failed. \n");
        exit(1);
    }
    else{
        for(i=0; i<row2*col2; i++){
            fscanf(fin, "%s", str);
            mat2[i] = atoi(str);
        }
    }
    if(!(col1==row2)){
        printf("Number of columns of matrix X must equal to number of rows of Matrix Y. \n");
        exit(1);
    }
    // Product
    int *mat3;
    mat3 = (int*)malloc(row1*col2*sizeof(int));
    two_product(mat1, mat2, mat3, col1, col2, row1);
    /*for (i=0; i<row1; i++){
        for (int j=0; j<col2; j++)
            printf("%d ", mat3[i*col2+j]);
        printf("\n");
    }*/

    free(mat1);
    free(mat2);

    // Output file
    for (i=0; i<row1; i++){
        for (int j=0; j<col2; j++)
            fprintf(fout, "%d ", mat3[i*col2+j]);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n");
    free(mat3);
}

void two_product(int *mat1, int *mat2, int *mat3, int col1, int col2, int row1)
{
    // row2 = col1
    for (int i=0; i<row1; i++){
        for (int j=0; j<col2; j++){
            for (int k=0; k<col1; k++){
                mat3[ i*col1+j ] += mat1[ i*col1+k ] * mat2[ k*col2+j ];
            }
        }
    }
}
