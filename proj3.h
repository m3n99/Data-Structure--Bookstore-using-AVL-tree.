#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *in_f;
FILE *out_f;
typedef struct tree *pos;
typedef pos sun;
struct tree {
    char name[50];
    char author[50];
    char country[50];
    char year[20];
    char category[50];
    struct tree *right;
    struct tree *left;
    int height;
};

int max(int x, int y)//compare two integers
{
    if (x > y)
        return x;
    return y;
}

sun searchBookPos(sun t, char name[50])//get the position of the node ::book name is the key
{
    if (t == NULL)
        return NULL;
    else if (strcmpi(name, t->name) == 0) {
        return t;
    } else if (strcmpi(name, t->name) < 0)
        return searchBookPos(t->left, name);
    else
        return searchBookPos(t->right, name);
}

sun searchAuthPos(sun t, char author[50])//get position of the nod :: author name is the key
{
    if (t) {
        searchAuthPos(t->left, author);
        searchAuthPos(t->right, author);
        if (strcmpi(author, t->author) == 0) {
            printf("\n %s %s %s %s %s ", t->name, t->author, t->year, t->country, t->category);
            return t;
        }
    }
    return NULL;
}
void searchAuthor(sun tt)//handle search by author name
{
    char author[50];
    printf("\n enter the Author Name :");
    gets(author);
    sun t = searchAuthPos(tt, author);
    if (!t)printf("\nNot Found");
}

int getHeight(sun c)//return the height of the node
{
    if (c == NULL)//because height is zero if there is a node without children
        return -1;
    else
        return c->height;
}

sun SLR(sun k2)//single rotation left right
{
    sun k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    //k2 before k1 since k1 height depends on it
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    return k1;
}

sun SRL(sun k1)//single right left rotation
{
    sun k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    //k1 before k2 since k2 height depends on it
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    return k2;
}

//this function returns the sub_tree k3 after doing double rotate from left to right on it
sun DLR(sun k3)//double left right rotation
{
    //double rotate is two single rotates
    k3->left = SRL(k3->left);
    return SLR(k3);
}

sun DRL(sun k1)// double right left rotation
{
    k1->right = SLR(k1->right);
    return SRL(k1);
}

sun insertFile(sun t, char name[50], char author[50], char country[50], char year[20],
               char category[50])//fill tree from file
{
    if (t == NULL) {
        t = (sun) malloc(sizeof(struct tree));
        strcpy(t->author, author);
        strcpy(t->name, name);
        strcpy(t->country, country);
        strcpy(t->year, year);
        strcpy(t->category, category);
        t->height = 0;
        t->left = t->right = NULL;
    } else if ((strcmpi(name, t->name) < 0)) {
        t->left = insertFile(t->left, name, author, country, year, category);
        if (getHeight(t->left) - getHeight(t->right) >= 2) {
            if (strcmpi(name, t->left->name) < 0)
                t = SLR(t);//single rotate left to right
            else
                t = DLR(t);//double rotate left to right
        }
    } else {
        t->right = insertFile(t->right, name, author, country, year, category);
        if (getHeight(t->right) - getHeight(t->left) >= 2) {
            if (strcmpi(name, t->right->name) > 0)
                t = SRL(t);//single rotate right to left
            else
                t = DRL(t);//double rotate right to left
        }
    }
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    return t;
}

sun update(sun t, char name[50])//update the node where to update
{
    char x;
    printf("do you want to update the Books (Y/N) : ");
    scanf(" %c", &x);
    if (x == 'y' || x == 'Y') {
        char year[50], country[50], category[50];
        printf("enter the new year of Book:  ");
        scanf("%s", year);
        strcpy(t->year, year);
        printf("enter the new Publish Country: ");
        scanf("%s", country);
        strcpy(t->country, country);
        printf("enter the new Category: ");
        scanf("%s", category);
        strcpy(t->category, category);
        printf("\n %s %s %s %s %s ", t->name, t->author, t->year, t->country, t->category);
    } else if (x == 'n' || x == 'N') {
        return 0;
    } else
        update(t, name);
    return t;
}

sun insertData(sun t, char name[50], char author[50], char year[20],char country[50],
               char category[50])//insert data to tree from user
{       char first[50],last[50];
    if (t == NULL) {
        printf("please  enter the  Name of Author :");
        scanf("%s %s",first,last);
        strcat(first," ");
        strcpy(author,strcat(first,last));
        printf("please  enter the year :");
        scanf("%s", year);
        printf("please  enter the country:");
        scanf("%s", country);
        printf("please  enter the Category :");
        scanf("%s", category);

        t = (sun) malloc(sizeof(struct tree));
        strcpy(t->name, name);
        strcpy(t->author, author);
        strcpy(t->year, year);
        strcpy(t->country, country);
        strcpy(t->category, category);
        t->height = 0;
        t->left = t->right = NULL;
        return t;
    } else if ((strcmpi(name, t->name) < 0)) {
        t->left = insertData(t->left, name, author, year, country, category);
        if (getHeight(t->left) - getHeight(t->right) >= 2) {
            if (strcmpi(name, t->left->name) < 0)
                t = SLR(t);//single rotate left to right
            else
                t = DLR(t);//double rotate left to right
        }
    } else {
        t->right = insertData(t->right, name, author, year, country, category);
        if (getHeight(t->right) - getHeight(t->left) >= 2) {
            if (strcmpi(name, t->right->name) > 0)
                t = SRL(t);//single rotate right to left
            else
                t = DRL(t);//double rotate right to left
        }
    }
    t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    return t;
}

void insertMenu(sun t)//to handle insertion from user
{
    char name[50], author[50], year[15], country[50], category[50];

    if (t == NULL)
        return;
    else {
        printf("Please  Enter The Book Name :");
        scanf("%s", name);
        sun n = searchBookPos(t, name);
        if(n)  {
            printf("The Book is Found \n");
            printf("\n %s %s  %s %s %s ", n->name, n->author, n->country, n->year, n->category);

        } else {
            insertData(t, name, author, year, country, category);
        }
    }
}

void updateMenu(sun t)//to handle update from user
{
    char name[50];

    if (t == NULL)
        return;
    else {
        printf("Please  Enter The Book Name :");
        scanf("%s", name);
        sun n = searchBookPos(t, name);
        if (n) {
            printf("The Book is Found \n");
            update(n, name);
            printf("\n %s %s %s %s %s ", n->name, n->author, n->country, n->year, n->category);

        } else {
            printf("The Book is not Found \n");
        }
    }
}

void save(sun t)//return data from tree to file
{
    if (t) {
        save(t->left);
        save(t->right);
        fprintf(out_f, "%s|%s|%s|%s|%s\n", t->name, t->author, t->year, t->country, t->category);
    }
}

void list(sun t, char type[20]) {//to list items category
    if (t) {
        list(t->left, type);
        list(t->right, type);
        if (strcmpi(type, t->category) == 0)
            printf("%s %s %s %s %s \n", t->name, t->author, t->country, t->year, t->category);
    }
}

void showList(sun t) {//to handle the shown category items

    printf("\nFiction\n----*******************----\n");
    list(t, "Fiction");
    printf("\nNon-Fiction\n----***************--------\n");
    list(t, "Non-Fiction");
}

void saveToFile(sun t)//handle returning data to file
{   out_f=fopen("books.txt","w");
    if (t) {
        save(t);
    }
}

sun readData()//read data from file
{
    char name[50];
    char author[50];
    char country[50];
    char year[20];
    char category[50];
    sun t = NULL;
    in_f = fopen("books.txt", "r");
    if (in_f == NULL)
        printf("File Doesn't Exit\n");
    else {
        while (fscanf(in_f, "%[^|]%*c%[^|]%*c%[^|]%*c%[^|]%*c%s ", name, author, country, year, category) != EOF) {
            t = insertFile(t, name, author, country, year, category);
        }
    }
    return t;
}

sun findMax(sun t) {
    if (t == NULL)
        return NULL;
    while (t->right)
        t = t->right;
    return t;
}

void searchBook(sun tt)//handle search by book name
{
    char name[50];
    printf("\n enter the Book Name :");
    gets(name);
    sun t=searchBookPos(tt, name);
    if (t) {
        printf("the Book was found \n");
        printf("\n %s %s %s %s %s ", t->name, t->author, t->year, t->country, t->category);
    } else
        printf("Not Found\n");
}

sun deleteBookPos(sun t, char name[50], char author[50], char country[50], char year[20],
                  char category[50])//get  record  position to delete
{
    if (t == NULL)
        return NULL;
    else if (strcmpi(name, t->name) < 0)
        t->left = deleteBookPos(t->left, name, author, year, country, category);
    else if (strcmpi(name, t->name) > 0)
        t->right = deleteBookPos(t->right, name, author, year, country, category);
    else if ((t->left) && (t->right)) {
        sun temp;
        temp = findMax(t->left);
        strcpy(t->name, temp->name);
        strcpy(t->author, temp->author);
        strcpy(t->year, temp->year);
        strcpy(t->country, temp->country);
        strcpy(t->category, temp->category);
        t->right = deleteBookPos(t->right, name, author, year, country, category);
    } else {
        sun chill;
        if (t->left == NULL)
            chill = t->right;
        if (t->right == NULL)
            chill = t->left;
        return chill;
    }
    return t;
}

void deleteBook(sun tt)//handle delete record by book name
{
    sun t;
    char name[50], author[50], year[15], country[50], category[50];
    printf("\nplease enter the Book Name :");
    scanf("%s", name);
    t = deleteBookPos(tt, name, author, year, country, category);
    if (t) {
        printf("the Book was successfully Deleted \n");
    } else
        printf("try again\n");
}

int getMaxHeight(sun t){
    sun d,x=t;
    if (t){
   getMaxHeight(t->right);
   d=t;
   getMaxHeight(x->left);
    }
  return max(getHeight(t),getHeight(x));
}
void getHigh(sun t){
    if (t)
        printf("height of tree is %d\n",getMaxHeight(t));
}
