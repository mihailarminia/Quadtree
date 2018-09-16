#include "functions.h"

void task02 ( char **argv )
{
		FILE *f = fopen ( argv[2], "rb" );
		FILE *g = fopen ( argv[3], "wb" );

		uint32_t frunze, noduri;
		int i, j, latura;
		unsigned char useless_number = 255;
		QuadTreeNode *vector;
		RGB **pixels;
		Node *root;

		vector = NULL;
		pixels = NULL;
		root = NULL;

		fread ( &frunze, sizeof(uint32_t), 1, f );
		fread ( &noduri, sizeof(uint32_t), 1, f );

		vector = (QuadTreeNode*)malloc(noduri * sizeof(QuadTreeNode));

		fread ( vector, sizeof(QuadTreeNode), noduri, f );

		///// Creez arborele cuaternar /////

		root = build_tree2 ( root, vector, 0 );

		latura = sqrt ( vector[0].area );

		pixels = (RGB**)malloc(( latura + 1 ) * sizeof(RGB*));
		for ( i = 0; i <= latura; ++i )
				pixels[i] = (RGB*)malloc(( latura + 1 ) * sizeof(RGB));

		build_matrix ( pixels, vector, 0, 1, 1, latura );

		fprintf ( g, "P6\n" );
		fprintf ( g, "%d %d\n", latura, latura );
		fprintf ( g, "%d\n", useless_number );

		for ( i = 1; i <= latura; ++i )
				for ( j = 1; j <= latura; ++j )
				{
						fwrite ( &pixels[i][j].red, sizeof(unsigned char), 1, g );
						fwrite ( &pixels[i][j].green, sizeof(unsigned char), 1, g );
						fwrite ( &pixels[i][j].blue, sizeof(unsigned char), 1, g );
				}
		
		///// Eliberare memorie /////

		for ( i = 0; i <= latura; ++i )
				free ( pixels[i] );
		free ( pixels );
		free( vector );
		free_quadtree ( root );

		fclose ( f );
		fclose ( g );
}