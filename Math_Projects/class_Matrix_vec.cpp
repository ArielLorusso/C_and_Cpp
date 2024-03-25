/*  USE NUTRITION DATABASE  (100g unit) hipotetical example       food vs macronutrient
//               | beef | fish  | egg   | Oat   | rice  |karror | letuce |tomato|banana | Total diary need
//               |      |       |       |       |       |       |        |      |       |
//      calories |      |       |       |       |       |       |        |      |       | 3000 kCal
//      wather   |      |       |       |       |       |       |        |      |       | > 2000g    
//      Protein  |  83  |  75   |  60   |  10   |   0   |   0   |   0    |  0   |   0   | 300g
//      Carbs    |   0  |   5   |   0   |  65   |  90   |  60   |  20    |      |  75   | 450g 500g
//      lipids   |  12  |  12   |  26   |   2   |   0   |   0   |   0    |  0   |   3   | 250g
//      mineral  |   3  |   4   |   7   |   8   |   2   |       |   3    |      |   5   | 20g
//      vitamin  |   2  |   4   |   7   |   5   |   1   |       |   2    |      |   3   | 10g */

using namespace std;
#include <vector> 
#include <iostream>
#include <iomanip>      // std::setprecision
#include <cstdlib>      // vector.malloc

class matrix
{
    public:
        ~matrix();                                          //  destructor
        matrix () ;                                         //  constructor empty
        matrix (uint i , uint j) ;                          //  constrctor  dimensions        -> size i,j , uninitialized values
        matrix (uint i , uint j , float homo) ;             //  constrctor  uniform matrix    -> size i,j , all same values
        matrix (vector<float> vec , uint i , uint j);       //  constructor from vector          SAFE
        matrix (vector<vector<float> > mat, uint i , uint j) ;//  constructor from nested vector
        matrix ( const matrix & M ) ;                       //  constructor copia

    //  INPUT / OUTPUT methods 
    void    homo        (const float f ) ;       //  fills matrix same values
    void    resize      (uint i , uint j);
    void    cin_fill    () ;                    //  asks value  for each element
    void    cin_fill2   () ;                    //  asks values for rows
    void    identity    () ;                    //  puts 1 id i == j else 0
    void    print       () ;                    //                done  ( no test made)
    float   element     (uint i , uint j) ;
    vector<vector<float>> content     () ;

    //   OPERATIONS      
    void  operator=   (const  matrix m );     // (not const)  Calling object copyes evry element to avoid multiple data destruction (pointers)
                                                // Mehods ahead do not change its object but return an object result therfore  -> const
    matrix  operator+   ( const matrix m ) const;    // Ads only if same dimension
    matrix  operator+   ( const float f  ) const;    // Ads float to every element 
    matrix  add_trunc   ( const matrix m ) const;    // Returns input size truncated matrixof sum
    matrix  add_cons    ( const float f  ) const;    // calls     operator+ ( float f  )               

    matrix  operator*   ( const matrix m ) const;      
    matrix  operator*   ( const float  f ) const;     
    bool    operator==  ( const matrix m ) const;

    //   SELF OPERATIONS   
    matrix  tran  (  )                  const;                     
    float   det   (  )                  const;
    float   det_unop()                 const;
    float   det_simple()                 const;
    matrix  cof   ( uint i , uint j )   const;       
    matrix  adj   (  )                  const;                          
    matrix  inv   (  )                  const;
    matrix  row   ( uint i )            const;
    matrix  col   ( uint j )            const;

    private:
//  float eigenvalue  
//  float eigenvector
//  char * name;
    
    uint iMax = 0 ;             // Max value for index of Rows   [ 0 , 1 , 2 , ... , i-1 ]
    uint jMax = 0 ;             //  Cols   [ 0 , 1 , 2 , ... , j-1 ]
    vector < vector <float> > value ;   //  matrix obj ; obj.value [i] [j] = element i,j of matrix

};

//////////////////////////////////////// CONSTRUCTORS /////////////////////////////////////////////////////
matrix::~matrix()
{ 
    std::cout << "Destructing" << std::endl;
    for(uint i=0 ; i < this->iMax ; ++i)
    {
        this->value[i].~vector();  // free each row 
        // for j 0 to jMax : delete value[i][j] ;
    }
    // delete this->value;
}  

matrix::matrix () 
{ 
    this->value.resize(0);
} 

matrix::matrix ( const matrix & M ) 
{
    this->resize( M.iMax, M.jMax);
    
    for(uint i = 0 ; i < M.iMax ; ++i)                  // copy elements value
    {
        for(uint j = 0 ; j < M.jMax ; ++j)
        {
            this->value [i] [j] = M.value[i][j] ;
            //this->value [i].emplace = M.value[i][j] ;           
        }
    }
    std::cout << "copyed  " << M.iMax << " x "<< M.jMax << "  matrix \n";
} 

matrix::matrix ( uint iM , uint jM)
{
    this->resize(iM,jM);
}

matrix::matrix ( uint iM , uint jM, float homo)
{
    this->resize(iM,jM);
    this->homo(homo); // sapiens
}

matrix::matrix (vector<float> vec,  uint iM , uint jM)
{
    this->iMax = iM;
    this->jMax = jM;

    if( vec.size() < (iM*jM)  )
    {
        uint rows = vec.size()/jM;
        std::cout << "array too small for matrix , constructor fail " << std::endl;
        std::cout << "will give less rows instead ("<< rows <<"x"<< jM <<")" << std::endl;
        this->value.resize(rows);     // populated as an array of ( pointers ) , 
        this->iMax = rows;

        for (uint i = 0; i < rows; i++ )    
        {
            this->value[i].resize(jM);              // ( pointers ) populateds as aray 
        }
    
        for(uint i = 0 ; i < rows ; i++)
        {
            for(uint j = 0 ; j < jM ; j++)
            {
            this->value [i][j] =  vec [ (i*jM) + j ] ;
            }
        }  
    }

    else
    { 
        this->value.resize( iM );  

        for (uint i = 0; i < iM; i++ )    
        {
            this->value[i].resize(jM);              // ( pointers ) populateds as aray 
        }
    
        for(uint i = 0 ; i < iM ; i++)
        {
            for(uint j = 0 ; j < jM ; j++)
            {
            this->value [i][j] =  vec [ (i*jM) + j ] ;
            }
        }
    }
}

matrix::matrix ( vector< vector<float>> mat, uint iM , uint jM)
{
    this->iMax = iM;
    this->jMax = jM;
    this->value =  mat;

}

//////////////////////////////////////// I/O METHOD /////////////////////////////////////////////////////
void   matrix::homo     (const  float f)
{
    for(uint i = 0 ; i < this->iMax ; i++)
    {
        for(uint j = 0 ; j < this->jMax ; j++)
        {
            this->value [i][j] = f;
        }
    }
}

void    matrix::resize (uint iM, uint jM )
{
    this->iMax = iM;
    this->jMax = jM;
    
    if (iM == 0) 
    {   
        return;
    }    
    
    //this-> value.reserve (iM);           // ask for iM vectors(vectors) ...(colums) ,  
    this-> value.resize (iM);
    for (uint i = 0; i < iM; ++i )    
    {
        this-> value[i].resize (jM);
//        this->value [i].reserve(jM);             // give every vector size  (Uninicializated values)    
    }         
}

void    matrix::cin_fill( ) 
{
    for(uint i = 0 ; i < this->iMax ; i++)
    {
        for(uint j = 0 ; j < this->jMax ; j++)
        {
            std::cout << "choose value for element [" <<  i  <<","<< j << "] \n";
            std::cin  >> ( this->value [i][j] ) ;
        }
    }
}

void    matrix::cin_fill2( ) 
{
    for(uint i = 0 ; i < this->iMax ; i++)
    {
        std::cout << "choose "<< this->jMax << " values for row [" <<  i  << "]\n";
        for(uint j = 0 ; j < this->jMax ; j++)
        {
            std::cin  >> ( this->value [i][j] ) ;
        }
    }
}

void    matrix::identity( )
{
    for(uint i = 0 ; i < this->iMax ; i++)
    {
        for(uint j = 0 ; j < this->jMax ; j++)
        {
            if( i == j ) 
            {
                this->value [i][j] = 1.0 ;
            }
            else { this->value [i][j] = 0.0; }
        }
    }
} 

void    matrix::print ()
{
    // std::cout << std::fixed << std::setprecision(5);     //  http://www.geeksforgeeks.org/stdfixed-stdscientific-stdhexfloat-stddefaultfloat-c/
    std::cout <<   std::scientific ;
    for(uint i=0 ;i < this->iMax ; i++)                 
    {
        for(uint j=0 ;j < this->jMax ; j++)             
        {           
           std::cout  << this->value [i][j] << " ";
        }
        std::cout  << "\n";
    }
    std::cout  << "\n" << std::defaultfloat  ;    
}

float   matrix::element(uint i , uint j)
{
    return this->value [i][j];
}

vector<vector<float>> matrix::content () 
{
    matrix copy (*this) ;     // matrix::matrix ( const matrix & M ) ->  output = matrix copy
    return copy.value;        // return copy not this.  We want different pointers  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////// OPERATION METHOD /////////////////////////////////////////////////////
void  matrix::operator=   (const matrix M )    // sets calling object values to argument ones 
{
    this->iMax = M.iMax;
    this->jMax = M.jMax;

    if( (this->iMax != M.iMax) || (this->jMax != M.jMax)) 
    {
        this->resize(M.iMax,M.jMax);
    }

    for(uint i=0 ;i < M.iMax ; i++)
    {
        for(uint j=0 ;j < M.jMax ; j++)
       {
            this->value [i][j] =  M.value[i][j];
        }
    }

    return;
}

matrix  matrix::operator+   (const matrix M )   const  // object size must match argument , neither are modified , returns extra object
{
    if( (this->iMax != M.iMax) || (this->jMax != M.jMax) )
    {
        std::cout << "\n \t Non same dimention matrix   addition Failed \n ";
        return *this;
    }
    matrix mcopy (*this);

    for(uint i=0 ;i < this->iMax ; i++)
    {
        for(uint j=0 ;j < this->jMax ; j++)
       {
            mcopy.value [i][j] +=  M.value[i][j];
        }
    }

    return mcopy;
}

matrix  matrix::operator+   (const float f )    const   // every element in object matrix increases by float arg 
{
    matrix mcopy (*this);

    for(uint i=0 ;i < this->iMax ; i++)
    {
        for(uint j=0 ;j < this->jMax ; j++)
        {
            mcopy.value [i][j] +=  f ;
        }    
    }

    return mcopy;
}

matrix  matrix::add_trunc   (const matrix M )   const    // output matrix has calling object size regardless argument (its truncated)
{
    uint  iMax = this->iMax  ,  jMax = this->jMax ;

    if( M.iMax < iMax)  //   up to where we make sum ?
    {
         iMax = M.iMax ;
    }
    if( M.jMax < jMax)
    {
         jMax = M.jMax ;
    }
    
    matrix mcopy (*this); //  copy  calling obj  and sum

    for( uint i=0 ;i < iMax ; i++)
    {
        for( uint j=0 ;j < jMax ; j++)
        {
            mcopy.value [i][j] += M.value[i][j];
        }
    }
    return mcopy ;
}

matrix  matrix::add_cons    (const float f )    const
{
    return *this + f ;
}      


matrix  matrix::operator*   ( const matrix m ) const    //  matrix multiplication 
/*    EXAMPLE                      this * m = out
    2x3    3x2            2x2
  1 1 1  *  1 2   =   1+3+5   2+4+6    =   9   12    
  1 2 3     3 4       1+6+15  2+8+18       22  28
  this      5 6 m        out                       */
{
    uint iMax_out = this->iMax  , jMax_out = m.jMax; 
    

    matrix out (iMax_out,jMax_out);

    if (  this->jMax !=  m.iMax  )
    {
        std::cout << "\n \t Non matching inter dimention matrix   addition Failed  ";
        std::cout << "\n \t Expected matrix dimention to be :  (n x M)  *  (M x l)  ";
        std::cout << "\n \t Current  matrix dimention are   :  (" 
        << this->iMax << " x " << this->jMax << ")  *  (" << m.iMax << " x "<< m.jMax << ")   \n ";
        out.resize(0,0);
        return out;
    }

    float sum ;
    for ( uint i_o = 0 ; i_o < iMax_out ; ++i_o)   //////////  OUTPUT MAT
    {
        for ( uint j_o = 0; j_o < jMax_out ; ++j_o)
        {
            sum = 0.0f ;
            for ( uint i = 0; i < m.iMax ; ++i)
            {
                sum += this->value[i_o][i] * m.value[i][j_o]   ;      
            }
            out.value [i_o] [j_o] = sum;
        }
    }
    
    return out;

}      

matrix  matrix::operator*   ( float f ) const
{
    matrix mcopy (*this);

    for(uint i=0 ;i < this->iMax ; ++i)
    {
        for(uint j=0 ;j < this->jMax ; ++j)
        {
            mcopy.value [i][j] *=  f ;
        }    
    }
    return mcopy;
}

bool    matrix::operator==  ( const matrix m ) const
{
    if( ( this->iMax != m.iMax ) || (this->jMax != m.jMax) )
    {
        return false;
    }
    
    for(uint i=0 ;i < this->iMax ; ++i)
    {
        for(uint j=0 ;j < this->jMax ; ++j)
        {
            if( this->value [i][j] !=  m.value[i][j] )
            {return false;}
        }    
    }
    return true;
}


//////////////////////////////////////// SELF OPERATION METHOD /////////////////////////////////////////////////////
matrix  matrix::tran () const
{
    matrix out (this->jMax ,this->iMax);
   
    for(uint i = 0 ; i < this->iMax ; i++)
    {
        for(uint j = 0 ; j < this->jMax ; j++)
        {
            out.value [j][i] = this->value [i][j] ;
        }
    }
    return out ;
}

matrix  matrix::cof (uint no_i, uint no_j)  const//  arguments are position [i],[j]  from 0  to skip
{
 /* matrix copy(*this);                         // quick  to whrite but slower to do.. not by much
    copy.value.erase(no_i);                     // (i+j) / (i*j) times slower
    for(uint i = 0 ; i < this->iMax ; i++)      // easier to debug ?
    {copy.value[i].errase(no_j) ;  
    return copy;       */

    uint out_i, out_j ;
    out_i = (this->iMax) - 1 ;
    out_j = (this->jMax) - 1 ;

    if (out_i < 1) 
    {
        std::cout << "out dimension i is 0  cofactor fail \n";
        return *this;
    }

    if (out_j < 1)
    {
        std::cout << "out dimension j is 0  cofactor fail \n";
        return *this;
    }

    matrix out( out_i , out_j );      // smaller out matrix  waste no time
    
    for(uint i = 0 ; i < out_i  ; ++i)
    {
        for(uint j = 0 ; j < out_i ; ++j)
        {   
            if ( (i >= no_i)  &&  (j >= no_j) )     
            {   out.value [i][j] = this->value [i+1] [j+1] ; }   // skip both
            else if      (i >= no_i )               
            {   out.value [i][j] = this->value [i+1] [j]   ; }   // skip row
            else if      (j >= no_j )              
             {   out.value [i][j] = this->value [i]   [j+1] ; }   // skip colom
            else                                    
            {   out.value [i][j] = this->value [i][j]      ; }    // don't slip
        }
    }  
    return out ;
}

/*  float   matrix::det () const 
{   
    if ( this->iMax != this->jMax )
    {
        std::cout << "\n \t Non square matrix  Failed determinant\n ";
        return 0.0f ;
    }

    if (this->iMax == 1) 
        {return this->value[0][0];} 

    float result ;

    uint row_max_ceros = 0 ,      col_max_ceros = 0;        // variable to store row,col max number of ceros bigger one will be used 
    uint row_ceros [this->iMax] , col_ceros [this->iMax];   // make ceros search vector   for  Row & col
    
    for(uint i = 0 ; i < this->iMax ; ++i)           
    {        
        row_ceros[i] = 0;   col_ceros[i] = 0;}              // start count in 0
    
    
    for( uint i = 0 ; i < this->iMax ; ++i)               // search for number of ceros   in  Row || col
    {
        for(uint j = 0 ; j < this->iMax ; ++j)
        {   
            if (  this->value [i] [j] == 0 )               // found 0 in (row,col) 
            {
                row_ceros[i] ++;                                // increment counter for that row & col
                col_ceros[j] ++; }}}
    
    for( uint i = 0 ; i < this->iMax ; ++i)               // store max number for ceros  in  Row 
    {
        if (row_max_ceros < row_ceros[i])
        {   
            row_max_ceros = row_ceros[i]; }               // keep biggest row 0 value
    
        if (col_max_ceros < col_ceros[i])
        {   
            col_max_ceros = col_ceros[i]; }                 // keep biggest col 0 value
    }
    
 // Compare biggest amount 0  Row vs col
    if ( row_max_ceros >= col_max_ceros)            // -> ROWS 0 WIN
    {
        for( uint i = 0 ; i < this->iMax ; ++i)         // search for that max ceros Row ( using index i ) 
        {
            if (row_max_ceros == row_ceros[i])              //  optimal row position i found
            {   
                float add = 0.0f ;
                for( uint j = 0 ; j < this->jMax ; ++j)           // for each row call recursively Det  of smaller matrix
                { 
                    if ( this->value[i][j] )                                 // is value != 0
                    {
                        add = (this->value [i][j] )  *  ( ( this->cof(i,j) ).det() ) ;    // element  Magnitude
                    }

                    if( (i+j) % 2 ) 
                    { add *= -1.0f ; }                                   //  element Sign
                    result += add; 
                    add = 0.0f;                                     //  element addition
                }
                return result;                                          //  return
            }   
        }
    }
    else                                              // -> COLS 0 WIN
    {
        for( uint j = 0 ; j < this->jMax ; j++)          // search for that max cerosCol 
        {   
            float add;
            for( uint i = 0 ; i < this->iMax ; i++)          // for each row call recursively Det  of smaller matrix
            {
                if ( this->value[i][j] )                                 // is value != 0
                {
                    add = (this->value [i][j] )  *  ( ( this->cof(i,j) ).det() ) ;    // element  Magnitude
                }
                if( (i+j) % 2 ) 
                { add *= -1.0f ; }                                   //  element Sign
                result += add;                                       //  element addition
                add = 0.0f;     
            }
            return result;   
        }    
    }
}
*/

float matrix::det() const
{
    int fila [this->iMax];
    int col [this->iMax];
    for(int i=0; i < this->iMax; ++i)
    {
        fila[i] = 0;
        col[i] = 0;      
    }
    for(int i = 0; i < this->iMax; ++i)
    {
        for(int j = 0; j < this->iMax; ++j)
        {
            if(!this->value[i][j])
            {
                fila[i]+=1;
                col[j]+=1;
            }
        }
    }
    bool filCol = false;
    uint poss = 0;
    char mayor = 0;
    for(int i=0; i < this->iMax; ++i)
    {
        if(fila[i] > mayor)
        {
            mayor = fila[i];
            poss = i;
            filCol = false;
        }
        if(col[i] > mayor)
        {
            mayor = col[i];
            poss = i;
            filCol = true;
        }
    }

    int det = 0;
    
    if(this->iMax > 2)
    {
        matrix aux;
        for(uint i=0; i< this->iMax; ++i)
        {
            if(!filCol)
            {
                aux = this->cof(poss,i);
            }
            else
            {
                aux = this->cof(i,poss);
            }
            if(!((i+poss)%2))
            {
                det += aux.det();
            }
            else
            {
                det -= aux.det();
            }
                  
        }
    }
    else
    {
        det = (this->value[0][0]*this->value[1][1])-(this->value[1][0]*this->value[0][1]);
    }
    return det;
}

float   matrix::det_unop() const// stupid version no optimisation may be usfull for shor  matrix
{
    if (this->iMax == 1) 
    {
        return this->value[0][0];
    } 
    float result = 0;
    float add = 0.0f;
    uint i = 0 ;

    for( uint j = 0 ; j < this->jMax ; ++j)           // for each row call recursively Det  of smaller matrix
    { 
        add = (this->value[i][j] ) * ( this->cof(i,j) ).det_unop()  ;                 // element  Magnitude
        if( (i+j) % 2 ) 
            { add *= -1.0f ; }                                   //  element Sign
        result += add;                                      //  element addition
        add = 0.0f;  
    }
    return result;                                          //  return       
}

float   matrix::det_simple() const// stupid version no optimisation may be usfull for shor  matrix
{
    if (this->iMax == 1) 
        {return this->value[0][0];} 
    
    float result = 0.0f;
    float mult , add;
    uint  dim = this->jMax ;


    add  = 0.0f;                                // set up to sum positive directions
    for( uint j = 0 ; j < dim  ; ++j)           
    {     
        mult = 1.0f;                                // set up to acumulate a direction 
        for( uint i = 0 ; i < dim ; ++i)           
        { 
            mult *=  this->value [i] [(j+i) % dim ]   ;     // acumulate 
        }                
        add += mult ;                                // positive sum 
    }                                   
    result += add;                               //  store positive sum
    
    
    add  = 0.0f;                                // set up to sum nrgative directions
    for( uint j = 0 ; j < dim  ; ++j)           
    {     
        mult = 1.0f;                                // set up to acumulate a direction 
        for( uint i = 0 ; i < dim ; ++i)           
        { 
            uint a = (dim-1-i-j) % dim ;
            mult *=  this->value [i] [(2*dim-1-i-j) % dim ]   ;     // acumulate 
        }                
        add -= mult ;                                // negative sum 
    }                                   
    result += add;   
    
    return result;                                          //  return       
}

matrix  matrix::adj () const
{
    matrix out (*this); //copy 
    for(uint i; i < out.iMax ; i++)
    {
        for(uint j; j < out.jMax ; j++)
        {
            out.value[i][j] = ( this->cof(i,j) ).det() ;  //   m =  det( cof(this,i,j) )
            if( (i+j) %2 ) 
            { out.value[i][j] *= -1.0 ; }
        }
    }
    return out;

}

using namespace std;

void vecinic(vector<float> (*vec), float array[], uint size )
{
    (*vec).resize(size);
    for ( uint i = 0 ; i < size ; i++)
    {
        (*vec) [i] = array[i];
    }
}

///////////////////////////////////////// MAIN //////////////////////////////////////////////////////

int main()
{
  vector <float> vec; /*   
    float array1[15] = { 1,2,1,1,0,0};
    vecinic(& vec,array1,15);
    matrix A (vec,2,3);

    cout << "Matrix A:\n" ;
    A.print();
    */
   
    float array2[15] = { 1,2,3,
                         4,5,6,
                         7,8,9,10,11,12,13,1,15};
    vecinic(& vec,array2,15);
    matrix B ( vec,3,3);

  /*  cout << "vec size: "  << vec.size() <<"\n"<< endl;
    cout << "Matrix B:\n" ;   B.print();


    matrix C (A);   cout << "Matrix C:\n" ;  C.print();
    C=A*B;          cout << "Matrix C:\n" ;  C.print();
*/
    cout << "Det:\n" ;
    cout << B.det();
    cout << "\n" ;
    //cout << B.det_simple();
    //cout << "\n" ;
/*
    C.homo(1.0);
    C.print();
    C = A * B; 
    C.print();*/
    return 0 ;  
}
