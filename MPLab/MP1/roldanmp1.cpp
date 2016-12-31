#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000            //maximum number of chars in buff stream

typedef struct elem{ //used linked list to avoid redundant addition of header files
	char item[MAX]; //data
	struct elem *next;
}node;

typedef struct{
	node *head, *tail;
	int size;
}list;

void init(list*);
void append(list*,char[MAX]);
void display(list);   //used for tracing purposes only
bool check(list*,char[MAX]);        //checks whether header file was added already

using namespace std;

void headerContentsFile(FILE*,list*,bool);  //takes note of the header file being included, the list of header f's
//third argument is a boolean value that determines whether a newline is to be printed after the first directive
int main(){
	FILE *ifp;
	list l;
	init(&l);
	ifp = fopen("inputFile.cpp","r");
	if(ifp == NULL){
		printf("File not found; error.\n");
	}

	headerContentsFile(ifp,&l,false); //false at first because first call

    display(l);
	fclose(ifp);
	return 0;
}
//needed a boolean arg bec. not able to print a newline when the second #include directive is called in inputFile.cpp
void headerContentsFile(FILE* ifp,list *l,bool checker){
	FILE *ofp;
	int a=0, flag = 0, counter = 0;
	char buff2[MAX], buff[MAX], check2[MAX];
	ofp = fopen("outputFile.out","a");

	if(checker)     //writes newline when needed for opening the first header file in a new sequence of header files
        fprintf(ofp,"\n");
	while(fgets(buff, MAX-1, ifp)!=NULL){
		char *parse;
		strcpy(buff2,buff);
		parse = strtok(buff2," \"");

		if(!strcmp(parse,"#include")){  //checks if statement is a preprocessor directive
			parse = strtok(NULL, " \"");

            if(check(l,parse)){
                FILE *sfp = fopen(parse,"r");
                append(l,parse);
                if(ifp==NULL)
                    printf("error, file not found.\n");
                if(counter<1)
                    headerContentsFile(sfp,l,false);    //false if first call
                else
                    headerContentsFile(sfp,l,true); //true if second and onwards

                fclose(sfp);
                counter++;
            }

		}
		else{
			fprintf(ofp,"%s",buff); //writes line if not a directive
		}
	}

	fprintf(ofp,"\n"); //writes a newline to the file after each header file is scanned

	fclose(ofp);
}

void init(list* l){
	l->size = 0;
	l->head = l->tail = NULL;
}

void append(list* l,char x[MAX]){
	node *n = new node;
	strcpy(n->item, x);
	n->next = NULL;
	if(l->size==0){
		l->head = l->tail = n;
	}
	else{
		l->tail->next = n;
		l->tail = n;
	}
	l->size++;
}

void display(list l){           //for tracing and checking only
	node *tmp = l.head;
	while(tmp!=NULL){
		printf("%s ",tmp->item);
		tmp = tmp->next;
	}
	printf("\n");
}

bool check(list *l, char x[MAX]){ //traverses linked list to check for repetitions
    node *tmp = l->head;
	while(tmp!=NULL){
		if(!strcmp(tmp->item,x))
            return false;
		tmp = tmp->next;
	}
	return true;
}
