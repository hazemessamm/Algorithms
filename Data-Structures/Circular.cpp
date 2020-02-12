#include<stdio.h>
#include<conio.h>

// Structure for the Node
struct Node {
	int data ;
	Node *next;
	Node *prev;
};

// Initialize the Linked List
void initialize(Node *&head){
	head = NULL;
}

// Insert at End
void insert(Node *&head,int x){
	Node *temp = new Node();
	temp->data = x;
	temp->next = temp;
	temp->prev = temp;
	
	if(head == NULL){
		head = temp ;
		return;
	}
	
	Node *p = head->prev;
	p->next = temp;
	temp->prev = p;
	temp->next = head;
	head->prev = temp;
}

// Display the Linked List
void display(Node *&head){
	if(head == NULL){
		printf("Empty Linked List");
		return;
	}
	
	Node *p = head;
	do{
		printf("%d ",p->data);
		p=p->next;
	}
	while(p != head);
}

int main(){
	Node* head ;
	initialize(head);
	insert(head,1);
	insert(head,2);
	insert(head,3);
	
	printf("+===Displaying Linked List===+\n");
	display(head);
	printf("\n+============================+");
	
	getch();
	return 0;
}
