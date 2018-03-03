#pragma once
#include <atomic>
#include <vector>
#include <string>
#include "afxwin.h"
#include "NiawgStructures.h"
#include "coordinate.h"
#include "directions.h"

struct complexMove
{
	complexMove( ) {}
	complexMove( dir direction )
	{
		moveDir = direction;
		locationsToMove.clear( );
	}
	bool isInlineParallel = false;
	dir moveDir;
	std::vector<coordinate> locationsToMove;
	bool needsFlash;
	int dirInt( )
	{
		if ( moveDir == dir::right || moveDir == dir::left )
		{
			return (moveDir == dir::right) ? 1 : -1;
		}
		else
		{
			return (moveDir == dir::up) ? 1 : -1;
		}
	}
};;


// should be a one-dimensional move, only change in row or column. Could probably improve the struct to reflect that.
struct simpleMove
{
	bool operator == ( const simpleMove & other ) const
	{
		// two moves are equal if all members are equal.
		return( initRow == other.initRow &&
				initCol == other.initCol &&
				finRow  == other.finRow  &&
				finCol  == other.finCol);
	}
	ULONG initRow;
	ULONG initCol;
	ULONG finRow;
	ULONG finCol;
	dir dir( )
	{
		if ( finCol != initCol )
		{
			return (finCol > initCol) ? dir::right : dir::left;
		}
		else
		{
			return (finRow > initRow) ? dir::up : dir::down;
		}
	}
	int dirInt( )
	{
		if ( finCol != initCol )
		{
			return (finCol > initCol) ? 1 : -1;
		}
		else
		{
			return (finRow > initRow) ? 1 : -1;
		}
	}
	
	int movingIndex()
	{
		if ( dir( ) == dir::up || dir( ) == dir::down )
		{
			return initRow;
		}
		else
		{
			return initCol;
		}
	}
	int staticIndex( )
	{
		if ( dir( ) == dir::up || dir( ) == dir::down )
		{
			return initCol;
		}
		else
		{
			return initRow;
		}
	}
};