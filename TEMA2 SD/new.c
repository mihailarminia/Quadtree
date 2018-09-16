#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct QuadtreeNode {

	unsigned char blue, green, red;
	uint32_t area;
	int32_t top_left, top_right;
	int32_t bottom_left, bottom_right;
} __attribute__ ( ( packed ) ) QuadtreeNode ;


typedef struct node {

	unsigned char blue, green, red;
	uint32_t area;
	struct node *top_left, *top_right;
	struct node *bottom_left, *bottom_right;
} node;


typedef struct pixel {

	unsigned char red, green, blue;
} pixel;

typedef struct queue {
	node *info;
	struct queue *next;
}queue;

void create_vector(node*, QuadtreeNode*);
void free_tree(node *);

int nods ( node *root )
{
		if ( root == NULL )
				return 0;

		else
				return 1 + nods ( root -> top_left ) + nods ( root -> top_left ) + nods ( root -> bottom_right ) + nods ( root -> bottom_left );
}

int leafs ( node *root )
{
		if ( root -> top_left ==  NULL )
			return 1;

		else
				return leafs ( root -> top_left )+ leafs ( root -> top_right ) + leafs( root -> bottom_right ) +  leafs( root -> bottom_left );
}

node *new_node(pixel p) {

	node *new = malloc(sizeof(node));
	new->red = p.red;
	new->blue = p.blue;
	new->green = p.green;
	new->top_right = NULL;
	new->top_left = NULL;
	new->bottom_right = NULL;
	new->bottom_left = NULL;

	return new;
}

queue *push(queue *head, node *p) {
	if(head == NULL) {
		head = (queue*)malloc(sizeof(queue));
		head->info=p;
		head->next=NULL;
	}
	else {
		queue *aux=head, *nou;
		while (aux -> next != NULL)
			aux = aux->next;

		nou=(queue*)malloc(sizeof(queue));
		nou->info=p;
		nou->next =NULL;
		aux->next=nou;
	}

	return head;
}


pixel medie(pixel **a, int lungime, int latime,int x, int y) {

	pixel p;
	int i,j;
	long long med_red = 0, med_green = 0, med_blue = 0;
	for(i=x; i<x+lungime; i++)
		for(j=y; j<y+latime; j++) {
			med_red = a[i][j].red + med_red;
			med_green = a[i][j].green + med_green;
			med_blue = a[i][j].blue + med_blue;
		}
	med_red = med_red / (lungime * latime);
	med_green = med_green / (lungime * latime);
	med_blue = med_blue / (lungime * latime);

	p.red = med_red;
	p.green = med_green;
	p.blue = med_blue;

	return p;
}


long long scor(pixel **a, pixel p, int lungime, int latime, int x, int y) {

	int i,j;
	long long r=0,g=0,b=0;
	for(i=x; i<x+lungime; i++)
		for(j=y; j<y+latime; j++) {
			r=r+(p.red - a[i][j].red)*(p.red - a[i][j].red);
			g=g+(p.green - a[i][j].green)*(p.green - a[i][j].green);
			b=b+(p.blue - a[i][j].blue)*(p.blue - a[i][j].blue);
		}
	return  (r+g+b) / (3*lungime*latime);
}


node* arbore(pixel **a, int lungime, int latime, int prag, int x, int y, int *n, int *f) { 
	node *arbore_nod = NULL;
	pixel p = medie(a, lungime, latime, x, y);
	long long s = scor(a, p, lungime, latime, x, y);
	if(s <= prag) {
		arbore_nod = new_node(p);
		arbore_nod->area=lungime*latime;
	}
	else if(s > prag && lungime > 1) {
		arbore_nod = new_node(p);
		arbore_nod->area=lungime*latime;
		arbore_nod->top_left = arbore(a,lungime/2,latime/2,prag,x,y,n,f);
		arbore_nod->top_right = arbore(a,lungime/2,latime/2,prag,x,y+latime/2,n,f);
		arbore_nod->bottom_left = arbore(a,lungime/2,latime/2,prag,x+lungime/2,y,n,f);
		arbore_nod->bottom_right = arbore(a,lungime/2,latime/2,prag,x+lungime/2,y+latime/2,n,f);

	}
	else {
		arbore_nod = new_node(p);
		arbore_nod->area=lungime*latime;
	}
	return arbore_nod;
}

void compresie(const char *string_i, const char *string_o, int prag) {

	FILE *fpi,*fpo;
	pixel **a=NULL;
	char var[5];
	int i,x=0,y=0,f =0, n=0;
	uint32_t n1 = 0, f1 = 0;
	int lungime, latime, max;
	QuadtreeNode *v=NULL;
	fpi=fopen(string_i,"rb");
	fpo=fopen(string_o,"wb");
	fscanf(fpi, "%s\n", var);
	fscanf(fpi,"%d %d\n",&lungime, &latime);
	fscanf(fpi,"%d\n", &max);
	a = calloc (lungime,sizeof(pixel*));
	for(i=0; i<lungime; i++) {
		a[i] = calloc (latime, sizeof(pixel));
		fread(a[i], sizeof(pixel), latime, fpi);
	}
	node *root = arbore(a, lungime, latime,prag,x,y,&n,&f);
	n = nods(root);
	f = leafs(root);
	v=(QuadtreeNode*)malloc(n*sizeof(QuadtreeNode));
	create_vector(root, v);
	f1=f;
	n1=n;
	fwrite(&f1, sizeof(uint32_t),1,fpo);
	fwrite(&n1, sizeof(uint32_t),1,fpo);
	fwrite(v, sizeof(QuadtreeNode), n, fpo);

	free(v);
	for(i=0; i<lungime; i++) {
		free(a[i]);
	}
	free(a);
	free_tree(root);

	fclose(fpi);
	fclose(fpo);

}

void free_tree (node *root)
{
	if(root != NULL)
	{
		free_tree(root->top_right);
		free_tree(root->top_left);
		free_tree(root->bottom_right);
		free_tree(root->bottom_left);
		free(root);
	}
}

void create_vector(node *root, QuadtreeNode *vector)
{
	queue *head = NULL;
	head = push(head, root);

	int poz = 0, urm = 0;

	while (head != NULL)
	{
		node *curent = head -> info;
		vector[poz].red = curent ->red;
		vector[poz].green = curent->green;
		vector[poz].blue = curent->blue;
		vector[poz].area = curent->area;

		if ( curent -> top_left != NULL)
		{
			head=push(head, curent->top_left);
			head=push(head, curent->top_right);
			head=push(head, curent->bottom_right);
			head=push(head, curent->bottom_left);
			++urm;
			vector[poz].top_left = urm;
			++urm;
			vector[poz].top_right=urm;
			++urm;
			vector[poz].bottom_right=urm;
			++urm;
			vector[poz].bottom_left=urm;
		}
		else
		{
			vector[poz].top_left = -1;
			vector[poz].top_right=-1;
			vector[poz].bottom_right=-1;
			vector[poz].bottom_left=-1;
		}
		++poz;
		queue *aux = head;
		head = head->next;
		free(aux);
	}
}

int main(int argc, char **argv)
{
	if(strcmp(argv[1], "-c") == 0) {
		int prag = atoi(argv[2]);
		compresie(argv[3],argv[4],prag);

	}

	return 0;
}
