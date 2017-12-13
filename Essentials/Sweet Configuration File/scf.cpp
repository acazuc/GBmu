/*************************************
**                                  **
**     Sweet Configuration File     **
**	     ( 1st try )            **
**                                  **
**       Sweet Mare Software        **
**       05/09/17 - --/--/17        **
**                                  **
*************************************/

#include <scf.h>

scf::scf( void ) : table( sizeof ( struct entry * ) )
{
}

char scf::getnextchar( void )
{
	char c;

	c = src.get();
	if ( src.eof() )
		throw true;
	if ( src.fail() )
		throw false;
	return c;
}

void scf::createvar( void )
{
	const char *s = centry.c_str();
	struct entry *entry;

	if ( *s == '"' )
	{
		s++;
		if ( *s )
		{
			const char *s2 = s + 1;
			while ( *s2 )
				s2++;
			if ( *--s2 == '"' )
			{
				entry = new struct entry;
				(*entry).type = SCF_STRING;
				(*entry).data.str = new char [centry.length() - 1];
				memcpy( (*entry).data.str, s, centry.length() - 2 );
				(*entry).data.str[centry.length() - 1] = NUL;
				table.add( ckey.c_str(), &entry );
			}
		}
	}
	else if ( isdigit( *s ) || ( *s == '-' ) )
	{
		char *end;
		int nb = strtol( s, &end, 0 );

		if ( !*end )
		{
			entry = new struct entry;
			(*entry).type = SCF_INT;
			(*entry).data.nb = nb;
			table.add( ckey.c_str(), &entry );
		}
	}
	else if ( !strcmp( s, "true" ) )
	{
		entry = new struct entry;
		(*entry).type = SCF_BOOL;
		(*entry).data.bo = true;
		table.add( ckey.c_str(), &entry );
	}
	else if ( !strcmp( s, "false" ) )
	{
		entry = new struct entry;
		(*entry).type = SCF_BOOL;
		(*entry).data.bo = false;
		table.add( ckey.c_str(), &entry );
	}
	ckey.clear();
	centry.clear();
}

bool scf::load( const char *path )
{
	char c;
	char *s;

	try
	{
		src.open( path );
		c = getnextchar();
top:		while ( ( c == CR ) || ( c == LF ) )
			c = getnextchar();

		if ( c == '#' )
		{
			do
				c = getnextchar();
			while ( c != LF );
			goto top;
		}

		while ( c != '=' )
		{
			ckey.push_back( c );
			c = getnextchar();
		}

		c = getnextchar();
		while ( c != LF )
		{
			if ( c != CR )
				centry.push_back( c );
			try
			{
				c = getnextchar();
			}
			catch ( bool ret )
			{
				src.close();
				if ( ret )
				{
					createvar();
					return true;
				}
				else
					return false;
			}
		}
		createvar();
		c = getnextchar();
		goto top;
	}
	catch ( bool ret )
	{
		src.close();
		return ret;
	}
}

bool scf::save( const char *path )
{
	char *key;
	struct entry *entry;

	dst.open( path );
	if ( dst.bad() )
		return false;
	while ( key = table.allstar( &entry ) )
	{
		dst << key << '=';
		switch ( (*entry).type )
		{
			case SCF_INT:
				dst << (*entry).data.nb;
				break;
			case SCF_BOOL:
				dst << ( (*entry).data.bo ? "true" : "false" );
				break;
			case SCF_STRING:
				dst << '"' << (*entry).data.str << '"';
		}
		dst << LF;
	}
}

void *scf::get( const char *key )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) )
		return NULL;
	return ( void * ) &(*entry).data;
}

long &scf::getint( const char *key )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) || (*entry).type != SCF_INT )
		throw SCFERR;
	return (*entry).data.nb;
}

bool &scf::getbool( const char *key )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) || (*entry).type != SCF_BOOL )
		throw SCFERR;
	return (*entry).data.bo;
}

char *&scf::getstring( const char *key )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) || (*entry).type != SCF_STRING )
		throw SCFERR;
	return (*entry).data.str;
}

int scf::test( const char *key )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) )
		return SCF_NONE;
	return (*entry).type;
}

bool scf::test( const char *key, int type )
{
	struct entry *entry;

	if ( !table.get( key, &entry ) )
		return false;
	return (*entry).type == type ? true : false;
}

scf::~scf( void )
{
}
