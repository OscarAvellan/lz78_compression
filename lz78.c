/*
*		Created by Oscar Avellan, 18/10/2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "treeops.h"

#define DEBUG 0
#define MAX_CHARS 1000
#define RANDOM_FACTOR 0
#define INITIAL_FACTOR 0

//------------------------------------------------------------------------------

typedef struct{
	char *word;
	int factor;
}data_t;

//------------------------------------------------------------------------------

int compare_strings(void *new,void *root);
void print_word_factor(void *x);
void free_word(void *x);

//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	char c,str[MAX_CHARS];
	int factr = INITIAL_FACTOR, input_bytes = 0;
	data_t *new_value,*locn;
	tree_t *tree;

	str[0] = '\0'; /*Sets str to the zero-length empty string*/

	tree = make_empty_tree(compare_strings);

	new_value = malloc(sizeof(*new_value));   /*Allocates spaces for new_value*/
	assert(new_value != NULL);
	new_value->word = malloc(1+strlen(str));  /*Allocates space to copy str*/
	assert(new_value->word != NULL);
	strcpy(new_value->word,str);
	new_value->factor = factr;

	tree = insert_in_order(tree,new_value);	/*Create an empty tree*/

	factr++;

	while ((c = getchar())!= EOF)
	{
		 input_bytes++;
		 strncat(str,&c,1);	/*Concatenates each character of the file to str*/

		 new_value = malloc(sizeof(*new_value)); /*Allocates space for the
		 														new_value*/
		 assert(new_value!=NULL);
		 new_value->word = str;					/*new_value->word is pointing
		 															to str*/
		 new_value->factor = factr;

		 locn = search_tree(tree,new_value); /*Searchs for the string in the tree*/

		 if (!locn)  	/*The string is not in the tree*/
		 {
		 	 new_value->word = malloc(1+strlen(str)); /*Allocates space for
		 	 													the string*/
		 	 assert(new_value->word!=NULL);
		 	 strcpy(new_value->word,str);

		 	 new_value->factor = factr++;
		 	 tree = insert_in_order(tree,new_value); /*Inserts the string
		 	 												into the tree*/

		 	 if (strlen(str) == 1)
		 	 {
		 	 	 /*If the string is of size 1, prints the character
		 	 	 and the factor 0*/
		 	 	 printf("%s0\n",str);
		 	 }
		 	 else
		 	 {
		 	 	/*Allocates space for a new value*/
		 	 	new_value = malloc(sizeof(*new_value));
		 	 	new_value->word = malloc(1+strlen(str));
		 	 	assert(new_value!=NULL && new_value->word!=NULL);

		 	 	/*Copies the string to new_value->word, but removes the last character*/
		 	 	strncpy(new_value->word,str,strlen(str)-1);

		 	 	/*Gives 0 to the new value since it doesn't matter*/
		 	 	new_value->factor = RANDOM_FACTOR;

		 	 	/*Searches for the longest prefix of the string in the tree*/
		 	 	locn = search_tree(tree,new_value);

		 	 	/*prints the last character of the string and
		 	 	the factor of the longest prefix*/
		 	 	printf("%c%d\n",str[strlen(str)-1],locn->factor);

		 	 	free(new_value->word);
		 	 	free(new_value);

		 	 }

		 	 /*Sets str to the zero-length empty string*/
		 	 str[0] = '\0';
		 }
		 else
		 {
		 	/*The string is in the tree,
		 	release the space that was allocated for the new value*/
		 	free(new_value);
		 }

	}

	/*Checks if the last character of the file was printed or not*/

	if (str[0] == '\n')
	{
		/*If the last character of the file is the '\n', it prints it with
		the factor 0*/
		printf("\n0\n");
	}
	else if (str[0] != '\0')
	{
		/*checks if the last character is different than the zero-length
		empty string and if it is, checks for the character in the tree
		and prints the char and its factor*/

		new_value = malloc(sizeof(*new_value));
		assert(new_value);
		new_value->word = str;
		new_value->factor = RANDOM_FACTOR;
		locn = search_tree(tree,new_value);

		printf("\n%d\n",locn->factor);

		free(new_value);
	}

	fprintf(stderr,"encode:		%d bytes input\n",input_bytes);
	fprintf(stderr,"encode:		%d factors generated\n",factr);

	#if DEBUG_TREE
	printf("----------------------------------------\n");
	traverse_tree(tree,print_word_factor);
	#endif

	/*Releases the space allocated for each string*/
	traverse_tree(tree,free_word);

	free_tree(tree);
	tree = NULL;

    return 0;
}

/*Compares the values in different nodes*/
int compare_strings(void *new,void *root)
{
	data_t *p1 = new, *p2 = root;
	return strcmp(p1->word,p2->word);
}

/*Only for debugging*/
void print_word_factor(void *x)
{
	data_t *p = x;
	printf("%d	%s\n",p->factor,p->word);
}

/*release the data struct store in the node*/
void free_word(void *x)
{
	data_t *p=x;

	free(p->word);
	free(p);
}

				 /*ALGORITHMS ARE FUN!!!!!!!!!!!!!!!*/
