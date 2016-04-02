/*
Given two SORTED Circular Linked Lists ,
Write a function to merge those two linked lists .
The First Linked List head should point to the final merged linked list .
The Final merged linked list should also be in SORTED order and a Circular Linked List.
You need to return the Length of Final SLL.

*********
The First linked list head should now point to the Final sorted(Ascending) Linked list First Node
*********
Ex : A: 0->3->5->10->20 (and 20 now pointing back to 0,instead of Null )
B: 1->2->6->11->21->50->70 (70 Pointing back to 1).

The Final Linked List is A:0->1->2->3->5->6->10->11->20->21->50->70 .

Note : Dont use Malloc or create any new nodes ,Only pointers need to be interchanged,
You can use temp pointers although.
Note : The Final Linked List should be  also be a circular Linked List where Last node is
pointing towards the first node.
Note : Return -1 for Invalid Inputs like NULL;

Input : head1 and head2 are Addresses of Two Circular Linked Lists heads .
Output :Return Length of New SLL .Modify the head1 value, such that it now points to 
Merged Sorted Circular SLL .

Difficulty : Medium
*/
#include <stdlib.h>
#include <stdio.h>

struct node{
	int data;
	struct node *next;
};
int len(node *l)
{
	node *temp = l;
	int i = 0;
	do
	{
		i++;
		temp = temp->next;
	} while (temp != l);
	return i;
}

int merge_circularlists(struct node **head1, struct node **head2)
{
	node *p = *head1, *q = *head2;
	struct node *t, *head;
	if (!p && !q)
		return -1;
	if (!p)
	{
		*head1 = q;
		return len(q);
	}
	if (!q)
	{
		*head1 = p;
		return len(p);
	}
	if (p->data > q->data)
	{
		head = q;
		t = q;
		q = q->next;
	}
	else
	{
		head = p;
		t = p;
		p = p->next;
	}
	do
	{
		if (p->data > q->data)
		{
			t->next = q;
			t = q;
			q = q->next;
		}
		else if (p->data < q->data)
		{
			t->next = p;
			t = p;
			p = p->next;
		}
		else
		{
			t->next = p;
			t = p;
			p = p->next;
			q = q->next;
		}
	} while (p != *head1 && q != *head2);
	if (q == *head2)
	{
		do
		{
			t->next = p;
			t = p;
			p = p->next;
		} while (p != *head1);
		t->next = head;
	}

	else if (p == *head1)
	{
		do
		{
			t->next = q;
			t = q;
			q = q->next;
		} while (q != *head2);
		t->next = head;
	}
	return len(head);
}