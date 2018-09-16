#include "functions.h"

void bonus ( char **argv )
{
		FILE *f1 = fopen ( argv[3], "rb" );
		FILE *f2 = fopen ( argv[4], "rb" );
		FILE *g = fopen ( argv[5], "wb" );
		
		char useless_buffer[3];
		int i, j, width, height, useless_number, latura, factor;
		uint32_t noduri, noduri2;
		unsigned char red, green, blue;
		RGB **pixels, **pixels2;
		Node *root, *root2;
		QuadTreeNode *vector, *vector2;

		pixels = NULL;
		pixels2 = NULL;
		root = NULL;
		root2 = NULL;
		vector = NULL;
		vector2 = NULL;

		factor = atoi( argv[2] );

		fscanf ( f1, "%s\n", useless_buffer );
		fscanf ( f1, "%d\n", &width );
		fscanf ( f1, "%d\n", &height );
		fscanf ( f1, "%d\n", &useless_number );

		latura = width;

		pixels = (RGB**)malloc(( latura + 1 ) * sizeof(RGB*));
		for ( i = 0; i <= latura; ++i )
				pixels[i] = (RGB*)malloc(( latura + 1 ) * sizeof(RGB));

		for ( i = 0; i < height; ++i )
				for ( j = 0; j < width; ++j )
				{
						fread ( &red, sizeof(unsigned char), 1, f1 );
						pixels[i + 1][j + 1].red = red;
						fread ( &green, sizeof(unsigned char), 1, f1 );
						pixels[i + 1][j + 1].green = green;
						fread ( &blue, sizeof(unsigned char), 1, f1 );
						pixels[i + 1][j + 1].blue = blue;
				}

		root = build_tree ( root, pixels, 1, 1, latura, factor );

		noduri = nr_noduri ( root );

		vector = (QuadTreeNode*)malloc(noduri * sizeof(QuadTreeNode));

		bfs ( root, vector, noduri );

		build_matrix ( pixels, vector, 0, 1, 1, latura );

		///// Fisier 2 /////

		fscanf ( f2, "%s\n", useless_buffer );
		fscanf ( f2, "%d\n", &width );
		fscanf ( f2, "%d\n", &height );
		fscanf ( f2, "%d\n", &useless_number );

		pixels2 = (RGB**)malloc(( latura + 1 ) * sizeof(RGB*));
		for ( i = 0; i <= latura; ++i )
				pixels2[i] = (RGB*)malloc(( latura + 1 ) * sizeof(RGB));

		for ( i = 0; i < height; ++i )
				for ( j = 0; j < width; ++j )
				{
						fread ( &red, sizeof(unsigned char), 1, f2 );
						pixels2[i + 1][j + 1].red = red;
						fread ( &green, sizeof(unsigned char), 1, f2 );
						pixels2[i + 1][j + 1].green = green;
						fread ( &blue, sizeof(unsigned char), 1, f2 );
						pixels2[i + 1][j + 1].blue = blue;
				}

		root2 = build_tree ( root2, pixels2, 1, 1, latura, factor );

		noduri2 = nr_noduri ( root2 );

		vector2 = (QuadTreeNode*)malloc(noduri2 * sizeof(QuadTreeNode));

		bfs ( root2, vector2, noduri2 );

		build_matrix ( pixels2, vector2, 0, 1, 1, latura );

		for ( i = 1; i <= height; ++i )
				for ( j = 1; j <= width; ++j )
				{
						int A, B, media;
						A = pixels[i][j].red; B = pixels2[i][j].red;
						media = ( A + B ) / 2;
						pixels2[i][j].red = media;

						A = pixels[i][j].green; B = pixels2[i][j].green;
						media = ( A + B ) / 2;
						pixels2[i][j].green = media;

						A = pixels[i][j].blue; B = pixels2[i][j].blue;
						media = ( A + B ) / 2;
						pixels2[i][j].blue = media;
				}

		fprintf ( g, "P6\n" );
		fprintf ( g, "%d %d\n", latura, latura );
		fprintf ( g, "%d\n", useless_number );

		for ( i = 1; i <= latura; ++i )
				for ( j = 1; j <= latura; ++j )
				{
						fwrite ( &pixels2[i][j].red, sizeof(unsigned char), 1, g );
						fwrite ( &pixels2[i][j].green, sizeof(unsigned char), 1, g );
						fwrite ( &pixels2[i][j].blue, sizeof(unsigned char), 1, g );
				}

		///// Eliberare memorie /////

		for ( i = 0; i <= latura; ++i )
				free ( pixels[i] );
		for ( i = 0; i <= latura; ++i )
				free ( pixels2[i] );
		free ( pixels );
		free ( pixels2 );
		free ( vector );
		free ( vector2 );
		free_quadtree ( root );
		free_quadtree ( root2 );

		fclose ( f1 );
		fclose ( f2 );
		fclose ( g );
}