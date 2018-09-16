#include "functions.h"

int nr_noduri ( Node *root )
{
		if ( root == NULL )
				return 0;

		else
		{
				int TL, TR, BR, BL;

				TL = nr_noduri ( root -> top_left );
				TR = nr_noduri ( root -> top_right );
				BR = nr_noduri ( root -> bottom_right );
				BL = nr_noduri ( root -> bottom_left );

				return 1 + TL + TR + BR + BL;
		}
}

int nr_frunze ( Node *root )
{
		if ( root -> top_left ==  NULL )
			return 1;

		else
		{
				int TL, TR, BR, BL;

				TL = nr_frunze ( root -> top_left );
				TR = nr_frunze ( root -> top_right );
				BR = nr_frunze ( root -> bottom_right );
				BL = nr_frunze ( root -> bottom_left );

				return TL + TR + BR + BL;
		}
}