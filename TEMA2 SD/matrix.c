#include "functions.h"

void build_matrix ( RGB **pixels, QuadTreeNode *vector, int poz, int L, int C, int latura )
{
		if ( vector[poz].top_left != -1 )
		{
				int jumatate = latura / 2;

				build_matrix ( pixels, vector, vector[poz].top_left, L, C, jumatate );
				build_matrix ( pixels, vector, vector[poz].top_right, L, C + jumatate, jumatate );
				build_matrix ( pixels, vector, vector[poz].bottom_right, L + jumatate, C + jumatate, jumatate );
				build_matrix ( pixels, vector, vector[poz].bottom_left, L + jumatate, C, jumatate );
		}

		else
		{
				int i, j;

				for ( i = L; i < L + latura; ++i )
						for ( j = C; j < C + latura; ++j )
						{
								pixels[i][j].red = vector[poz].red;
								pixels[i][j].green = vector[poz].green;
								pixels[i][j].blue = vector[poz].blue;
						}
		}
}