#include "functions.h"

void modify_horizontal ( Node *root )
{
		Node *top_left, *top_right, *bottom_right, *bottom_left;

		top_left = root -> top_left;
		top_right = root -> top_right;
		bottom_right = root -> bottom_right;
		bottom_left = root -> bottom_left;

		root -> top_left = top_right;
		root -> top_right = top_left;
		root -> bottom_right = bottom_left;
		root -> bottom_left = bottom_right;

		if ( top_left != NULL )
		{
				modify_horizontal ( root -> top_left );
				modify_horizontal ( root -> top_right );
				modify_horizontal ( root -> bottom_right );
				modify_horizontal ( root -> bottom_left );
		}
}

void modify_vertical ( Node *root )
{
		Node *top_left, *top_right, *bottom_right, *bottom_left;

		top_left = root -> top_left;
		top_right = root -> top_right;
		bottom_right = root -> bottom_right;
		bottom_left = root -> bottom_left;

		root -> top_left = bottom_left;
		root -> top_right = bottom_right;
		root -> bottom_right = top_right;
		root -> bottom_left = top_left;

		if ( top_left != NULL )
		{
				modify_vertical ( root -> top_left );
				modify_vertical ( root -> top_right );
				modify_vertical ( root -> bottom_right );
				modify_vertical ( root -> bottom_left );
		}
}

void free_quadtree ( Node *root )
{
		if ( root != NULL )
		{
				free_quadtree ( root -> top_left );
				free_quadtree ( root -> top_right );
				free_quadtree ( root -> bottom_right );
				free_quadtree ( root -> bottom_left );
				free ( root );
		}
}