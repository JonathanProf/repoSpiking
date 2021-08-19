/*!
 * \file functions.h
 * \brief This file contains a group of utility functions
 */
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

/*!
 \def NUMPIXELS
 Number of total pixels of an image with dimensions 28 x 28
 */
#define NUMPIXELS 784

using namespace std;

/*!
 * \brief Function to load the weights or synapses from a file to facilitate the processing of the information in the program
 * \param weights Array of weights or synapses
 * \param fileName Name of the file to be uploaded
 * \param row Number of rows to be loaded
 * \param col Number of columns to be loaded
 */
void getWeights( float weights[8][784], string fileName, const int row = 8, const int col = 784 )
{
    string nombreArchivo = fileName;
    string data;

    ifstream infile;
    infile.open( nombreArchivo );

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    cout << "Read file" << endl;

    unsigned long long int n1 = 0, n2 = 0, longChar = 0;
    string tmp;
    for (int indx = 0; indx < row; ++indx) {

        infile >> data;
        if (infile.eof())
        {
            cout << "End of file " << fileName <<  " reached successfully" << endl;
        }
        n1 = 0;
        n2 = 0;

        for (int indj = 0; indj < col; ++indj) {
            n2 = data.find(",", n1);
            longChar = n2 - n1;
            try {

                if (n2 == std::string::npos) {
                    //cout << "not found\n";
                    n2 = data.length();
                    longChar = n2 - n1;

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    tmp = data.substr(n1,longChar);
                    weights[ indx ][ indj ] = std::stold(tmp);
                    //cout << "found: " << weights[indx] << endl;
                } else {

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    tmp = data.substr(n1,longChar);
                    weights[ indx ][ indj ] = std::stold(tmp);
                    //cout << "found: " << weights[indx] << endl;
                }
                n1 = n2 + 1;
            } catch (exception& e)
            {
                cerr << "Standard exception: (" << e.what() << ") indx (" << indx << ") - LINE -> " << __LINE__ << " - FUNC -> " << __func__ << endl;
                exit(1);
            }
        }
    }
    infile.close();
}

/*!
 * \brief Function to load the image from a file to facilitate the processing of the information in the program
 * \param img 28 x 28 pixel image
 * \param fileName Name of the file to be uploaded
 * \param row Number of rows to be loaded
 * \param col Number of columns to be loaded
 */
void loadImg( float img[28][28], string fileName, const int row, const int col )
{
    string nombreArchivo = fileName;
    string data;

    ifstream infile;
    infile.open( nombreArchivo );

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    cout << "Read file" << endl;

    infile >> data;
    if (infile.eof())
    {
        cout << "End of file " << fileName <<  " reached successfully" << endl;
    }

    unsigned long long int n1 = 0, n2 = 0, longChar = 0;
    for (int indx = 0; indx < row; ++indx) {
        for(int indy = 0; indy < col; ++indy) {
            n2 = data.find(",", n1);
            longChar = n2 - n1;
            try {
                if (n2 == std::string::npos) {
                    //cout << "not found\n";
                    n2 = data.length();
                    longChar = n2 - n1;

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    img[ indx ][ indy ] = std::stod(data.substr(n1,longChar));
                    //cout << "found: " << weights[indx] << endl;
                } else {

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    string tmp = data.substr(n1,longChar);
                    img[ indx ][ indy ] = std::stold(tmp);
                    //cout << "found: " << weights[indx] << endl;
                }
                n1 = n2 + 1;
            } catch (exception& e)
            {
                cerr << "Standard exception: (" << e.what() << ") indx (" << indx << ") - LINE -> " << __LINE__ << " - FUNC -> " << __func__ << endl;
                exit(1);
            }
        }
    }
    infile.close();
}

/*!
 * \brief Function to load the encoded image from a file to facilitate the processing of the information in the program
 * \param img Encoded image, each of the 28x28 pixels encoded in 200ms in time
 * \param fileName Name of the file to be uploaded
 */
void encoding( bool img[784][201], string fileName){

    const int row = 784;
    const int col = 201;

    string nombreArchivo = fileName;
    string data;

    ifstream infile;
    infile.open( nombreArchivo );

    if (!infile.is_open())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }

    cout << "Read file" << endl;

    unsigned long long int n1 = 0, n2 = 0, longChar = 0;
    string tmp;
    for (int indNeuron = 0; indNeuron < row; ++indNeuron) {
        infile >> data;
        if (infile.eof())
        {
            cout << "End of file " << fileName <<  " reached successfully" << endl;
        }
        n1 = 0;
        n2 = 0;

        for(int indTime = 0; indTime < col; ++indTime) {
            n2 = data.find(",", n1);
            longChar = n2 - n1;
            try {
                if (n2 == std::string::npos) {
                    //cout << "not found\n";
                    n2 = data.length();
                    longChar = n2 - n1;

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    tmp = data.substr(n1,longChar);
                    img[ indNeuron ][ indTime ] = (tmp == "False") ? false : true;
                    //cout << "found: " << weights[indx] << endl;
                } else {

                    //cout << "found: " << s.substr(n1,longChar) << endl;
                    tmp = data.substr(n1,longChar);
                    img[ indNeuron ][ indTime ] = (tmp == "False") ? false : true;
                    //cout << "found: " << weights[indx] << endl;
                }
                n1 = n2 + 1;
            } catch (exception& e)
            {
                cerr << "Standard exception: (" << e.what() << ") ind Neuron (" << indNeuron << ") - LINE -> " << __LINE__ << " - FUNC -> " << __func__ << endl;
                exit(1);
            }
        }
    }
    infile.close();
}

/*!
 * \brief dotPoint
 * \param syn Vector of synapses per neuron
 * \param pixels_x_time Pixels encoded in time by probability distribution
 * \param t Time stamp where processing takes place
 * \return Real value as a result of synaptic contributions for the analyzed neuron
 */
float dotPoint( float syn[NUMPIXELS], bool pixels_x_time[NUMPIXELS][201], int t ){
    float acum = 0.0f;

    for (int i = 0; i < NUMPIXELS; ++i) {
        acum += syn[i] * pixels_x_time[i][t];
    }
    return acum;
}

/*!
 * \brief Calculates the maximum neuron output potential
 * \param active_pot array of potentials
 * \return The maximum neuron output potential
 */
float maxPotential( float active_pot[8] ){
    float maxP = 0.0;
    for (int i = 0; i < 8; ++i) {
        if ( active_pot[i] > maxP ) {
            maxP = active_pot[i];
        }
    }
    return maxP;
}

/*!
 * \brief Determines which neuron has generated an action potential at the output.
 * \param active_pot Array with current action potentials
 * \return The index of the neuron that has generated the first firing in time
 */
unsigned int winnerTakeAll(float active_pot[8]){

    unsigned int index = 0;
    float tmpPot = active_pot[0];
    for (int i = 0; i < 8; ++i) {
        if ( active_pot[i] > tmpPot  ) {
            tmpPot = active_pot[i];
            index = i;
        }
    }

    return index;
}

/*!
 * \brief Allows the calculation of the membrane potential from the receptive field.
 * \param pot Potential matrix
 * \param inp Input image
 */
void receptiveField(float pot[28][28], float inp[28][28] )
{
    const int kernel = 5;
    float w[kernel][kernel] = {
        {-0.5,-0.125,  0.25,  -0.125, -0.5  },
        {-0.125 , 0.25  , 0.625 , 0.25 , -0.125},
        { 0.25   ,0.625 , 1. ,    0.625 , 0.25 },
        {-0.125 , 0.25  , 0.625 , 0.25,  -0.125},
        {-0.5  , -0.125 , 0.25 , -0.125 ,-0.5  }};

    const int ran[kernel] = {-2,-1,0,1,2};
    int ox = 2;
    int oy = 2;

    for (int i = 0; i < 28; ++i) {
        for (int j = 0; j < 28; ++j) {
            float summ = 0;

            for (int m = 0; m < kernel; ++m) {
                for (int n = 0; n < kernel; ++n) {
                    if( (i + ran[m]) >= 0 && (i + ran[m]) <= 15 && ( j + ran[n] ) >= 0 && ( j + ran[n] ) <= 15 )
                    {
                        summ = summ + w[ox+ran[m]][oy+ran[n]]*(float)inp[i+ran[m]][j+ran[n]]/255.0f;
                    }
                }
            }
            pot[i][j] = summ;
        }
    }
}

#endif // FUNCTIONS_H
