// g++ -o trainningData makeTrainningData.cpp -lstdc++

#include <iostream>
#include <fstream>

#include <vector>
#include <cstdlib>

#include <cmath>


int main ()
{
	const uint NumExamples = 2000;
    std::cout << "number of examples:" << NumExamples << std::endl;

    std::ofstream myoutfile;
    myoutfile.open("trainingData.txt");
    myoutfile << "3 topology: 2 4 1 "<< std::endl;
    
    uint inputDim = 2;

	std::vector <float> in;		//	INIC VECTOR
	in.resize(inputDim);

    
	for(uint ex = NumExamples ; ex >  0 ; --ex)		//	every exaple
    {
		for (uint i=0; i< inputDim ;++i)
		{
			in[i] = (int) ( 2.0*rand()/double(RAND_MAX));   // give random input 0 or 1
			myoutfile << "in: " << in[i] << ".0 ";			// print input
		}
		myoutfile << std::endl;

		int t = 0;
		for (uint i=0; i< inputDim ;++i)					// calculate output
		{
			t = t ^ (int)in[i]; 							// should be 0 or 1
		}
		
		myoutfile << "out: " << t << ".0 " << std::endl; 	// print output
    }
    myoutfile.close();
    return 0;
}




/* OTHER CALC METHODS....

IDEA 1) :

	a^b^c

IDEA 2) :
	a = b = 0...1
	d = (a-.5)*(b-.5)
	if d < 0 
		d = - 1
	else
		d = 1

Idea 3)

	float dist = 0; // unidim dist
	float sum = 0;
	for (uint i; i< inputDim ;++i)
	{			
		dist = ( in[i] - 0.1f) ;
		dist *= dist ;				// square distance to (0.1 , 0.1)
		if (dist < 0) { dist = - dist; }
		sum += dist;				// sum square dist
	}
*/