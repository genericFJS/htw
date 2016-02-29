#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char*	title;	
} medium;

typedef struct LITEM{
	struct LITEM* next;
	struct LITEM* prev;
	medium *item;
}lItem;

typedef struct{
	lItem* first;
	lItem* curr;
	unsigned int size;
}theLib;

theLib myLib = {NULL, NULL, 0};
medium *myMedia = NULL, *myMediat;
int myMediaCount = 0;

medium* createItem(char* ntitle){
	if ( myMedia == NULL ){
		myMedia = malloc (sizeof(medium));
	} else{
		myMediat = realloc (myMedia, (myMediaCount+1)*sizeof(medium));
		if (myMediat){
			myMedia = myMediat;
		} 
	}
	medium nMedia = {};
	nMedia.title = malloc (strlen(ntitle)+1);
	strcpy(nMedia.title, ntitle);
	
	*(myMedia+myMediaCount) = nMedia;
	medium *retMedia = myMedia+myMediaCount;
	
	myMediaCount++;	
	return retMedia;
}

void insertItem(medium *nMedium){
	printf("----Einfügen\n");
	if (myLib.size != 0){
		printf("\e[34mfirst: %s\e[0m\n", myLib.first->item->title);
// 		printf("\e[34mcurr: %s\e[0m\n", myLib.curr->item->title);
	}
// 	myLib.curr = myLib.first;
// 	if (myLib.size != 0){
// 		printf("\e[31mcurr: %s \e[0m\n", myLib.curr->item->title);
// 		printf("\e[31mfirs: %s \e[0m\n", myLib.first->item->title);
// 	}
	lItem *new = malloc (sizeof(lItem));
	new->item = nMedium;
	if ( myLib.size == 0 ){
		printf("1. Einfügen\n");
		new->next = new->prev = new;
		myLib.first = new;
		myLib.curr = new;
	} else{
		printf("\e[31mcurr: %s\e[0m\n", myLib.curr->item->title);
		printf("\e[31mnext: %s\e[0m\n", myLib.curr->next->item->title);
		int i;
		printf("====%s < %s: %d\n", myLib.curr->item->title, nMedium->title, (strcmp(myLib.curr->item->title, nMedium->title) < 0));
		for (i = 0; i < myLib.size ; i++){
			if (myLib.size == 1){
				printf("2. einfügen\n");
				myLib.curr->next = new;
				myLib.curr->prev = new;
				new->next = new->prev = myLib.curr;
				if ( strcmp(myLib.curr->item->title, nMedium->title) > 0 )
					myLib.first = new;
			}else {
				if ( strcmp(myLib.curr->item->title, nMedium->title) < 0 || i == myLib.size-1 ){
					printf("%s kleiner %s -> weiter!\n",myLib.curr->item->title, nMedium->title);
					myLib.curr = myLib.curr->next;
				} else {
					printf("%s größer %s, also vorher einfügen!\n",myLib.curr->item->title, nMedium->title);
// 					myLib.curr = myLib.curr->prev;
					printf("Einfügen vor: %s\n", myLib.curr->item->title);
					new->prev = myLib.curr->prev;
					new->next = myLib.curr;
					myLib.curr->prev->next = new;
					myLib.curr->prev = new;
					if (myLib.curr = myLib.first)
						myLib.first = new;
					break;
				}
			}
		}
	}
	printf("erfolgreich eingefügt.\n");
	myLib.size++;
	printItems();
}

void printItems(){	
	int i, size = 0;
	
// 	for (i = 0; i < myMediaCount; i++)
// 	printf("%s\n", (myMedia+i)->title);
	
	myLib.curr = myLib.first;
	size = myLib.size;
	for (i = 0; i < size; i++){
		printf("\e[32m %10s   prev: %s next: %s \e[0m\n", myLib.curr->item->title, myLib.curr->prev->item->title, myLib.curr->next->item->title);
		myLib.curr = myLib.curr->next;
	}
}

main(){
	printf("\n\e[34m=========================\e[0m\n");
	insertItem( createItem("ITEM5") );
	insertItem( createItem("ITEM4") );
	insertItem( createItem("ITEM3") );
	insertItem( createItem("ITEM7") );
	insertItem( createItem("ITEM1") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM5") );
// 	insertItem( createItem("ITEM6") );
// 	insertItem( createItem("ITEM4") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM7") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM8") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM9") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM6") );
// 	insertItem( createItem("ITEM4") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM2") );
// 	insertItem( createItem("ITEM1") );
// 	insertItem( createItem("ITEM0") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM3") );
// 	insertItem( createItem("ITEM99") );
	printItems();
	
	printf("\n\e[34m=========================\e[0m\n");
}