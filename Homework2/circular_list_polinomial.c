/* Usage : ./main testbench0*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// -----------------
//   Circular List
// -----------------

struct Node {
    int exp;
    int coef;
    struct Node *next;
};

// Initialize
struct Node *head = NULL;
struct Node *last = NULL;

// insert last
void insertLast(int exp, int coef){
    struct Node* temp;
    temp = (struct Node*)malloc(sizeof(struct Node));
    temp->exp = exp;
    temp->coef = coef;
    temp->next = head;
    if (last == NULL)   // empty list
    {
        // Segmentation Fault (core dumped) if directly identify head->next
        struct Node* init;
        init->exp = -1;     // always less than others (never be swapped)
        init->coef = 0;
        init->next = temp;
        head = init;
        last = temp;
    }
    else
    {
        last->next = temp;
        last = temp;
    }
}

// print list
void printList(){
    if (last == NULL)
        printf("List is empty.\n");
    else
    {
        struct Node* temp;
        temp = head->next;
        int i = 1;
        do {
            printf("->(%3d ,%3d)", temp->coef, temp->exp);
            temp = temp->next;
            i++;
        }while(temp != head);
        printf("\n");
    }
}

// print list to File
void outfileList(FILE *fout, char* filename){
    fprintf(fout, "%s=", filename);

    if (last == NULL)
        fprintf(fout, "List is empty.\n");
    else
    {
        struct Node* temp;
        temp = head->next;
        int i = 1;
        do {
            if(temp->exp == 0)
                fprintf(fout, " %+d", temp->coef);
            else if(temp->exp == 1){
                fprintf(fout, " %+d x", temp->coef);
            }
            else{
                fprintf(fout, " %+d x ^ %d", temp->coef, temp->exp);
            }
            temp = temp->next;
            i++;
        }while(temp != head);
        fprintf(fout, "\n");
    }
}

// get list lenth
int getLenth(){
    int count = 0;
    if (last == NULL)
        return count;
    else
    {
        struct Node* temp;
        temp = head->next;
        do {
            temp = temp->next;
            count++;
        }while(temp != head);
    }
    return count;
}

// delete term ( pre->del, delete del )
void delTerm(struct Node *pre, struct Node *del){
    if (last == del)
        last = pre;
    if (head->next == del)
        head->next = del->next;
    pre->next = del->next;  // reassign link
    free(del);
}

// clearList
void clearList(){
    if(last != NULL){
        do {
            delTerm(head, head->next);
        }while(head->next != head);
        head = NULL;
        last = NULL;
    }
}


// bubble sort
void swapTerm(struct Node *prev, struct Node *current){ // swap current & current->next
    struct Node* next = current->next;
    int head_swap = 0, last_swap = 0;
    if(head == prev) head_swap = 1;
    if(last == next) last_swap = 1;
    current->next = next->next;
    next->next = current;
    prev->next = next;
    if (head_swap==1) head = prev;
    if (last_swap==1) last = current;
}

void sortTerm()
{
    if (last == NULL)
        printf("Empty List. \n");
    else{
        struct Node *prev = head;
        struct Node *check = head->next;
        int swapped = 0;
        int len = getLenth();
        // printf("Lenth of list: %d\n", len);
        for (int i=0; i<len-1; i++){         // head->next to last->prev
            prev = head;
            check = head->next;
            swapped = 0;
            for (int j=i; j<len-1; j++){
                if (check->exp < check->next->exp){ // head->next to i th
                    swapTerm(prev, check);  // swap check and check->next
                    swapped = 1;
                    prev = prev->next;
                }
                else{
                    prev = prev->next;
                    check = check->next;
                }
            }
            if(swapped==0)  // optimize
                break;

            // debugging
            //
            // printf("sort %d : ", i);
            // printList();
            //
            // printf("last: (%2d, %2d)->(%2d, %2d)\n", last->coef, last->exp, last->next->coef, last->next->exp);
            // printf("head: ->(%2d, %2d)\n", head->next->coef, head->next->exp);
            // printf("prev->check: (%2d, %2d)->(%2d, %2d)\n\n", prev->coef, prev->exp, check->coef, check->exp);
        }
    }
}

// simpily polynimial
void simplifyTerm()
{
    if (last == NULL)
        printf("Empty List. \n");
    else{
        // sort terms by exp
        sortTerm();
        // merge terms
        struct Node *current = head->next;
        while(!(current==last)){
            if(current->exp == current->next->exp){
                current->coef += current->next->coef;
                delTerm(current, current->next);
            }
            else
                current = current->next;
        }
    }
}

// ----------------
//      main
// ----------------

void f(FILE *fin, FILE *fout)
{
    char filename[11];  //testbenchx
    int exp, coef;
    
    // read file
    fscanf(fin, "%s = ", filename);
    printf("Process file: %s. \n", filename);
    char ch;
    ch = fgetc(fin);
    while(ch != EOF)
    {
        if (ch == '+')
        {
            fscanf(fin, "%d ", &coef);
            if ((ch = fgetc(fin)) == 'x'){
                ch = fgetc(fin);
                if ((ch = fgetc(fin)) == '^'){
                    fscanf(fin, "%d", &exp);
                    ch = fgetc(fin);
                    if(ch != EOF)
                        ch = fgetc(fin);
                }
                else
                    exp = 1;
            }else
                exp = 0;
        }
        else if (ch == '-')
        {
            fscanf(fin, "%d ", &coef);
            coef *= -1;
            if ((ch = fgetc(fin)) == 'x'){
                ch = fgetc(fin);
                if ((ch = fgetc(fin)) == '^'){
                    fscanf(fin, "%d", &exp);
                    ch = fgetc(fin);
                    if(ch != EOF)
                        ch = fgetc(fin);
                }
                else
                    exp = 1;
            }else
                exp = 0;
        }
        // printf("(%+d, %d) \n", coef, exp);
        insertLast(exp, coef);
    }

    // Simplify 
    printf("Original : \n");
    printList();
    printf("\n");

    simplifyTerm();
    
    printf("\nMerge : \n");
    printList();

    // Output File
    outfileList(fout, filename);
    
    printf("\nClear List. \n");
    clearList();
    //printList();

}



int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Usage: ./main filename1 filename2 ...\n");
        return 1;
    }

    // instruction must in a function
    // head->exp = 0;      
    // head->coef = -1;
    // head->next = head;

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
        // Read File & Process & Write File
        f(fp1, fp2);
        fclose(fp1);
    }
    fclose(fp2);
    return 0;
}
