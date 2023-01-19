/*
Aley Khaled		6291
Abdallah Aloush		6325
Mazen AbouElHassen	6139
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<ctype.h>

typedef struct
{
    char* name;
    float value;
} Variable;

typedef struct BSTNode
{
    struct BSTNode* left;
    struct BSTNode* right;
    Variable variable;
} BSTNode;

typedef union
{
    char cdata;
    float fdata;
} item;

BSTNode* root = NULL;
Variable heapArray[100];
int counter=0;


///////////////////////
typedef struct
{
    item items[100];
    int top;
} stack;

stack* initialize()
{
    stack*s=(stack*)malloc(sizeof (stack));
    s->top=0;
    return s;
}
void push(stack*s,item x)
{
    s->items[s->top]=x;
    s->top++;
}

item pop(stack*s)
{
    s->top--;
    item value;
    value=s->items[s->top];
    return value;
}
int isEmpty(stack*s)
{
    return s->top==0;
}
item top(stack*s)
{
    return s->items[s->top-1];
}

int priority(char c)
{
    switch(c)
    {
    case '*':
    case '/':
    case '%':
        return 2;
    case '+':
    case '-':
        return 1;
    case '(':
    case ')':
        return 0;
    case '^':
        return 3;
    default :
        return -1;
    }
}

float evaluate(char x, float op1, float op2)
{
    switch(x)
    {
    case '+':
        return(op1+op2);
    case '-':
        return(op2-op1);
    case '*':
        return(op1*op2);
    case '/':
        return(op2/op1);
    case '%':
        return((int)op1%(int)op2);
    case '^':
        return(pow(op2,op1));
    default:
        return 0;
    }

}

int isnumber(char*s)
{
    int i;
    int count=0;
    for(i=0; i<strlen(s); i++)
    {
        if (isdigit(s[i]))
            count++;
    }
    if(count>0)
        return 1;
    else
        return 0;
}

int isValid (char c)
{
    if(isalnum(c)|| (c == '.') || (c == '=') || (isspace(c)) || priority(c)!=-1)
        return 1;
    else
        return 0;
}

///Add spaces
char* addSpaces(char*str1)
{
    char *str2=malloc(strlen(str1)*2);
    //str2[0]='\0';
    int counter1=0,counter2=0,flag=0;

    while(counter1<strlen(str1))
    {
        if(str1[counter1]=='-'&&flag)
        {
            str2[counter2++]=str1[counter1++];
        }
        else if(priority(str1[counter1])!=-1)
        {
            str2[counter2++]=' ';
            str2[counter2++]=str1[counter1++];
            str2[counter2++]=' ';
            flag=1;
        }
        else
        {
            str2[counter2++]=str1[counter1++];
            flag=0;
        }
    }
    str2[counter2]='\0';
    return str2;
}

///BST
BSTNode* newNode(char* name,float value)
{
    BSTNode* n=malloc(sizeof(BSTNode));
    n->variable.name = malloc(strlen(name)+1);
    strcpy(n->variable.name,name);
    n->variable.value=value;
    n->left=NULL;
    n->right=NULL;
    return n;
}

void Inorder(BSTNode *root)
{
    if(root == NULL)
        return;
    heapArray[counter++]=root->variable;
    Inorder(root->left);       //Visit left subtree
    printf("%s : ",root->variable.name);
    printf("%.2f\n",root->variable.value);  //Print data
    Inorder(root->right);      // Visit right subtree


}

void putBST(char* key, float value)
{
    BSTNode* newOne = newNode(key,value);
    BSTNode* temp=root;
    if (temp==NULL)
        root=newOne;
    else
    {
        while(1)
        {
            if(strcmp(temp->variable.name,key)>0)
            {

                if(temp->left==NULL)
                {
                    temp->left=newOne;
                    temp=temp->left;
                    break;
                }
                temp=temp->left;
            }
            else if (strcmp(temp->variable.name,key)<0)
            {

                if(temp->right==NULL)
                {
                    temp->right=newOne;
                    temp=temp->right;
                    break;
                }
                temp=temp->right;
            }
            ///Overwrite
            else
            {
                temp->variable.value=newOne->variable.value;
                break;
            }
        }
    }
}

BSTNode* searchBST(BSTNode* root,char*str)
{
    BSTNode* temp=root;
    int flag = 0;
    while(flag==0 && temp!=NULL)
    {
        if (strcmp(str,temp->variable.name)>0)
        {
            temp=temp->right;
        }
        else if (strcmp(str,temp->variable.name)<0)
        {
            temp=temp->left;
        }
        else if (strcmp(str,temp->variable.name)==0)
        {
            flag=1;
        }
    }
    if (!flag)
    {
        printf("VARIABLE NOT FOUND !!!");
        exit(-1);
    }
    return temp;
}
///END

float evaluatepostfix(char*postfix)
{
    stack*s=initialize();
    item op1,op2,value;
    item x,y;
    char*token=strtok(postfix," ");
    while (token!=NULL)
    {
        if(isnumber(token))
        {
            x.fdata=atof(token);
            push(s,x);
        }
        else if (isalpha(token[0]))
        {
            BSTNode* foundNode = searchBST(root,token);
            x.fdata = foundNode->variable.value;
            push(s,x);
        }
        else
        {
            op1.fdata=pop(s).fdata;
            op2.fdata=pop(s).fdata;
            y.cdata=token[0];
            value.fdata=evaluate(y.cdata,op1.fdata,op2.fdata);
            push(s,value);
        }

        token=strtok(NULL," ");
    }
    value.fdata=pop(s).fdata;
    return value.fdata;
}

char *fgetstr(char *string, int n, FILE *stream)
{
    char *result;
    result = fgets(string, n, stream);
    if(!result)
        return(result);

    if(string[strlen(string) - 1] == '\n')
        string[strlen(string) - 1] = 0;

    return(string);
}

int ArePair(char opening,char closing)
{
    if(opening == '(' && closing == ')')
        return 1;
    else if(opening == '{' && closing == '}')
        return 1;
    else if(opening == '[' && closing == ']')
        return 1;
    return 0;
}
int AreParanthesesBalanced(char* exp)
{
    stack*s=initialize();
    for(int i =0; i<strlen(exp); i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
        {
            item x;
            x.cdata = exp[i];
            push(s,x);
        }
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if(isEmpty(s) || !ArePair(top(s).cdata,exp[i]))
                return 0;
            else
                pop(s);
        }
    }
    return isEmpty(s);
}

void infixToPostfix(char*infix,char*postfix)
{
    stack*s=initialize();
    postfix[0]='\0';
    char*TOKEN=strtok(infix," ");
    while(TOKEN!=NULL)
    {
        if(strlen(TOKEN)==1)
        {
            if(isalnum(TOKEN[0]))
            {
                strcat(postfix,TOKEN);
                strcat(postfix," ");
            }
            else if(isEmpty(s) || TOKEN[0]=='(')
            {
                item x ;
                x.cdata=TOKEN[0];
                push(s,x);
            }
            else if (priority(TOKEN[0])>priority(top(s).cdata))
            {
                item z;
                z.cdata=TOKEN[0];
                push(s,z);
            }
            else if (TOKEN[0]==')')
            {
                char q[2];
                q[1]='\0';
                q[0]=pop(s).cdata;
                while(q[0]!='(')
                {
                    strcat(postfix,q);
                    strcat(postfix," ");
                    q[0]=pop(s).cdata;
                }

            }
            else
            {
                while(priority(TOKEN[0])<=priority(top(s).cdata))
                {
                    char g[2];
                    g[0]=pop(s).cdata;
                    g[1]='\0';
                    strcat(postfix,g);
                    strcat(postfix," ");

                }
                item m;
                m.cdata=TOKEN[0];
                push(s,m);
            }
        }
        else
        {
            strcat(postfix,TOKEN);
            strcat(postfix," ");
        }


        TOKEN=strtok(NULL," ");
    }

    while(s->top>0)
    {
        char g[2];
        g[0]=pop(s).cdata;
        g[1]='\0';
        strcat(postfix,g);
        strcat(postfix," ");
    }
    //printf("postfix: %s",postfix);
}

void checkSymbol(char* str)
{
    int flag=0;
    for(int i=0; i<strlen(str) ; i++)
    {
        if(!isValid(str[i]))
        {
            printf("INVALID SYMBOL !!!");
            exit(-1);
        }
        if(str[i]=='=')
            flag=1;

    }
    if (!flag)
    {
        printf("CAN'T FIND '=' OPERATION !!!");
        exit(-1);
    }

}

void validation(char* variableName)
{
    if(!isalpha(variableName[0]))
    {
        printf("INVALID VARIABLE NAME !!!");
        exit(-1);
    }
    for(int i=0; i<strlen(variableName); i++)
    {
        if(!isalnum(variableName[i]))
        {
            printf("INVALID VARIABLE NAME !!!");
            exit(-1);
        }
    }

}

void check(char* str)
{
    char* token = strtok(str,"= ");
    char variableName[20];
    strcpy(variableName,token);
    validation(variableName);
    token = strtok(NULL,"\n= ");
    if(!AreParanthesesBalanced(token))
    {
        printf("UNBALANCED PARANTHESES !!!");
        exit(-1);
    }
    char* equation=addSpaces(token);
    char* postfix=malloc(strlen(equation)+1);
    infixToPostfix(equation,postfix);
    free(equation);
    float result = evaluatepostfix(postfix);
    free(postfix);
    putBST(variableName,result);
}

void loadFile(char*filename)
{
    counter=0;
    FILE *fp = fopen(filename,"r");
    char str[500];

    if(fp == NULL)
    {
        perror("Error opening file");
        exit(-1);
    }
    while(fgetstr(str, 500, fp)!=NULL)
    {
        printf("%s\n",str);
        checkSymbol(str);
        check(str);
    }
    fclose(fp);
}

///TEST
void print2DUtil(BSTNode *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 10;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->variable.name);


    // Process left child
    print2DUtil(root->left, space);
}

    // Wrapper over print2DUtil()
void print2D(BSTNode *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

    // Function to swap the the position of two elements
void swap(Variable *a, Variable *b)
{
    Variable temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Variable arr[], int n, int i)
{
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].value > arr[largest].value)
        largest = left;

    if (right < n && arr[right].value > arr[largest].value)
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Main function to do heap sort
void heapSort(Variable arr[], int n)
{
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Heap sort
    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);

        // Heapify root element to get highest element at root again
        heapify(arr, i, 0);
    }
}

// Print an array
void printArray(Variable arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%s : %.2f\n",arr[i].name,arr[i].value);
}

int main()
{

    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
        {
            puts("Equations:");
            loadFile(filename);
            puts("----------------------------------");
            puts("Sorting by variable name:");
            Inorder(root);
            puts("----------------------------------");
            puts("Sorting by value:");
            heapSort(heapArray,counter);
            printArray(heapArray,counter);
            puts(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
        }
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
