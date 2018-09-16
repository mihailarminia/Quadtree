#include "functions.h"

void task01 ( char **argv )
{
		FILE *f = fopen ( argv[3], "rb" );
		FILE *g = fopen ( argv[4], "wb" );
		
		char useless_buffer[3];
		int i, j, width, height, useless_number, latura;
		long long factor;
		uint32_t noduri, frunze;
		unsigned char red, green, blue;
		RGB **pixels;
		Node *root;
		QuadTreeNode *vector;

		pixels = NULL;
		root = NULL;
		vector = NULL;

		fscanf ( f, "%s\n", useless_buffer );
		fscanf ( f, "%d\n", &width );
		fscanf ( f, "%d\n", &height );
		fscanf ( f, "%d\n", &useless_number );

		latura = width;
		factor = atoi ( argv[2] );

		pixels = (RGB**)malloc(( latura + 1 ) * sizeof(RGB*));
		for ( i = 0; i <= latura; ++i )
				pixels[i] = (RGB*)malloc(( latura + 1 ) * sizeof(RGB));

		for ( i = 0; i < height; ++i )
				for ( j = 0; j < width; ++j )
				{
						fread ( &red, sizeof(unsigned char), 1, f );
						pixels[i + 1][j + 1].red = red;
						fread ( &green, sizeof(unsigned char), 1, f );
						pixels[i + 1][j + 1].green = green;
						fread ( &blue, sizeof(unsigned char), 1, f );
						pixels[i + 1][j + 1].blue = blue;
				}
		

		root = build_tree ( root, pixels, 1, 1, latura, factor );

		noduri = nr_noduri ( root );
		frunze = nr_frunze ( root );

		vector = (QuadTreeNode*)malloc(noduri * sizeof(QuadTreeNode));

		bfs ( root, vector, noduri );

		fwrite ( &frunze, sizeof(uint32_t), 1, g );
		fwrite ( &noduri, sizeof(uint32_t), 1, g );
		fwrite ( vector, sizeof(QuadTreeNode), noduri, g );

		///// Eliberare memorie /////

		for ( i = 0; i <= height; ++i )
				free ( pixels[i] );
		free ( pixels );
		free ( vector );
		free_quadtree ( root );

		fclose ( f );
		fclose ( g );
}