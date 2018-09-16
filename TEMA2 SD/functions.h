#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef struct QuadTreeNode
{
		unsigned char blue, green, red;

		uint32_t area;

		int32_t top_left, top_right;
		int32_t bottom_left, bottom_right;

}__attribute__((packed))QuadTreeNode;

typedef struct RGB
{
		unsigned char red, green, blue;

}RGB;

typedef struct Node
{
		RGB info;

		long long area;

		struct Node *top_left, *top_right;
		struct Node *bottom_left, *bottom_right;

}Node;

void task01 ( char ** );
void task02 ( char ** );
void task03 ( char ** );
void bonus ( char ** );
Node *add_node ();
Node *build_tree ( Node *, RGB **, int, int, int, long long );
Node *build_tree2 ( Node *, QuadTreeNode *, int );
void build_matrix ( RGB **, QuadTreeNode *, int, int, int, int );
void update_matrix ( RGB **, QuadTreeNode *, int, int, int, int );
void bfs ( Node *, QuadTreeNode *, int );
void h ( char ** );
void v ( char ** );
void modify_horizontal ( Node * );
void modify_vertical ( Node * );
void free_quadtree ( Node * );
int nr_noduri ( Node * );
int nr_frunze ( Node * );
