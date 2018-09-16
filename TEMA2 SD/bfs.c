#include "functions.h"

void bfs ( Node *root, QuadTreeNode *vector, int noduri )
{
		Node **queue;
		queue = NULL;
		queue = (Node**)malloc(noduri * sizeof(Node*));
		int st = 0, dr = 0;

		queue[0] = root;

		while ( st <= dr )
		{
				vector[st].red = queue[st] -> info.red;
				vector[st].green = queue[st] -> info.green;
				vector[st].blue = queue[st] -> info.blue;
				vector[st].area = queue[st] -> area;

				if ( queue[st] -> top_left == NULL )
				{
						vector[st].top_left = -1;
						vector[st].top_right = -1;
						vector[st].bottom_right = -1;
						vector[st].bottom_left = -1;
				}

				else
				{
						queue[++dr] = queue[st] -> top_left;
						vector[st].top_left = dr;
						queue[++dr] = queue[st] -> top_right;
						vector[st].top_right = dr;
						queue[++dr] = queue[st] -> bottom_right;
						vector[st].bottom_right = dr;
						queue[++dr] = queue[st] -> bottom_left;
						vector[st].bottom_left = dr;
				}

				++st;
		}

		free ( queue );
}