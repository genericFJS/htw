#include <stdlib.h>
#include <stdio.h>

typedef struct nODE {
	struct nODE *left;
	struct nODE *right;
	int data;
} node;

node * new_list(){
	node *new = malloc(sizeof(node));
	new->data  = -1;
	new->right = new;
	new->left  = new;
	return new;
}

node * insert_right(node *list, int data){
	node *new = malloc(sizeof(node));
	new->data        = data;
	new->left        = list;
	new->right       = list->right;
	list->right      = new;
	new->right->left = new;
	return new;
}

node * delete(node *list){
	list->right->left = list->left;
	list->left->right = list->right;
	return list->left;
}

node * restore(node *list){
	list->right->left = list;
	list->left->right = list;
	return list;
}

void print_all(node* list){
	node *head = list;
	node *current = list;
	printf("%d ", head->data);
	while (head != (current = current->right)){
		printf("%d ", current->data);
	}
	printf("\n");
}

int main(int argc, char** argv){
	/* erstelle eine neue Liste: */
	node *head    = new_list();
	node *current = head;
	int i;

	/* Befuelle die List mit den Zahlen 1 bis 10 */
	for(i = 1; i <= 10; i++){
		current = insert_right(current, i);
	}

	/* Gebe die Liste  aus, einmal von head aus startent, einmal vom 
	   letzten Element aus: */
	print_all(head);
	print_all(current);

	/* loesche das vorletzte Element: */
	current = current->left;
	current = delete(current); 
	printf("Liste nach loeschen:\n");
	print_all(head);

	current = delete(head);
	printf("Liste nach loeschen des Kopfes:\n");
	print_all(current);

	head = restore(head);
	printf("Liste nach Wiederherstellen des Kopfes:\n");
	print_all(head);

	return 0;
}