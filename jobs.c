#include "main.h"

Slist *head = NULL;

int insert_at_last(Job data)
{
	//1.create node
	Slist *new = (Slist *)malloc(sizeof(Slist));

	//2.error check
	if(new == NULL)
		return FAILURE;

	//3.update the data and link part
	new -> data = data;
	new -> link = NULL;

	//4.check whether list is empty or not
	if(head == NULL)
	{
		//update head
		head = new;
		return SUCCESS;
	}
	//5.traverse till reach the last node
	//Create local reference
	Slist *temp = head;
	while(temp -> link != NULL)
	{
		temp = temp -> link;
	}
	//6.Establish the link between last node and new node
	temp -> link = new;
	return SUCCESS;

}


void print_jobs()
{
    Slist *temp = head;

    // traverse to the list
    while(temp != NULL)
    {
        printf("[%d]\t%s\t\t%s\n", temp->data.stop_count, temp->data.status, temp->data.input_name);
        temp = temp -> link;
    }
}
