#include "functions.h"

int main ( int argc, char **argv )
{
		if ( strcmp ( argv[1], "-c" ) == 0 )
				task01 ( argv );

		else if ( strcmp ( argv[1], "-d" ) == 0 )
				task02 ( argv );

		else if ( strcmp ( argv[1], "-m" ) == 0 )
				task03 ( argv );

		else if ( strcmp ( argv[1], "-o" ) == 0 )
				bonus ( argv );

		return 0;
}