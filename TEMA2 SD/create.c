#include "functions.h"

Node *add_node ()
{
		Node *nou = (Node*)malloc(sizeof(Node));
		nou -> top_left = NULL;
		nou -> top_right = NULL;
		nou -> bottom_right = NULL;
		nou -> bottom_left = NULL;

		return nou;
}

Node *build_tree ( Node *root, RGB **pixels, int L, int C, int latura, long long factor )
{
		int i, j;
		long long mean = 0, area = latura * latura, red = 0, green = 0, blue = 0;
		Node *nou = add_node ();

		for ( i = L; i < L + latura; ++i )
				for ( j = C; j < C + latura; ++j )
				{
						red += 1LL * pixels[i][j].red;
						green += 1LL * pixels[i][j].green;
						blue += 1LL * pixels[i][j].blue;
				}

		red /= area;
		green /= area;
		blue /= area;

		for ( i = L; i < L + latura; ++i )
				for ( j = C; j < C + latura; ++j )
				{
						mean += 1LL * ( red - pixels[i][j].red ) * ( red - pixels[i][j].red );
						mean += 1LL * ( green - pixels[i][j].green ) * ( green - pixels[i][j].green );
						mean += 1LL * ( blue - pixels[i][j].blue ) * ( blue - pixels[i][j].blue );
				}

		mean /= ( 3LL * area );

		nou -> info.red = red;
		nou -> info.green = green;
		nou -> info.blue = blue;
		nou -> area = area;

		if ( mean > factor && area > 1 )
		{
				int jumatate = latura / 2;

				nou -> top_left = build_tree ( nou -> top_left, pixels, L, C, jumatate, factor );
				nou -> top_right = build_tree ( nou -> top_right, pixels, L, C + jumatate, jumatate, factor );
				nou -> bottom_right = build_tree ( nou -> bottom_right, pixels, L + jumatate, C + jumatate, jumatate, factor );
				nou -> bottom_left = build_tree ( nou -> bottom_left, pixels, L + jumatate, C, jumatate, factor );
		}

		return nou;
}

Node *build_tree2 ( Node *root, QuadTreeNode *vector, int poz )
{
		Node *nou = add_node ();

		nou -> info.red = vector[poz].red;
		nou -> info.green = vector[poz].green;
		nou -> info.blue = vector[poz].blue;
		nou -> area = vector[poz].area;

		if ( vector[poz].top_left != -1 )
		{
				nou -> top_left = build_tree2 ( nou -> top_left, vector, vector[poz].top_left );
				nou -> top_right = build_tree2 ( nou -> top_right, vector, vector[poz].top_right );
				nou -> bottom_right = build_tree2 ( nou -> bottom_right, vector, vector[poz].bottom_right );
				nou -> bottom_left = build_tree2 ( nou -> bottom_left, vector, vector[poz].bottom_left );
		}

		return nou;
}