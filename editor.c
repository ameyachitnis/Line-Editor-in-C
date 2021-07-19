#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define red printf("\033[31m");
#define blue printf("\033[34m");
#define magenta printf("\033[35m");
#define cyan printf("\033[36m");
#define yellow printf("\033[33m");
#define green printf("\033[32m");
#define reset printf("\033[0m");
#define bold printf("\033[1m");
#define underline printf("\033[4m");
typedef struct node
{
  char data[80];
  struct node *next;
  struct node *prev;
} NODE;
NODE *head, *newnode, *t;
int changed = 0;
char fname[100];
int noofl()
{
        int length=0;
        for(t=head;t!=NULL;t=t->next)
                length++;
        return(length);
}
void display (int s, int e)
{
	if(s> noofl() || e>noofl())
	{
		printf("Line Number Out Of Range \n");
		return;
	}
	int i;
	for (i = 1, t = head; i < s; i++, t = t->next);
	for (; i <= e; i++, t = t->next)
    	{
        	printf ("%d : %s\n", i, t->data);
    	}

}
void update (int s, int e)
{
	if(s > noofl() || e > noofl())
	{
		printf("Line Number Out Of Range \n");
		return;
	}
	int i, j, cnt;
  	char line[100];
  	for (t = head; t != NULL; t = t->next, cnt++);
  	if (s == 1 && s == e)
    	{
       		printf ("\nThe Original String is : ");
      		puts (head->data);
      		NODE *temp;
      		printf ("Enter The New Line : ");
      		fflush (stdin);
      		gets (line);
      		temp = (NODE *) malloc (sizeof (NODE));
      		strcpy (temp->data, strcat (line, "\n"));
      		temp->next = head->next;
      		head = temp;
    	}
  	else if (s == cnt && s == e)
    	{
      //NODE *temp;
      		for (t = head; t->next != NULL; t = t->next);
      		printf ("The Original String is : ");
      		puts (t->data);
      		printf ("Enter The New Line : ");
      		fflush (stdin);
      		gets (line);
      //temp=(NODE *)malloc(sizeof(NODE));
      		strcpy (t->data, strcat (line, "\n"));
      //t->next=temp->next;
      //t=temp;


    	}	
  	else if (s != 1 && s != cnt && s == e)
    	{
      		for (t = head, i = 1; i < s; t = t->next, i++);
      		printf ("The Original String is : ");
      		puts (t->data);
      		printf ("\nEnter The New Line : ");
      		fflush (stdin);
      		gets (line);
      		strcpy (t->data, strcat (line, "\n"));


    	}
  	else if (s != e)
    	{
      		for (t = head, i = 1; i < s; t = t->next, i++);
      		j = 1;
      		while (j <= e)
		{
	  		printf ("\nEnter The Original String : ");
	  		puts (t->data);
	  		printf ("\nEnter the New Line : ");
	  		fflush (stdin);
	  		gets (line);
	  //temp=(NODE *)malloc(sizeof(NODE));
	  		strcpy (t->data, strcat (line, "\n"));
	  		j++;
	  		t = t->next;
	 
		}

	}


}

NODE * getnode (char *s)
{
  	NODE *temp;
  	temp = (NODE *) malloc (sizeof (NODE));
  	strcpy (temp->data, s);
  	temp->next = NULL;
  	temp->prev = NULL;
  	return (temp);
}

void append ()
{
   	char line[100];
  	printf ("Enter Text(. to Quit)\n");
  	fflush (stdin);
  	gets (line);
  	for (t = head; t->next != NULL; t = t->next);
  	while (strcmp (line, ".") != 0)
    	{
      		newnode = getnode (strcat (line, "\n"));
      		t->next = newnode;
      		newnode->prev = t;
      		t = newnode;
      		fflush (stdin);
      		gets (line);
      		changed = 1;

    	}
  	printf ("Lines Added\n");
}

void save ()
{
  	FILE *fp1;
  	fp1 = fopen (fname, "w");
  	if (!fp1)
    	{
      		printf ("File not saved");
      		exit (0);
    	}
  	else
    	{
      		for (t = head; t != NULL; t = t->next)
		{
	  		fputs (t->data, fp1);
		}

    	}
  	printf ("File Saved Successfully\n");
}

void saveas ()
{
 	FILE *fp1;
  	char newname[20];
  	printf ("\nEnter The New File Name  :\t");
  	gets (newname);
  	fp1= fopen (newname, "w");
  	if (!fp1)
    	{
      		printf ("File not saved!!");
      		return;

    	}
  	else
    	{
      		for (t = head; t != NULL; t = t->next)
		{
	  		fprintf(fp1,"%s",t->data);
		}
    	}
  	printf ("\nNew File Saved Sucessfully");
	fclose(fp1);
  	return;
}

void delete (int s, int e)
{
	if(s > noofl() || e > noofl())
	{
		printf("\nOut Of Range");
		return;
	}
	if(noofl()==1)
	{
		printf("\nCannot delete last line ");
		return;
	}
 	int i, cnt = 0;
  	NODE *del;
  	for (t = head; t != NULL; t = t->next, cnt++);
  //printf ("%d", cnt);
  	if (s == 1 && s == e)
    	{
      		del = head;
      		head = head->next;
      		head->prev = NULL;
      		free (del);
    	}
  	else if (s == 1 && e > 1)
    	{
      	
     	 	for (i = s; i <= e; i++)
		{
		  	del = head;
		  	head = head->next;
	  		head->prev = NULL;
	  		free (del);
		}
	}
  	else if (s == e && s != 1 && s != cnt)
    	{
      	
      		for (i = 1, t = head; i < s - 1; i++, t = t->next);
      		del = t->next;
      		t->next = del->next;
      		del->next->prev = t;
      		free (del);
    	}
  	else if (s == cnt && s == e)
    	{
      		for (i = 1, t = head; i < cnt - 1; i++, t = t->next);
      //puts (t->data);
      		del = t->next;
      		t->next = NULL;
      		free (del);


    	}
  	else if (s != e)
    	{
   
      //	
      		for (i = 1, t = head; i < s - 1; i++, t = t->next);
      		for (; i < e; i++)
		{
	 		del = t->next;
	  		t->next = del->next;
	  		del->next->prev = t;
	  		free (del);

		}
    	}
}

void insert (int s, int e)
{
	if(e > noofl())
	{
		printf("Out Of range");
		return;
	}
   	char line[100];
  	int cnt = 0, i, j;
  	for (t = head; t != NULL; t = t->next, cnt++);
  /*    printf("Enter Text\n");
     fflush(stdin);
     gets(line);
   */
  	if (s == 1 && s == e)
    	{
      		printf ("Enter Text\n");
      		fflush (stdin);
      		gets (line);
      		newnode = getnode (strcat (line, "\n"));
      		newnode->next = head;
      		head = newnode;
      		head->prev = NULL;
    
	}
  	else if (s == cnt && s == e)
    	{
      		printf ("Enter Text\n");
      		fflush (stdin);
      		gets (line);
      		newnode = getnode (strcat (line, "\n"));
      		for (t = head; t->next != NULL; t = t->next);
      		t->next = newnode;
      		newnode->prev = t;
      //newnode->next=NULL;
    	}
  	else if (s != 1 && s != cnt && s == e)
    	{
      		printf ("Enter Text\n");
      		fflush (stdin);
      		gets (line);
      		for (t = head, i = 1; i < s - 1; t = t->next, i++);
      		newnode = getnode (strcat (line, "\n"));
      		newnode->next = t->next;
      		t->next = newnode;
      		newnode->prev = t;
     		 newnode->next->prev = newnode;
    	}
  	else if (s != e)
    	{
      		for (t = head, j = 1; j < e - 1; t = t->next, j++);
      		printf (" In Multiline \n");
		for (i = 1; i <= s; i++)
		{
	  		printf ("Enter Line : ");
	  		fflush (stdin);
	  		gets (line);
	  		newnode = getnode (strcat (line, "\n"));
	  		newnode->next = t->next;
	  		t->next = newnode;
	  		newnode->prev = t;
	  		newnode->next->prev = newnode;
	  		t = newnode;
	  //t=t->next;
	  		changed = 1;

		}
      }
}

void move (int s, int e, int dest)
{
	if (dest > noofl()  || s> noofl() || e> noofl())
        {
                printf("Out Of Range");
                return;
        }

	int i, cnt = 0;
  	NODE *temp1, *temp2;
	for (t = head; t != NULL; t = t->next, cnt++);
	if (dest == -1 && s > 0 && s <= cnt && e > 0 && e <= cnt)
    	{
      		if (s == e)
		{
		}

      		else if (s == 1 && e != s)
		{
	  		temp1 = head;
	  		head = head->next;
	  		for (i = 1, t = head; i < e - 1; t = t->next, i++);
	  		temp1->next = t->next;
	  		temp1->prev = t;
	  		t->next = temp1;
		}
      		else if (s != 1 && s != e)
		{
	  		if (e == 1)
	   		{
	      			for (i = 1, t = head; i < s - 1; i++, t = t->next);
	      			temp1 = t->next;
	      			t->next = temp1->next;
	      			temp1->next->prev = t;
	      			temp1->next = head;
	      			head->prev = temp1;
	      			head = temp1;
	   		}
	  		else if (e != 1)
	    		{
	      			for (i = 1, t = head; i < s - 1; i++, t = t->next);
	      			temp1 = t->next;
	      			t->next = temp1->next;
	      			temp1->next->prev = t;
				for (i = 1, t = head; i < e - 1; t = t->next, i++);
	      			temp1->next = t->next;
	      			t->next->prev = temp1;
	      			t->next = temp1;
	    		}
		}
    	}

  	else if (dest != -1 && s > 0 && s <= cnt && e > 0 && e <= cnt)
    	{

      		if (s == e && s == dest)
		{
		}

      		else if (s == e && s != dest && s == 1)
		{
	  		temp1 = head;
	  		head = head->next;
			for (i = 1, t = head; i < dest - 1; t = t->next, i++);
	 	 	temp1->next = t->next;
	  		t->next->prev = temp1;
	  		t->next = temp1;
		}
      		else if (s == e && s != dest && s != 1)
		{
	  		for (i = 1, t = head; i < s - 1; i++, t = t->next);
	  		temp1 = t->next;
	  		t->next = temp1->next;
	  		temp1->next->prev = t;
			for (i = 1, t = head; i < dest - 1; t = t->next, i++);
	  		temp1->next = t->next;
	  		temp1->next->prev = temp1;
	  		t->next = temp1;
	  		temp1->prev = t;
		}
      		else if (s == 1 && s != e)
		{
	  		temp1 = head;
	  		head = head->next;
	  //        head->prev=NULL;
	 		for (i = 1; i < e - 1; i++, head = head->next);
	  		temp2 = head;
	  //temp2->next=NULL;
	  		head = head->next;
	  		head->prev = NULL;
			for (i = 1, t = head; i < dest - 1; i++, t = t->next);
			temp2->next = t->next;
	  		t->next = temp1;
	  		temp1->prev = t;
	  		temp2->next->prev = temp2;


		}
      		else if (s != 1 && s != e && dest == 1)
		{
	  		for (i = 1, t = head; i < s - 1; i++, t = t->next);
	  		temp1 = t->next;
	  		for (i = 1, temp2 = head; i < e; i++, temp2 = temp2->next);
	  		t->next = temp2->next;
	  		temp2->next->prev = t;
	  		temp2->next = head;
	  		head->prev = temp2;
	  		temp1->prev = NULL;
	  		head = temp1;
		}
      		else if (s != 1 && s != e && dest != 1)
		{
	  		for (i = 1, t = head; i < s - 1; i++, t = t->next);
	  		temp1 = t->next;
	  		for (i = 1, temp2 = head; i < e; i++, temp2 = temp2->next);
	  		t->next = temp2->next;
	  		temp2->next->prev = t;
	  		for (i = 1, t = head; i < dest - 1; t = t->next, i++);
	  		temp2->next = t->next;
	  		temp2->next->prev = temp2;
			t->next = temp1;
	  		temp1->prev = t;
		}
		

   	}



}

void copy (int s, int e, int dest)
{
  	NODE *temp, *temp1;
  	int i, cnt = 0;
  	for (t = head; t != NULL; t = t->next, cnt++);
	if (dest == -1 && s >noofl() || dest==-1 && e > noofl())
        {
                        printf("Out Of Range");
                        return;
        }
	else if (dest == -1 && s > 0 && s <= cnt && e > 0 && e <= cnt + 1)
    	{
      		for (i = 1, t = head; i < s; i++, t = t->next);
      		temp = getnode (t->data);
      		if (e == 1)
		{
			temp->next = head;
	  		head->prev = temp;
	  		head = temp;

		}
      		else if (e >= cnt + 1)
		{
	  		for (t = head; t->next != NULL; t = t->next);
	  		t->next = temp;
	  		temp->prev = t;
		}
     		else
		{
	  		for (i = 1, t = head; i < e - 1; i++, t = t->next);
	  		temp->next = t->next;
	  		temp->prev = t;
	  		t->next = temp;
		}
    	}
	else if (dest != -1 && s>noofl() || dest!=-1 && e > noofl())
	{
		printf("Out Of Range");
		return;
	}
  	else if (dest != -1 && s > 0 && s <= cnt && e > 0 && e <= cnt)
    	{
      		for (i = 1, t = head; i < s; i++, t = t->next);
      		temp = getnode (t->data);
      		temp1 = temp;
      		t = t->next;
      		for (i = 1; i <= e - s; i++)
		{
	  		newnode = getnode (t->data);
	  		temp1->next = newnode;
	  		newnode->prev = temp1;
	  		temp1 = newnode;
	  		t = t->next;
		}
      		for (i = 1, t = head; i < dest - 1; i++, t = t->next);
      		temp1->next = t->next;
      		t->next->prev = temp1;
      		t->next = temp;
      		temp->prev = t;
    	}

}

void adddata (char name[10])
{
  	FILE *fptr;
  	char str1[100];
  	fflush (stdin);
  	fptr = fopen (name, "w+");
  	if (!fptr)
  	{
      		printf ("error");
    	}
  	printf ("\n\t\t\t\t\t\tEnter The String To Be Written Without Spaces : ");
//int i=0;
//do
//{
  	scanf ("%s", str1);
  //fgets(str1,100,stdin);
  	fputs (strcat (str1, "\n"), fptr);
//}while(str1[i]!='\n');
  	fclose (fptr);

}

main (int ac, char *av[])
{
	red;
	bold;
	printf("\n\t\t\t\t\t***------------- LINE EDITOR ---------------***");
	reset;
	reset;
	yellow;
	printf("\n\n\n\n\t\t\t\t\t\t\t\t--------MADE WITH C PROGRAMMING\n\n\n");
	reset;
	FILE *fp;
  	int i, tokens, len = 0, c;
  	char ch, name[100], line[100], command[10], t1[2], t2[2], t3[2], t4[2];
  	while (1)
    	{
		bold;
		magenta;
      		printf("\n\t\t\t\t\t  --------------MAIN MENU---------------\n\n");
		reset;
		bold;	
      		printf ("\n\t\t\t\t\t\t\t1)OPEN A FILE \n");
      		printf ("\n\t\t\t\t\t\t\t2)CREATE A FILE \n");
		printf("\n\t\t\t\t\t\t\t3)EXIT \n");
      		printf ("\n\t\t\t\t\t\t\tENTER THE CHOICE : ");
      		scanf ("%d", &c);
      		switch (c)
		{
			case 1:
	  		{
	    			printf ("\n\t\t\t\t\t\t Enter Existing File Name :\t");
	    			scanf ("%s", name);
				reset;
	    			break;
	  		}
			case 2:
	  		{
	    			printf ("\n\t\t\t\t\t\tEnter The New File Name :\t");
	    			scanf ("%s", name);
	    			int l, m;
	    			adddata (name);
				reset;
	    			break;

			}
			case 3:
			{
				green;
				printf("\n\t\t\t\t\t\t    Thanks For Using The Editor \n ");
				reset;
				exit(0);
			}
			default:
	  		{
	   
	   			 printf ("\n\t\t\t\t\t\t\tInvalid Choice ");
	   			 break;
	  		}
		}
		if(c==1 || c==2)
		break;


    	}
	underline;
	blue;
	bold;
	printf("\n\n\t\t\t\t\t\tTHE CONTENTS OF THE FILE ARE\n\n");
	reset;
  	strcpy (fname, name);
  	fp = fopen (fname, "r");
	if(!fp)
	{
		red;
		printf("\n\t\t\t\t\t\t   The File Does Not Exist!!\n\n");
		reset;
		exit(0);
	}
  	head = NULL;
  	while (fgets (line, 80, fp))
    	{
      		newnode = (NODE *) malloc (sizeof (NODE));
      		strcpy (newnode->data, line);	
      	//puts(line);
      		newnode->next = NULL;
      		newnode->prev = NULL;
      		if (head == NULL)
		head = t = newnode;
      		else
		{
	  		t->next = newnode;
	  		newnode->prev = t;
	  		t = t->next;
		}
    	}
  	for (t = head, i = 1; t != NULL; t = t->next, i++)
    	printf ("%d : %s\n", i, t->data);
	int r = 0;
  	while (1)
    	{
      		r++;
      		if (r != 1)
		{
			bold;
			printf ("\n\nMyprompt>");
			reset;
		}	
      		fflush (stdin);
      		gets (command);
      		tokens = sscanf (command, "%s%s%s%s", t1, t2, t3, t4);
      		if (tokens == 1 || tokens == 2 || tokens == 3 || tokens == 4)
		{
	  		fflush (stdin);
			bold;
			green;
	  		printf ("\nNo Of Arguments = %d\n\n", tokens);
			reset;
		}
      		switch (tokens)
		{
			case -1:
	  			break;

			case 1:		//printf("In case 1");
	  			if (strcmp (t1, "p") == 0)
	    			{
	      				len = 0;
	      				for (t = head; t != NULL; t = t->next)
					len++;
		      			display (1, len);
	    			}
	  			else if (strcmp ("a", t1) == 0)
	    				append ();
	  			else if (strcmp ("q", t1) == 0)
	    			{
	      				if (changed == 1)
					{
		  				printf ("Do u want to save the file first?(y/n)");
		  				ch = getchar ();
		  				if (ch == 'y' || ch == 'Y')
						{
			    					save ();
								exit(0);
						}
		 				else
						{
							printf("\n\t\t\t\t\t\tThanks For Using The Editor\n");
		    					exit (0);
						}
					}
					else
					{
							printf("\n\t\t\t\t\t\tThanks For Using The Editor\n");
                                                        exit (0);
					}

				}
	
				else if (strcmp ("h", t1) == 0)
	    			{
					underline;
					bold;
					printf("\n* Print\n\t1) use p to print entire file\n\t2) use p --line number to print a particular line\n\t3) use p --form line --to line to print multiple lines\n* Append\n\tuse a to Append\n* Save\n\tuse s to save\n* SaveAs\n\tuse sa to saveas\n* Update\n\t1) use u --line number to update specific line\n\t2) use u --line number --number of lines to update number of lines\n* Insert\n\t1) use i --line number to insert at specific line\n\t2) use i --no of lines --line number\n* Delete\n\t1) use d --line number to delete a specific line\n\t2)use d --line number --upto line to delete multiple lines\n* Copy\n\t1) use c --souce --destination to copy single line\n\t2)use c --from source --to source --destination to copy number of lines\n* Move\n\t1) use m --souce --destination to move single line\n\t2)use m --from source --to source --destination to move number of lines\n* Help\n\tuse h for help\n");
					reset;
	    			}
				else if (strcmp ("s", t1) == 0)
	    				save ();
	  			else if (strcmp ("sa", t1) == 0)
	    				saveas ();
	  			else
	    				printf ("Invalid Command\n");

	  			break;
			case 2:
	  			if (strcmp ("p", t1) == 0)
	    			{
	      				display (atoi (t2), atoi (t2));
	    			}
	  			else if (strcmp ("d", t1) == 0)
	    			{
					//printf("dd");
	      				delete (atoi (t2), atoi (t2));
	    			}
	  			else if (strcmp ("i", t1) == 0)
	    				insert (atoi (t2), atoi (t2));
	  			else if (strcmp (t1, "u") == 0)
	    				update (atoi (t2), atoi (t2));
	  			else
	  	  			printf ("Invalid Command\n");
	 			 break;
			case 3:
	  			if (strcmp ("p", t1) == 0)
	    			{
	      				if (atoi (t2) > atoi (t3))
					{
		  				display (atoi (t3), atoi (t2));
					}
	      				else
					display (atoi (t2), atoi (t3));
	    			}
	  			else if (strcmp ("d", t1) == 0)
	    			{
					//printf("%d %d",atoi(t2),atoi(t3));
	      				delete (atoi (t2), atoi (t3));
	    			}
	  			else if (strcmp ("i", t1) == 0)
	    				insert (atoi (t2), atoi (t3));
	  			else if (strcmp ("m", t1) == 0)
	    				move (atoi (t2), atoi (t3), -1);
	  			else if (strcmp ("u", t1) == 0)
	    				update (atoi (t2), atoi (t3));
	  			else if (strcmp ("c", t1) == 0)
	    				copy (atoi (t2), atoi (t3), -1);
	  			else
	    				printf ("Invalid command\n");

				break;
			case 4:
	  			if (strcmp ("m", t1) == 0)
	    				move (atoi (t2), atoi (t3), atoi (t4));
	  			else if(strcmp ("c", t1) == 0)
	    				copy (atoi (t2), atoi (t3), atoi (t4));
				else
					printf("Invalid Command\n");
	   			break;
		       default:
	  			printf("\nINVALID COMMAND!!");
				break;
	}
    }

}
