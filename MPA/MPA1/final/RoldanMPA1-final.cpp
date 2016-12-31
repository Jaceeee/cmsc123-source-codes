/*
 *I declare upon my honor that I did this MPA by myself
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define MAX 10000
#define SIZE 30

using namespace std;
void linearChk(bool, bool, bool, int, int, int);
class node{
public:
    char str[SIZE];
    int type;
    node* next;

    node(){
        next = NULL;
        type = 0;
    }
    node(int type, char x[]){
        strcpy(str, x);
        next = NULL;
        this->type = type;
    }
};

class List{
protected:
    node* head;
    node* tail;
    int size;
public:
    List(){
        head = tail = NULL;
        size = 0;
    }
    ~List(){
        deleteAll();
    }
    void append(int,char[]);
    bool deleteItem(int);
    void display();
    void deleteAll();
    void performCount();
    void determineComp(int);
    bool incrementDirection();
    void determineBounds(char*,char*,int,bool,int,bool,int);
    int determineIncrement();
    int determineTypeInc();
    int getSize(char*);
};

int List::getSize(char* a){
    int ja;
    for(ja=0; a[ja] != '\0'; ja++);
    return ja;
}

int List::determineTypeInc(){
    node *tmp = head;
    while(tmp->type != 3){
        tmp = tmp->next;
    }
    for(int i = 0; tmp->str[i]!='\0'; i++){
        if(tmp->str[i] == '+' || tmp->str[i] == '*')
            return 1;
        else if(tmp->str[i] == '-' || tmp->str[i] == '/'){
            return 2;
        }
    }
    return 0;
}

void List::determineComp(int a){
    node* tmp = head;
    bool symbol;
    char *pt1, *pt2, *token;
    char buff[20], tmp1[20];
    while(tmp!=NULL){
        if(tmp->type == 1){
            strcpy(buff,tmp->str);
            int i = 0;
            token = strtok(buff," =");
            while(token != NULL){
                if(token[0] == '='){
                    token = strtok(NULL," ");
                    pt1 = token;
                    strcpy(tmp1,pt1);
                    break;
                }
                token = strtok(NULL," ");
                i++;
            }
        }
        if(tmp->type == 2){
            char buff2[20];
            int asteriskChk = 0;
            strcpy(buff2,tmp->str);

            for(int i = 0; buff2[i] != '\0'; i++){
                if(buff2[i] == '*' || buff2[i] == '/' || buff2[i] == '+' || buff2[i] == '-'){
                    a++;
                    asteriskChk++;
                }
            }

            char* token = strtok(buff2," 1234567890*");
            char holder[20];
            strcpy(holder,buff2);
            while(token!=NULL){
                if(token[0] == '<' || token[0] == '>'){
                    if(token[0] == '<'){
                        symbol = true;
                    }
                    else{
                        symbol = false;
                    }
                    a++;
                    token = strtok(NULL, " ");
                    pt2 = token;
                    tmp = tmp->next;
                    int ast = 0;
                    int i,tmp2, m;
                    char buff3[20];

                    for(i = 0; tmp->str[i] != '*' && tmp->str[i] != '/' && tmp->str[i] != '+' && tmp->str[i] != '-'; i++);

                    for(m = 0; tmp->str[i] != '\0'; i++){
                        if(tmp->str[i] >= '0' && tmp->str[i] <= '9'){
                            buff3[m] = tmp->str[i];
                            m++;
                        }
                    }

                    buff3[m] = '\0';
                    tmp2 = atoi(buff3);
                    bool k = (asteriskChk>0) ? true : false;
                    pt1 = tmp1;
                    determineBounds(pt1,pt2,a,k,tmp2,symbol,a);
                    break;
                }
                token = strtok(NULL, " ");
            }
        }
        tmp = tmp->next;
    }
}

bool List::incrementDirection(){
    node *tmp = head;
    while(tmp != NULL){
        if(tmp->type == 3){
            for(int i = 0; tmp->str[i] != '\0'; i++){
                if(tmp->str[i] == '+'){
                    return true;
                }
                else if(tmp->str[i] == '-'){
                    return false;
                }
            }
        }
        tmp = tmp->next;
    }
}

void List::determineBounds(char* f1, char* f2, int operations, bool rtChk, int logChk, bool symbolChk, int compOp){
    int bound1, bound2, increment, type, opCt = 0;
    bool flag = false, flag2 = false, incrementDir = incrementDirection();
    int i;
    node *tmp = head;
    while(tmp!=NULL){
        if(tmp->type == 2){
            for(i = 0; tmp->str[i] != '\0'; i++){
                if(tmp->str[i] == '*'){
                    opCt++;
                }
            }
        }
        tmp = tmp->next;
    }
    increment = determineIncrement();
    type = determineTypeInc();

    if(f2[0] > 48 && f2[0] <57){
        flag2 = true;
        bound2 = atoi(f2);
    }
    if(f1[0] > 48 && f1[0] < 57){
        flag = true;
        bound1 = atoi(f1);
    }
    if(flag == false && flag2 == false){
        printf("T(n) = %i%s - %i%s + %i",operations,f2,operations,f1,operations+2);
        return;
    }

    if(type == 1 && rtChk == false){
        if(flag == true){

            if(flag2 == true){
                if((bound1 > bound2 && symbolChk == true && incrementDir == true) || (bound1 < bound2 && symbolChk == false && incrementDir == false)){
                    printf("T(n) = infinite\n");
                    return;
                }
                else if((bound1 > bound2 && symbolChk == true && incrementDir == false) || bound1 < bound2 && symbolChk == false && incrementDir == true){
                    printf("T(n) = 2\n");
                    return;
                }
            }
            else if(flag2 == false){
                if(symbolChk == false){
                    printf("T(n) = infinite\n");
                    return;
                }
            }
        }
        else if(flag==false){
            if(symbolChk == false){
                printf("T(n) = %i\n",compOp+1);
                return;
            }
            else if(symbolChk == true){
                printf("T(n) = 2\n");
                return;
            }
        }
    }
    else if(type == 2 && rtChk == false){
        if(flag == true){
            if(flag2 == true){
                if((bound1 > bound2 && symbolChk == false && incrementDir == true) || (bound1 < bound2 && symbolChk == true && incrementDir == false)){
                    printf("T(n) = infinite\n");
                    return;
                }
                else if((bound1 > bound2 && symbolChk == true && incrementDir == false) || bound1 < bound2 && symbolChk == false && incrementDir == true){
                    printf("T(n) = 2\n");
                    return;
                }
            }
            else{
                if(symbolChk == true){
                    printf("T(n) = infinite\n");
                    return;
                }
            }
        }
        else{
            if(symbolChk == false){
                printf("T(n) = %i\n",compOp+1);
                return;
            }
            else{
                printf("T(n) = 2\n");
                return;
            }
        }
    }
    if(increment == 2 || increment == 3){
        if(increment == 2){
            if(flag2 == false){
                if(bound1 == 1){
                    printf("T(n) = %in/%i + 2\n", operations,logChk);
                    return;
                }
                else{
                    int g = operations * (bound1 - 1) - 2;
                    printf("T(n) = %in/%i - %i\n",operations,logChk, g);
                }
            }
            return;
        }

        else if(increment == 3){
            if(flag == true){
                if(bound1 == 1){
                    printf("T(n) = %ilog (%i) n + 2\n",operations,logChk);
                }
                else{
                    int g = operations * (bound1 - 1);
                    printf("T(n) = %ilog (%i) n",operations,logChk);
                    if(g < 2){
                        g -= 2;
                        printf(" + %i\n", g*-1);
                    }
                    else{
                        g -= 2;
                        printf(" - %i\n", g);
                    }
                }
                return;
            }
        }
    }
    if(rtChk == false){
        if(flag == true){
            if(flag2 == true){
                if(bound1 != 1){
                    printf("T(n) = %i\n",operations*(bound2-bound1+1)+2);
                }
                else{
                    printf("T(n) = %i\n",bound2*operations+2);
                }
            }
            else{
                if(bound1 != 1){
                    int newNum = ((operations * (bound1 - 1)) - 2) * -1;
                    printf("T(n) = %in",operations);
                    if(newNum > 0){
                        printf(" + %i\n", newNum);
                    }
                    else if(newNum < 0){
                        printf(" %i\n", newNum);
                    }
                }
                else{
                    printf("T(n) = %in + 2\n",operations);
                }
            }
        }
    }
    else{
        if(opCt == 1){
            printf("T(n) = %i sqrt(n) + 3\n",operations);
        }
        else if(opCt == 2){
            printf("T(n) = %i cubert(n) + 4\n",operations);
        }
        else{
            printf("T(n) = %i (%i root of)(n) + %i\n",operations, opCt+1, opCt+2);
        }
    }
}

int List::determineIncrement(){
    node* tmp = head;

    while(tmp->type!=3){
        tmp = tmp->next;
    }

    for(int i = 0; tmp->str[i] != '\0'; i++){
        if(tmp->str[i] == '+' || tmp->str[i] == '-'){
            if(tmp->str[i+1] == '+' || tmp->str[i+1] == '-'){
                return 1;
            }
            else if(tmp->str[i+1] == '='){
                return 2;
            }
        }
        else if(tmp->str[i] == '/' || tmp->str[i] == '*'){
            return 3;
        }
    }
    return 0;
}

void List::performCount(){
    int operations = 0;
    node *tmp = head;
    if(tmp == NULL){
        return;
    }
    while(tmp != NULL){
        if(tmp->type == 3){
            for(int i = 0; tmp->str[i]!='\0'; i++){
                if(tmp->str[i] == '+' || tmp->str[i] == '-' || tmp->str[i] == '*' || tmp->str[i] == '/' || tmp->str[i] == '='){
                    operations++;
                    if(tmp->str[i+1] == '+' || tmp->str[i+1] == '-' || tmp->str[i+1] == '='){
                        i+=2;
                    }
                }
            }
        }
        tmp = tmp->next;
    }
    determineComp(operations);
}

void List::deleteAll(){
    while(size>0){
        deleteItem(1);
    }
}


void List::display(){
    node* trav = head;
    int i = 1;
    while(trav != NULL){
        cout << i << " ";
        printf("%s\n", trav->str);
        trav = trav->next;
        i++;
    }
}
void List::append(int type, char str[]){
    node* x = new node(type,str);

    if(size==0){
        head = tail = x;
    } else{
        tail->next = x;
        tail = x;
    }

    size++;
}

bool List::deleteItem(int pos){
    node *tmp = head,  *del;
    int i = 1;

    if(pos < 1 || pos > size){
        return false;
    } else{
        if(pos == 1){
            del = head;
            head = del->next;
            del->next = NULL;
        }
        else{
            while(i < pos - 1){
                tmp = tmp->next;
                i++;
            }
            del = tmp->next;
            tmp->next = del->next;
            del->next = NULL;

            if(tail == del){
                tail = tmp;
            }
        }

        size--;
        delete del;
    }

    return true;
}

void performParse(List*); //main parser function

int main(){
    List l;
    performParse(&l);
	return 0;
}

void performParse(List* l){
    int j = 0;
    bool flag = false;
    bool flag2 = false;
    bool checker;
    FILE *inputFilePointer;
    char buff[MAX];
    char copy[MAX];
    char str[3][MAX] = {"Initialization","Condition","Increment"};
    int i;
    inputFilePointer = fopen("sample-test-cases.txt","r");

    if(inputFilePointer == NULL){
        perror("File not found\n");
    }

    while(fgets(buff, MAX-1, inputFilePointer) != NULL){
        if(buff[0] == '}'){
            l->performCount();
            cout << endl;
            l->deleteAll();
        }

        j = 0;
        char *token;
        char forCheck[4];
        strcpy(copy,buff);
        token = strtok(copy, ";{}()\n\t");

        forCheck[0] = buff[0];
        forCheck[1] = buff[1];
        forCheck[2] = buff[2];
        forCheck[3] = '\0';

        if(token!=NULL){
            if(!strcmp(forCheck,"for")){
                //printf("\n\n\n");

                if(flag == true && flag2 == true){
                    flag2 = false;
                }

                flag = false;
                token = strtok(NULL,";()}{\n");
                while(token != NULL){

                    if(j<3){
                        l->append(j+1,token);
                    }
                    token = strtok(NULL, ";(){}\n");
                    j++;
                }
            }
            else{
                bool emptyChk = true;
                for(i = 0;buff[i] != '\0'; i++){
                    if(buff[i] == ';'){
                        emptyChk = false;
                    }
                }
                if(emptyChk == false){
                    l->append(3, buff);
                    if(flag == false){
                        flag = true;
                    }
                    if(buff[0] != '}'){
                        for(i = 0; buff[i] != '\0'; i++){
                            if(buff[i] == ';'){
                                buff[i] = '\0';
                            }
                        }
                    }
                }
            }
            if(flag == true){
                flag2 = true;
            }
        }
    }

    fclose(inputFilePointer);
}
