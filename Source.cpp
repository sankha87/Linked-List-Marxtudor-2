#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct Node
{
	int data;
	Node *link;
};

void display(struct Node *head_ref);
Node* push(struct Node *head_ref, int num);
void append(struct Node *head_ref, int num);
Node* del(struct Node *head_ref, int num);
void search(struct Node *head_ref, int num);
void count(struct Node *head_ref);
void addafter(struct Node *head_ref, int after, int num);
Node* addbefore(struct Node *head_ref, int before, int num);
Node* reverse(struct Node *head_ref);

void main()
{
	struct Node *head = NULL;
	int choice, num, after, before;
	while (1)
	{
		printf("\n\n1. Display \n");
		printf("2. Add node to empty list / Add at beginning \n");
		printf("3. Add node at the end \n");
		printf("4. Delete from List \n");
		printf("5. Search \n");
		printf("6. Count number of nodes \n");
		printf("7. Add after node \n");
		printf("8. Add before node \n");
		printf("9. Reverse List \n");
		printf("10. Exit \n");


		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			display(head);
			break;
		case 2:
			printf("Enter the number to be inserted: ");
			scanf("%d", &num);
			head = push(head, num);			//	while(1) - for checking Stack Overflow condition
											//  head = push(head, num);  - for checking Stack Overflow condition
			break;
		case 3:
			printf("Enter the number to be inserted: ");
			scanf("%d", &num);
			append(head, num);
			break;
		case 4:
			printf("Enter the number to be deleted: ");
			scanf("%d", &num);
			head = del(head, num);
			break;
		case 5:
			printf("Enter the number to be searched: ");
			scanf("%d", &num);
			search(head, num);
			break;
		case 6:
			count(head);
			break;
		case 7:
			printf("Enter the number to be inserted: ");
			scanf("%d", &num);
			printf("Enter the number after which to insert: ");
			scanf("%d", &after);
			addafter(head, after, num);
			break;
		case 8:
			printf("Enter the number to be inserted: ");
			scanf("%d", &num);
			printf("Enter the number before which to insert: ");
			scanf("%d", &before);
			head = addbefore(head, before, num);
			break;
		case 9:
			head = reverse(head);
			break;
		case 10:
			exit(1);
		default: printf("Invalid choice \n\n");
		}
	}
	_getch();
}
void display(struct Node *head_ref)
{
	struct Node *temp = head_ref;
	if (head_ref == NULL)
	{
		printf("List is empty \n\n");
		return;
	}
	while (temp != NULL)
	{
		printf("%d  ", temp->data);
		temp = temp->link;
	}
}

Node* push(Node *head_ref, int num)
{
	struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
	if (new_node == NULL)						// if while(1) loop is getting executed, after sometime new_node will not get any memory
		printf("Stack Overflow \n");			// that time Stack overflow condition occurs.
	else
	{
		new_node->data = num;
		new_node->link = head_ref;
		head_ref = new_node;
		return head_ref;
	}
}

void append(Node *head_ref, int num)
{
	if (head_ref == NULL)
	{
		printf("This function cannot be used to add a node to an Empty list \n");
		return;
	}
	struct Node *head_ref2 = head_ref;
	struct Node *new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->data = num;
	new_node->link = NULL;
	while (head_ref2->link != NULL)
		head_ref2 = head_ref2->link;
	head_ref2->link = new_node;
}

Node* del(Node *head_ref, int num)
{
	struct Node *temp, *ptr;
	if (head_ref == NULL)
	{
		printf("List is empty\n");
		return head_ref;			// not to update the value of start
	}
	if (head_ref->data == num)
	{
		temp = head_ref;
		head_ref = head_ref->link;
		free(temp);
		return head_ref;			// to update the value of start
	}
	ptr = head_ref;
	while (ptr->link != NULL)
	{
		if (ptr->link->data == num)
		{
			temp = ptr->link;
			ptr->link = temp->link;
			free(temp);
			return head_ref;		// not to update the value of start
		}
		ptr = ptr->link;
	}
	printf("%d is not present in List", num);
	return head_ref;				// not to update the value of start
}

void search(Node *head_ref, int num)
{
	struct Node *ptr = head_ref;
	int pos = 1;
	while (ptr != NULL)
	{
		if (ptr->data == num)
		{
			printf("%d found in %d position of the List", num, pos);
			return;
		}
		ptr = ptr->link;
		pos++;
	}
	printf("%d not found in the List", num);
}

void count(Node *head_ref)
{
	struct Node *ptr = head_ref;
	int i = 0;
	while (ptr != NULL)
	{
		ptr = ptr->link;
		i++;
	}
	printf("Number of nodes : %d", i);
}

void addafter(Node *head_ref, int after, int num)
{
	struct Node *ptr = head_ref, *temp;
	while (ptr != NULL)
	{
		if (ptr->data == after)
		{
			temp = (struct Node*)malloc(sizeof(struct Node));
			temp->data = num;
			temp->link = ptr->link;
			ptr->link = temp;
			return;
		}
		ptr = ptr->link;
	}
	printf("%d is not present in the List \n", after);
}

Node* addbefore(Node *head_ref, int before, int num)
{
	if (head_ref->data == before)
	{
		struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
		new_node->data = num;
		new_node->link = head_ref;
		head_ref = new_node;
		return head_ref;
	}

	struct Node *ptr = head_ref, *temp;
	while (ptr->link != NULL)
	{
		if (ptr->link->data == before)
		{
			temp = (struct Node*)malloc(sizeof(struct Node));
			temp->data = num;
			temp->link = ptr->link;
			ptr->link = temp;
			return head_ref;
		}
		ptr = ptr->link;
	}
	printf("%d is not present in the List \n", before);
	return head_ref;
}

Node* reverse(Node *head_ref)
{
	struct Node *prev, *ptr, *next;
	prev = NULL;
	ptr = head_ref;
	while (ptr != NULL)
	{
		next = ptr->link;
		ptr->link = prev;
		prev = ptr;
		ptr = next;
	}
	head_ref = prev;
	return head_ref;
}
