#include<stdio.h>
#include<conio.h>

// Structure for the Node
struct Node {
	int data ;
	Node *next;
};

// Initialize the Linked List
void initialize(Node *&head){
	head = NULL;
}

// Insert at End
void insert(Node *&head,int x){
	Node *temp = new Node();
	temp->data = x;
	temp->next = NULL;

	if(head == NULL){
		head = temp ;
		return;
	}

	Node *p = head;
	while(p->next != NULL){
		p=p->next;
	}
	p->next=temp;
}
void insertHead(Node *&root, int x)
{
    Node *temp = new Node();
	temp->data = x;
	temp->next = root;
	root = temp;
}

// Display the Linked List
void display(Node *&head){
	if(head == NULL){
		printf("Empty Linked List");
		return;
	}

	Node *p = head;
	while(p != NULL){
		printf("%d \n",p->data);
		p=p->next;
	}
}
int maximum(Node *root)
{
    Node *p = root;
    int x = root->data;
    while(p != NULL)
    {
        if(x < p->data)
        {
            x = p->data;
        }
        p = p->next;
    }
    return x;
}
int sum(Node *root)
{
    Node *p = root;
    if (p != NULL)
    {
        return p->data + sum(p->next);
    }
}
void deletex(Node *&root, int x)
{
    Node *p = root;
    Node *q = root;
    p = p->next;
    if(root->data == x)
    {
        root = root->next;
        delete q;
        return;
    }
    while(p != NULL && p->data != x)
    {
        q = q->next;
        p = p->next;
    }
    q->next = p->next;
    delete p;

}

int main()
{
	Node* list1 ;
	initialize(list1);
	insertHead(list1,1);
	insertHead(list1,1);
	insertHead(list1,2);
	insertHead(list1,3);
	insertHead(list1,4);
	insertHead(list1,5);

	printf("+===Displaying Linked List===+\n");
	deletex(list1, 5);
	display(list1);
	int x = sum(list1);
	printf("%d\n", x);
	printf("\n+============================+\n");

	getch();
	return 0;
}
