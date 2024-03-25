#include  <iostream>
#include  <vector>
#include  <cstdlib>
#include  <ctime>

bool  chance ( float probability)
{
	if ( probability > rand()/ (float) RAND_MAX )
	{
		return	true;
	}
	return  false ;
}



int  binomial_simulation  (int cuantity )
{
	uint n = 0;
	for(uint i=0 ; i< cuantity ; ++i)
	{
		if ( chance( 0.5f ) )
		{
			n++;
		}
	}

	return n;
}

//-------------------------------------------------------------------------------------------------------------

uint   dice  ( uint  maxValue )		// give radom dice value
{
	return  (uint)  (  (float) maxValue  * rand()/ RAND_MAX   ) ;
}

uint  trow_n_dices  ( uint  n , uint maxVal)	// sum n dices of 1 thow
{
	uint val = 0 ;
	for( uint i=0  ;  i< n  ; ++i)
	{
		val += dice( maxVal );
	}
		
	return val;
}

void set_to_0( std::vector<uint> vec)
{
	for(uint i=0; i< vec.size() ;++i)
	{
		vec[i]=0;
	}
}


std::vector <uint>  dice_trows (uint throws ,uint n ,uint dice_max)	// make trow histogram
{
	std::vector <uint> throw_res ;
	throw_res.resize(0);
	for (uint i=0; i < throws ; ++i)
	{
		throw_res.push_back( trow_n_dices(n, dice_max) ) ;
	}
		
	
	std::vector <uint> histo ;
	histo.resize( dice_max* n) ;
	set_to_0(histo);

	for (uint i=0; i < throw_res.size() ; ++i) 
	{
		histo[ throw_res[i]] += 1;
	}		
	return histo ;
}

void printhisto(std::vector<uint> histo)
{
	for (uint i=0; i < histo.size() ; ++i) 
	{
		std::cout << histo[i] << " ";
	} 
}

int main()
{
	srand(time(NULL) );
	std::vector <uint> histo  = dice_trows(500,2,6);
	printhisto(histo);
	//histo.resize(0);
	//histo.~vector();
	return 1;
}
