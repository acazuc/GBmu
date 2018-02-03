
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main( int ac, char **av )
{
	if ( ac < 2 )
	{
		puts( "Eat shit yoh" );
		return EXIT_FAILURE;
	}

	FILE *rom;
	char head[0x19];
	uint8_t check = 0;

	if ( !( rom = fopen( av[1], "rb+" ) ) )
	{
		puts( "Bad file name bro" );
		return EXIT_FAILURE;
	}

	if ( fseek( rom, 0x134, SEEK_SET ) == -1 )
		return EXIT_FAILURE;

	if ( fread( head, 1, 0x19, rom ) != 0x19 )
	{
		puts( "File too short, that's not a header lul :3" );
		return EXIT_FAILURE;
	}

	for ( int i = 0 ; i < 0x19 ; i++ )
		check = check - head[i] - 1;

	if ( fseek( rom, 0x14d, SEEK_SET ) == -1 )
		return EXIT_FAILURE;

	if ( fwrite( &check, 1, 1, rom ) < 1 )
	{
		puts( "Can't write, your file suck" );
		return EXIT_FAILURE;
	}

	puts( "Success yoh :3" );
	return EXIT_SUCCESS;
}
