// NeuralNet_Vimeo.cpp : 
//        Vimeo channel  https://vimeo.com/technotes
//  Vimeo video tutotial https://vimeo.com/channels/technotes/19569529

#include <vector>   //http://www.cplusplus.com/reference/vector/vector/    vector <type>     .back()   .push_back()
#include <iostream> //http://www.cplusplus.com/reference/iostream/         cout <<        cin >>  http://www.cplusplus.com/reference/istream/istream/operator>>/
#include <cstdlib>  //http://www.cplusplus.com/reference/cstdlib/          rand() srand() Rand_MAX  malloc() atoi()...
#include <cassert>  //http://www.cplusplus.com/reference/cassert/          acert()  errorcheck
#include <cmath>    //http://www.cplusplus.com/reference/cmath/            sqrt()  tang() ....
#include <fstream>  //http://www.cplusplus.com/reference/fstream/fstream/  if stream class  .open(file)    

// ██████████████████████████████████████████████████████████████████████████████████████████████████████████
// ███████████████████  class TrainingData  █████████████████████████████████████████████████████████████████

class TrainingData
{
 public:
    TrainingData(const char* filename );
    bool isEof(void) { return feof(trainingDataFile); }
    void getTopology(std::vector<unsigned>& topology);
    void setVectors( std::vector<double> & inputVals , std::vector<double> & targetVals );
    // Returns the number of input values read from the file:
    unsigned getNextInputs( std::vector<double>& inputVals);
    unsigned getTargetOutputs( std::vector<double>& targetOutputVals);

 private:
    FILE * trainingDataFile;  // imput_file_stream object
    char comand  [10];        // last read entry type ("topology","in" ,"out")
    int  layers = 0 ;        // layer count
    unsigned inputs  ;        // last input vector
    unsigned outputs ;        // last output vector
};

void TrainingData::getTopology(std::vector<unsigned>& topology)
{
    unsigned layerNeurons;
    fscanf(trainingDataFile,"%d",& this->layers );             //  read layer number
    fscanf(trainingDataFile,"%s", comand);                //  read "topology"
    
    
    for (uint16_t i=0;  i < layers ;i++)              //  for (layers) 
    { 
        topology.push_back(0);                        //  apend new empty value
        fscanf (trainingDataFile,"%d", & topology[i]) ;         //  fill  topology vector
        std::cout << "capa_"<< i  << " = "<< topology[i] << " , " ;  //  print it
    }       
    std::cout << std::endl;
    
     inputs  = topology[0];           // first layer = inputs
     outputs = topology[layers-1];   // last layer = outputs

    return;
}

void TrainingData::setVectors( std::vector<double> & inputVals , std::vector<double> & targetVals )
{
    inputVals.resize ( inputs );
    targetVals.resize( outputs );
}

TrainingData::TrainingData( const char* filename  )
{
    this->trainingDataFile = fopen( "/home/mompc/Documentos/VisualCode/Neural Net Vimeo/trainingData.txt" , "r");
    if (trainingDataFile != NULL)
    { 
        std::cout << "file opened :" << "\\" << filename << "\\" << std::endl;
        return;
    }
    std::cout << "error" ;
}


unsigned TrainingData::getNextInputs ( std::vector<double> & inputVals)
{
    fscanf(trainingDataFile,"%s", comand);                //  leer "in"
    if(comand[0] == 'i' && comand[1] == 'n')    //   in ?
    {
        for (size_t i=0; i < inputs ; i++ )               //  
        {   fscanf (trainingDataFile,"%lf", & inputVals[i] ) ;
            std::cout << "entrada_" << i << " = "<< inputVals[i] <<" , " ;
        }   
        fgetc(trainingDataFile);  // skip  '\n'
    }
    
    return inputVals.size();
}

unsigned TrainingData::getTargetOutputs( std::vector<double>& outputVals)
{
    double ineficient;
    fscanf(trainingDataFile,"%s", comand);                //  leer "out"
        if(comand[0] == 'o' && comand[1] == 'u' && comand[2] == 't')
        {
            for(uint16_t i=0; i < outputs ;i++)
            {   fscanf (trainingDataFile,"%lf", & ineficient ) ;
                outputVals.at(i) = ineficient;
                std::cout << "Output Target = " << outputVals.at(i) <<" , "  ;
            }   //  for(N) para valores de topologia
        }

    return outputVals.size();
}

struct Connection
{
    double weight;
    double deltaWeight;
};

class Neuron;
typedef std::vector<Neuron> Layer;
// ██████████████████████████████████████████████████████████████████████████████████████████████████████████
// ███████████████████  class Neuron  ███████████████████████████████████████████████████████████████████████
class Neuron
{
public:
    Neuron(unsigned numOutputs, unsigned myIndex);
    void setOutputVal(double val) { m_outputVal = val; }
    double getOutputVal(void) const { return m_outputVal; }
    void feedForward(const Layer& prevLayer);
    void calcOutputGradients(double targetVal);
    void calcHiddenGradients(const Layer& nextLayer);
    void updateInputWeights(Layer& prevLayer);
    void printWeights( void );
    void SetWeights  ( std::vector<double> weigt );

private:
    static double transferFunction(double x);
    static double transferFunctionDerivative(double x);
    static double randomWeight(void) { return rand() / double(RAND_MAX); }
    double sumDOW(const Layer& nextLayer) const;
    
    static double eta;      // [0.0..1.0] overall net training rate
    static double alpha;    // [0.0..n] multiplier of last weight change (momentum)
    double m_outputVal;
    std::vector<Connection> m_outputWeights;
    unsigned m_myIndex;
    double gradient ;
};

double Neuron::eta = 0.28;    // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5;   // momentum, multiplier of last deltaWeight, [0.0..1.0]

void Neuron::updateInputWeights(Layer& prevLayer)
{
    // The weights to be updated are in the Connection container
    // in the neurons in the preceding layer

    for (unsigned n = 0; n < prevLayer.size(); ++n) 
    {
        Neuron& neuron = prevLayer[n];
        double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

        double newDeltaWeight =   
            eta  * neuron.getOutputVal()   * gradient     // Individual input, magnified by the gradient and train rate:
            + alpha  * oldDeltaWeight;                     // Also add momentum = a fraction of the previous delta weight;

        neuron.m_outputWeights[ this-> m_myIndex ].deltaWeight = newDeltaWeight;
        neuron.m_outputWeights[ this-> m_myIndex ].weight     += newDeltaWeight;
    }
}

void Neuron::printWeights( void )  // 
{
    for (uint i =0; i < m_outputWeights.size() ;i++)
    { 
        std::cout << "W" << i << ": " ;  
        std::cout << this->m_outputWeights[i].weight << " ";
    }
}

void Neuron::SetWeights  ( std::vector<double> weigts ) // changes output weights to argument
{
    if ( weigts.size() == m_outputWeights.size())
    {
        for (uint i =0; i < m_outputWeights.size() ;i++)
        { 
        std::cout << "W" << i << ": " ;  
        this->m_outputWeights[i].weight = weigts[i];
        std::cout << this->m_outputWeights[i].weight << " ";
        }
    }
    else { std::cout << "Weight dimension does not match " ;}
}

double Neuron::sumDOW(const Layer& nextLayer) const
{
    double sum = 0.0;
  
    for (unsigned n = 0; n < nextLayer.size() - 1; ++n) {    // Sum our contributions of the errors at the nodes we feed.
        sum += m_outputWeights[n].weight * nextLayer[n].gradient ;
    }

    return sum;
}

void Neuron::calcHiddenGradients(const Layer& nextLayer)
{
    double dow = sumDOW(nextLayer);
}

void Neuron::calcOutputGradients(double targetVal)
{
    double delta = targetVal - m_outputVal;
    gradient  = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
    return tanh(x);         // tanh - output range [-1.0..1.0]
}

double Neuron::transferFunctionDerivative(double x)
{
    return 1.0 - x * x;     // tanh derivative
}

void Neuron::feedForward(const Layer& prevLayer)
{
    double sum = 0.0;

    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the previous layer.

    for (unsigned n = 0; n < prevLayer.size(); ++n) { // for each neuron in prev layer + bias
        sum += prevLayer[n].getOutputVal() *                // sum  outputs * Weights  of previous layer
            prevLayer[n].m_outputWeights[m_myIndex].weight;
    }

    m_outputVal = Neuron::transferFunction(sum);    // Output Sum
}

Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
    for (unsigned c = 0; c < numOutputs; ++c) {         // conection from 0 to NumOutputs
        m_outputWeights.push_back(Connection());        // Asign Weiht,DeltaWeight to each connection
        m_outputWeights.back().weight = randomWeight(); //set Last connection Weight to random 
       
    }

    m_myIndex = myIndex;
}

// ████████████████████████████████████████████████████████████████████████████████████████████████████████
// ███████████████████  class Net  ████████████████████████████████████████████████████████████████████████

class Net
{
public:
    Net(const std::vector<unsigned>& topology);
    void feedForward(const std::vector<double>& inputVals);
    void backProp(const std::vector<double>& targetVals);
    void getResults(std::vector<double>& resultVals) const;
    double getRecentAverageError(void) const { return m_recentAverageError; }
    void printWeights( void );
    void SetWeights  ( std::vector<double> weigt );

private:
    std::vector<Layer> m_layers; // m_layers[layerNum][neuronNum]
    double m_error;
    double m_recentAverageError;
    static double ErrorSmoothingFactor;
};

void Net::printWeights( void )
{
    for(uint i=0; i< this->m_layers.size() ; ++i)
    {
        std::cout  << "\n" << "Layer" << i;
        for(uint j=0; j < this->m_layers[i].size() ; ++j)
        {
            std::cout << "Neuron" << j << " ";
            this->m_layers[i][j].printWeights();
        }
    }
}

void Net::SetWeights  ( std::vector<double> weigt )
{}

double Net::ErrorSmoothingFactor = 100.0; // Number of training samples to average over

void Net::getResults( std::vector<double>& resultVals) const
{
    resultVals.clear();

    for (unsigned n = 0; n < m_layers.back().size() - 1; ++n) {
        resultVals.push_back(m_layers.back()[n].getOutputVal());
    }
}

void Net::backProp(const std::vector<double>& targetVals)
{
    // Calculate overall net error (RMS of output neuron errors)

    Layer& outputLayer = m_layers.back();
    m_error = 0.0;

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        double delta = targetVals[n] - outputLayer[n].getOutputVal();
        m_error += delta * delta;
    }
    m_error /= outputLayer.size() - 1; // get average error squared
    m_error = sqrt(m_error); // RMS

    // Implement a recent average measurement

    m_recentAverageError =
        (m_recentAverageError *  ErrorSmoothingFactor + m_error)
        / ( ErrorSmoothingFactor + 1.0);

    // Calculate output layer gradients

    for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
        outputLayer[n].calcOutputGradients(targetVals[n]);
    }

    // Calculate hidden layer gradients

    for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; --layerNum) {
        Layer& hiddenLayer = m_layers[layerNum];
        Layer& nextLayer = m_layers[layerNum + 1];

        for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
            hiddenLayer[n].calcHiddenGradients(nextLayer);
        }
    }

    // For all layers from outputs to first hidden layer,
    // update connection weights

    for (unsigned layerNum = m_layers.size() - 1; layerNum > 0; --layerNum) {
        Layer& layer = m_layers[layerNum];
        Layer& prevLayer = m_layers[layerNum - 1];

        for (unsigned n = 0; n < layer.size() - 1; ++n) {
            layer[n].updateInputWeights(prevLayer);
        }
    }
}

void Net::feedForward(const std::vector<double>& inputVals)
{
    assert(inputVals.size() == m_layers[0].size() - 1); // Asume (imputVals = InputLayerNeurons) else error

    // Assign (latch) the input values into the input neurons
    for (unsigned i = 0; i < inputVals.size(); ++i) { // for each input neuron 
        m_layers[0][i].setOutputVal(inputVals[i]);    // Set output of Layer0 (input layer) = it's Input  
    }

    // forward propagate
    for (unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum) {  // from 1 to LayerNum
        Layer& prevLayer = m_layers[layerNum - 1]; //  prevLayer reference

        for (unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n) {      // from 0 to last neuron
            m_layers[layerNum][n].feedForward(prevLayer);   // current neuron  Neuron::feedForward() ....  SUM imputs  of prev layer
        }
    }
}

Net::Net(const std::vector<unsigned>& topology)
{
    m_error = 0;
    m_recentAverageError = 0;
    unsigned numLayers = topology.size();                            //  get layers num
    for (unsigned layerNum = 0; layerNum < numLayers; ++layerNum) {  //  for all layers
        m_layers.push_back(Layer());                                 //  append new layer at the end of m_layer ( layer vector )  
        unsigned numOutputs =   ( layerNum == topology.size() - 1 ? 0 : topology[layerNum + 1])  ;  
        // Last layer ? NumOutputs = 0   else  NumOutputs = Next_Layer_Neurons

        for (unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {  // for every neuron in layer_num + Biass neuron
            m_layers.back().push_back( Neuron(numOutputs,neuronNum) );                // append new neuron() in last layer : "m_layers.back()" of m_layer 
            std::cout << "Made a Neuron!" << std::endl;
        }

        // Force the bias node's output to 1.0 (it was the last neuron pushed in this layer):
        m_layers.back().back().setOutputVal(1.0);
    }
}


void showVectorVals( std::string label, std::vector<double>& v)
{
    std::cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }

     std::cout << std::endl;
}


int main()
 {
    const char* filename = "trainingData.txt" ;
    TrainingData trainData( filename );

    // topology ej :   { 3, 2, 1 }   =>  3 layers :  3 inp , 2 hidden, 1 out 
    // 1 biass is added in each layer resulting in   4 inp   3 hidden  1 output 
    //  biass is used to "off center" the logic (sigmoid) function     
    std::vector<unsigned> topology;
    trainData.getTopology(topology);

    Net myNet(topology);

    std::vector<double> inputVals, targetVals, resultVals ;
    trainData.setVectors(inputVals, targetVals);

    int trainingPass = 0;
    uint i=0; 

    while (!trainData.isEof() && (i<1000)) {
        ++trainingPass;
        std::cout << std::endl << "Pass :" << trainingPass << "\t";

        // Get new input data and feed it forward:
        if (trainData.getNextInputs(inputVals) != topology[0]) {
           std::cout <<  "ERROR : INPUT MISMACH  !!! "; //   break;      
        }
        //showVectorVals("Inputs:", inputVals);
        myNet.feedForward(inputVals);

        // Collect the net's actual output results:
        myNet.getResults(resultVals);
        showVectorVals("Outputs:", resultVals);

        // Train the net what the outputs should have been:
        trainData.getTargetOutputs(targetVals);
        //showVectorVals("Targets:", targetVals);
        assert(targetVals.size() == topology.back());

        myNet.backProp(targetVals);

        // Report how well the training is working, average over recent samples:
        std::cout << "Net recent average error: "
            << myNet.getRecentAverageError() << std::endl;
            ++i;
    }
    myNet.printWeights();
    std::cout << std::endl << "Done" << std::endl;
}
