#include "functions.h"

void h ( char **argv )
{
		FILE *f = fopen ( argv[4], "rb" );
		FILE *g = fopen ( argv[5], "wb" );
		
		char useless_buffer[3];
		int i, j, width, height, useless_number, latura, factor;
		uint32_t noduri;
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
		factor = atoi ( argv[3] );

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

		modify_horizontal ( root );

		noduri = nr_noduri ( root );

		vector = (QuadTreeNode*)malloc(noduri * sizeof(QuadTreeNode));

		bfs ( root, vector, noduri );

		latura = sqrt ( vector[0].area );

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

		for ( i = 0; i <= height; ++i )
				free ( pixels[i] );
		free ( pixels );
		free ( vector );
		free_quadtree ( root );

		fclose ( f );
		fclose ( g );
}

void v ( char **argv )
{
		FILE *f = fopen ( argv[4], "rb" );
		FILE *g = fopen ( argv[5], "wb" );
		
		char useless_buffer[3];
		int i, j, width, height, useless_number, latura, factor;
		uint32_t noduri;
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
		factor = atoi ( argv[3] );

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

		modify_vertical ( root );

		noduri = nr_noduri ( root );

		vector = (QuadTreeNode*)malloc(noduri * sizeof(QuadTreeNode));

		bfs ( root, vector, noduri );

		latura = sqrt ( vector[0].area );

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

		for ( i = 0; i <= height; ++i )
				free ( pixels[i] );
		free ( pixels );
		free ( vector );
		free_quadtree ( root );

		fclose ( f );
		fclose ( g );
}