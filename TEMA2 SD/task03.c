#include "functions.h"

void task03 ( char ** argv )
{
		if ( strcmp ( argv[2], "h" ) == 0 )
				h ( argv );

		else if ( strcmp ( argv[2], "v" ) == 0 )
				v ( argv );
}