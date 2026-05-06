#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
typedef struct AVLnode * AVLNode;
struct AVLnode
{
    char Element[101];
    AVLNode Left;
    AVLNode Right;
    int Height; //Balance information
    int frequency;//node counter
};
struct hashing{
char word[301];
int frequency;
};
int flag=0,Flag=0,counter=0,rehash=0;
struct hashing* HashTable;
// Function prototypes
void printMenu();
AVLNode MakeEmpty( AVLNode T );
AVLNode Find(char  X[], AVLNode T );
AVLNode FindMin( AVLNode T );
AVLNode FindMax( AVLNode T );
int Height( AVLNode P );
int Max( int Lhs, int Rhs );
AVLNode SingleRotateWithLeft( AVLNode K2 );
AVLNode SingleRotateWithRight( AVLNode K1 );
AVLNode DoubleRotateWithLeft( AVLNode K3 );
AVLNode DoubleRotateWithRight( AVLNode K1 );
AVLNode Insert(char X[], AVLNode T );
AVLNode Delete(char X[], AVLNode T );
void PrintInOrder( AVLNode t);
AVLNode LoadFile(AVLNode T);
void RemoveNonAlphabetical(char x[]);
int isPrimeNumber(int n);
int hash(char* key,int TableSize);
int Hash(char* key,int TableSize);
int new_size_rehash(int currentSize);
float computeLoadFactor (int tableSize);
void initializeHashTable(int size,struct hashing* H);
void createHashTable(int size,struct hashing* HT,AVLNode T);
void InsertToHash(int size,int f,char x[],struct hashing* H);
struct hashing* ReHash(int size,struct hashing* H);
void DeleteFromHashTable(int size,char x[],struct hashing* H);
void SearchForWordPrintfrequency(int size,char x[],struct hashing* H);
void PrintWordStatistics(int size,struct hashing* H);
void PrintHashTable(int size, struct hashing* H);

int main()
{
    float LF;
    int size=17;
    char word[101];
    AVLNode tree=NULL;
    struct hashing* Hashtable1 = (struct hashing*)malloc(size * sizeof(struct hashing)); // Allocate memory for the hash table
    initializeHashTable(size,Hashtable1);
    int option;//the option that will be entered by the user
    do{
    printMenu(); //display application menu for the user
    scanf("%d",&option);//scan the option selected by the user
    getchar();//let gets in other function read string within incorporated spaces correctly //actually remove the null terminator placed by scanf after reading from the user
    switch(option){//do the operation based on the user choices
    case 1:if(flag==1){
       tree=LoadFile(tree);
        } else{printf("Choose to create the avl tree first\n");};break;
    case 2:tree = MakeEmpty(tree);flag=1;break;
    case 3:if(flag==1&&Flag==1){
           printf("Enter word to insert\n");
           gets(word);
           tree=Insert(word,tree);
           }else {
           printf("Please select 1 and 2 first\n");}break;
    case 4:if(flag==1&&Flag==1){
           printf("Enter word to delete\n");
           gets(word);
           tree=Delete(word,tree);};break;
    case 5:if(flag==1&&Flag==1){PrintInOrder(tree);}else{printf("Please select 1 and 2 first\n");};break;
    case 6:if(flag==1&&Flag==1){createHashTable(size,Hashtable1,tree);size=new_size_rehash(size),PrintHashTable(size,HashTable);}else{printf("Please select 1 and 2 first\n");}break;
    case 7:if(flag==1&&Flag==1){
           printf("Enter word to insert\n");
           gets(word);
           RemoveNonAlphabetical(word);
           LF=computeLoadFactor(size);
           if(LF<0.7){
            if(rehash==0){
            InsertToHash(size,1,word,Hashtable1);
            PrintHashTable(size,Hashtable1);
            }
            else if(rehash==1){
              size=new_size_rehash(size);
             InsertToHash(size,1,word,HashTable);
             PrintHashTable(size,HashTable);
            }

           }
           else {
             counter=0;
             rehash=1;
             HashTable=ReHash(size,Hashtable1);
             size=new_size_rehash(size);
             InsertToHash(size,1,word,HashTable);
             PrintHashTable(size,HashTable);
           }
           }else {printf("Please select 1 and 2 first\n");}break;
    case 8:if(flag==1&&Flag==1){
           printf("Enter word to delete\n");
           gets(word);
           if(rehash==0){
            DeleteFromHashTable(size,word,Hashtable1);
            PrintHashTable(size,Hashtable1);
           }
           else if(rehash==1) {DeleteFromHashTable(size,word,HashTable);PrintHashTable(size,HashTable);}
           }else{printf("Please select 1 and 2 first\n");} break;
    case 9:if(flag==1&&Flag==1){
           printf("Enter word to Search for\n");
           gets(word);
           if(rehash==0){
            SearchForWordPrintfrequency(size,word,Hashtable1);
           }
           else if(rehash==1){ SearchForWordPrintfrequency(size,word,HashTable);}}else{printf("Please select 1 and 2 first\n");}break;
    case 10:if(flag==1&&Flag==1){
        if(rehash==0){
            PrintWordStatistics(size,Hashtable1);
        }
        else if(rehash==1){
            SearchForWordPrintfrequency(size,word,HashTable);
        }
    }else{printf("Please select 1 and 2 first\n");};break;
    case 11: printf("exit application");exit(0);
    default:printf("try again");break;
    }}while(option!=11);//display menu to the user until they choose exit

    return 0;
}

void printMenu(){// print menu to user
printf("Menu of my application\n");
printf("Please select an operation \n");
printf("1-Load data from the file\n");
printf("2-Create the AVL tree\n");
printf("3-Insert a word to the AVL tree\n");
printf("4-Delete a word from the AVL tree\n");
printf("5-Print the words as sorted in the AVL tree\n");
printf("6-Create the Hash Table\n");
printf("7-Insert a word to the Hash table\n");
printf("8-Delete a word from the hash table\n");
printf("9-Search for a word in the hash table and print its frequency\n");
printf("10-Print words statistics\n");
printf("11-Exit the application\n");
}

AVLNode LoadFile(AVLNode T){
FILE* in;//initialize pointer to the file
in = fopen("input.txt","r"); // select the file to open, and scan it later
if(in==NULL){
    printf("Error in opening the file!\n");
    exit(0); //if file don't have data print error message and exit the function
}
char inputString[3001],String[1001];//define an array to store input string  from file including the null character for each line
while(fgets(inputString,sizeof(inputString),in)){//loop to read the file line by line
if(strlen(inputString)>3001){//if the size of a line in the file is greater than the maximum (3000) exit program
        printf("Error\n");
        exit(0);
}
RemoveNonAlphabetical(inputString);
char *tok=strtok(inputString," ");
while(tok!=NULL){

    strcpy(String,tok);
    T=Insert(String,T);
    tok=strtok(NULL," ");
}
}
printf("File is loaded in success\n");
fclose(in);//close the file
Flag=1;
return T;
}

void RemoveNonAlphabetical(char x[]){
int i,j=0,flag=0;
for(i=0;x[i]!='\0';i++){
if(isalpha(x[i])){
if(flag==1){
x[j++]=' ';
}
x[j++]=x[i];
flag=0;
}
else{
    flag=1;
}
}
x[j]='\0';
}

AVLNode MakeEmpty( AVLNode T ){
    if( T != NULL )
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

AVLNode Find(char  X[], AVLNode T ){
    if( T == NULL )
        return NULL;
    if(strcasecmp(X,T->Element) <0)
        return Find( X, T->Left );
    else if(strcasecmp(X,T->Element)>0)
        return Find( X, T->Right );
    else
        return T;
}

AVLNode FindMin( AVLNode T ){
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )
        return T;
    else
        return FindMin( T->Left );
}

AVLNode FindMax( AVLNode T ){
    if( T != NULL )
        while( T->Right != NULL )
            T = T->Right;

    return T;
}

int Height( AVLNode P ){
    if( P == NULL )
        return -1;
    else
        return P->Height;
}

int Max( int Lhs, int Rhs ){
    return Lhs > Rhs ? Lhs : Rhs;
}

/* This function can be called only if K2 has a left child */
/* Perform a rotate between a node (K2) and its left child */
/* Update heights, then return new root */

AVLNode SingleRotateWithLeft( AVLNode K2 ){
    AVLNode  K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}


/* This function can be called only if K1 has a right child */
/* Perform a rotate between a node (K1) and its right child */
/* Update heights, then return new root */

AVLNode SingleRotateWithRight( AVLNode K1 ){
    AVLNode K2;

    K2 = K1->Right;
    K1->Right = K2->Left;
    K2->Left = K1;

    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithLeft( AVLNode K3 ){
    K3->Left = SingleRotateWithRight( K3->Left );//Rotate between K1 and K2
    return SingleRotateWithLeft( K3 );//Rotate between K3 and K2
}

/* This function can be called only if K1 has a right */
/* child and K1's right child has a left child */
/* Do the right-left double rotation */
/* Update heights, then return new root */

AVLNode DoubleRotateWithRight( AVLNode K1 ){
    K1->Right = SingleRotateWithLeft( K1->Right );//Rotate between K3 and K2
    return SingleRotateWithRight( K1 );//Rotate between K1 and K2
}

AVLNode Insert(char X[],AVLNode T ){
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = (struct AVLnode*)malloc( sizeof( struct AVLnode ) );
        if( T == NULL )
            printf( "Out of space!!!" );
        else
        {
            strcpy(T->Element,X);
            T->Height = 0;
            T->frequency=1;
            T->Left = T->Right = NULL;
        }
    }
    else if(strcasecmp(X,T->Element) < 0)
    {
        T->Left = Insert( X, T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 ){
            if( strcasecmp(X,T->Left->Element) < 0 )
                T = SingleRotateWithLeft( T );
            else
                T = DoubleRotateWithLeft( T );
        }
    }
    else if(strcasecmp(X,T->Element) > 0 )
    {
        T->Right = Insert( X, T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 ){
            if( strcasecmp(X,T->Right->Element) > 0 )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
        }
    }
    else if(strcasecmp(X,T->Element)==0){
      T->frequency++;
    }

    T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;
    return T;
}

AVLNode Delete(char X[], AVLNode T ){
AVLNode TmpCell;
if( T == NULL )
printf( "Element not found" );
else if(strcasecmp(X,T->Element)<0) /* Go left */
T->Left = Delete( X, T->Left );
else if(strcasecmp(X,T->Element)>0) /* Go right */
T->Right = Delete( X, T->Right );
else /* Found element to be deleted */
if( T->Left && T->Right )  //Two children
{//Replace with smallest in right subtree
TmpCell = FindMin( T->Right );
strcpy(T->Element,TmpCell->Element);
T->Right = Delete( T->Element, T->Right );
}
else { //One or zero children
TmpCell = T;
if( T->Left == NULL )//Also handles 0 children
    T = T->Right;
else if( T->Right == NULL )
    T = T->Left;

free( TmpCell );
}
if (T == NULL) return T;
T->Height = 1 + Max(Height(T->Left), Height(T->Right));
int balance = Height( T->Left ) - Height( T->Right );
int Balance1 = Height( T->Left->Left ) - Height( T->Left->Right );
int Balance2 = Height( T->Right->Left ) - Height( T->Right->Right );

if(balance > 1){
// Left Left Case
if (Balance1 >= 0)
        return SingleRotateWithRight(T);
// Left Right Case
if (Balance1 < 0)
{
T->Left = SingleRotateWithLeft(T->Left);
return SingleRotateWithRight(T);
}

}
if(balance<-1){
// Right Right Case
if ( Balance2 <= 0)
     return SingleRotateWithLeft(T);
// Right Left Case
if ( Balance2 > 0)
{
T->Right = SingleRotateWithRight(T->Right);
return SingleRotateWithLeft(T);
}
}
return T;
}

void PrintInOrder( AVLNode t){//in-order print to see the elements
    if( t != NULL)
    {
        PrintInOrder( t->Left );
        printf("%s\tfrequency=%d\n", t->Element,t->frequency);
        PrintInOrder( t->Right );
    }
}

int isPrimeNumber(int n){
int i;
for(i=2;i<(n/2);i++){
    if(n%i==0)
        return 0;
}
return 1;
}

int new_size_rehash(int currentSize){
int newSize = 2*currentSize;
while (!isPrimeNumber(newSize))
         newSize++;
return newSize ;
}

float computeLoadFactor (int tableSize){
    return ((float)(counter)/(float) tableSize);
}

int hash(char* key,int TableSize){
int hashValue = 0;
while( *key != '\0'){
hashValue +=*key++;
}
return (hashValue%TableSize);
}

int Hash(char* key,int TableSize){
int hashValue = 0,num,i;
while( *key != '\0'){
hashValue +=*key++;
}
for(i=0;i<TableSize;i++){
    if(isPrimeNumber(i)){
        num=i;
    }
}
return (num-(hashValue%num));
}

void initializeHashTable(int size,struct hashing* H){
for(int i=0;i<size;i++){
    H[i].word[0]='\0';
    H[i].frequency=0;
}
}

void createHashTable(int size,struct hashing* HT,AVLNode T){
if(T!=NULL){
createHashTable(size,HT,T->Left);
if(rehash==1){
int Size=new_size_rehash(size);
InsertToHash(Size,T->frequency,T->Element,HashTable);
}
else if(rehash==0){
InsertToHash(size,T->frequency,T->Element,HT);
}
createHashTable(size,HT,T->Right);
}
}

void InsertToHash(int size,int f,char x[],struct hashing* H){
int i,index;
float LF=computeLoadFactor(size),Size;
if(LF>=0.7){
counter=0;
rehash=1;
HashTable=ReHash(size,H);
Size=new_size_rehash(size);
InsertToHash(Size,f,x,HashTable);
counter++;
}
else{
printf(".\n");
counter++;
for(i=0;i<size;i++){
if(i==0){
x[0]=toupper(x[0]);
}
else{
    x[i]=tolower(x[i]);
}
index=(hash(x,size)+i*Hash(x,size))%size;
if(strcasecmp(H[index].word,x)==0){
    H[index].frequency++;
    return;
}
if(H[index].word[0]=='\0' && H[index].frequency==0&&strcasecmp(H[index].word,x)!=0){
    strcpy(H[index].word,x);
    H[index].frequency=f;
    return;
}
}
}

}

struct hashing* ReHash(int size,struct hashing* H){
int Size=new_size_rehash(size);
HashTable=(struct hashing*)malloc(Size * sizeof(struct hashing));
if(HashTable!=NULL){
    printf("size=%d",Size);
initializeHashTable(Size,HashTable);
for(int i=0;i<Size;i++){
    if(H[i].word[0]!='\0'){
        InsertToHash(Size,H[i].frequency,H[i].word,HashTable);
    }
}
}
return HashTable;
}

void DeleteFromHashTable(int size,char x[],struct hashing* H){
for(int i=0;i<size;i++){
    int index=(hash(x,size)+i*Hash(x,size))%size;
    if(strcasecmp(H[index].word,x)==0){
        if(H[index].frequency==1){
         H[index].word[0]='\0';
         H[index].frequency=0;
        }
        else{
            H[index].frequency--;
        }
        return;
    }
}
printf("Word not found!\n");
counter--;
}

void SearchForWordPrintfrequency(int size,char x[],struct hashing* H){
for(int i=0;i<size;i++){
    int index=(hash(x,size)+i*Hash(x,size))%size;
    if(strcasecmp(H[index].word,x)==0){
        printf("Frequency=%d\n",H[index].frequency);
        return;
    }
}
}

void PrintWordStatistics(int size,struct hashing* H){
int i,Count=0,max=H[0].frequency,threshold;
printf("Enter a number to find all words that appear more times than this number\n");
scanf("%d",&threshold);
char x[301];
for(i=0;i<size;i++){
    if(H[i].frequency==1){
        Count++;
    }
    if(H[i].frequency > max){
     strcpy(x,H[i].word);
    }
}
printf("Number of Unique words=%d\n",Count);
printf("most frequent word=%s\n",x);
Count=0;
for(i=0;i<size;i++){
if(H[i].frequency>threshold){
    Count++;
    printf("%s\t",H[i].word);
}
}
printf("Number of words appeared more than threshold=%d\n",Count);
}

void PrintHashTable(int size, struct hashing* H) {
    printf("\nIndex\tWord\t\tFrequency\n");
    for (int i = 0; i < size; i++) {
        if (H[i].word[0] != '\0') { // If the word is not empty
            printf("%d\t%s\t\t%d\n", i, H[i].word, H[i].frequency);
        }
    }
}
