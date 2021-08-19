/*!
 * \file main.cpp
 */
/*! \mainpage Index Page
 * Navigate through the files for additional information.<br>
 * main.cpp, neuron.h, neuron.cpp, functions.h
 */

#include <string>
#include <cstdlib>
#include "neuron.h"
#include "functions.h"


#define DEBUG 1

using namespace std;

int main(int argc, char *argv[])
{    
#if (DEBUG != 1)
    assert(("Check your entries", argc > 1));
#endif
    const unsigned short int T = 200;
    unsigned int time[T] = {0};

    for (int indx = 0; indx < T; ++indx) {
        time[indx] = indx + 1;
    }
#if (DEBUG == 1)
    const float Pth =150.0f;
#else
    const float Pth = (argc > 2) ? std::stof(argv[1]) : 150.0f;
#endif
    const unsigned int m = NUMPIXELS;

#if (DEBUG == 1)
    const unsigned short int n = 8;
#else
    unsigned short int n = (argc > 3) ? stoi(argv[2]) : 8;
#endif
    unsigned short int epoch = 1;
#if (DEBUG == 1)
    const unsigned short int num_of_images = 2;
#else
    unsigned short int num_of_images = (argc > 4) ? stoi(argv[3]) : 6;
#endif

    // Neuron Init
    neuron layer2[n];

    float synapse[n][m] = {{0}};

    getWeights(synapse, "./weights/synapse.csv" );


    float Pot[28][28] = {{0}};
    float img[28][28] = {{0}};
    bool pixelsEncoded[784][201] = {{0}};

    bool f_spike = 0;

    float active_pot[n] = {0.0f};

    for (int k = 0; k < epoch; ++k) {
        for (int i = 1; i <= 2; ++i) {

            unsigned int spike_count[n] = {0};

            for (int neurIndx = 0; neurIndx < n; ++neurIndx) {
                layer2->initial();
            }
            string filename = "./img/img_" + to_string(i-1) + ".csv";
            loadImg( img, filename, 28,28);
            receptiveField(Pot, img);

            filename = "./enc/img_enc_" + to_string(i-1) + ".csv";
            encoding(pixelsEncoded, filename);

            f_spike = 0;
            for (int i = 0; i < n; ++i) {
                active_pot[i] = 0.0f;
            }

            /*! time analysis */
            for (int indT = 0; indT < T; ++indT)
            {

                for (int j = 0; j < n; ++j)
                {

                    /*! Update potential if not in refractory period */
                    if ( layer2[j].get_t_rest() < time[indT] )
                    {
                        float dp = dotPoint( &synapse[j][0], pixelsEncoded, time[indT] );
                        layer2[j].setPotencial( layer2[j].getPotencial() + dp );

                        if( layer2[j].getPotencial() > layer2[j].getPotencialRest() )
                        {
                            layer2[j].setPotencial( layer2[j].getPotencial() - layer2[j].getPotencialD() );
                        }
                        active_pot[j] = layer2[j].getPotencial();
                    }
                }

                /*! Lateral Inhibition step */
                if ( f_spike == 0 )
                {
                    float high_pot = maxPotential(active_pot);

                    if ( high_pot > Pth )
                    {
                        f_spike = 1;
                        unsigned int winner = winnerTakeAll(active_pot);

                        for (unsigned int s = 0; s < n; ++s)
                        {
                            if ( s != winner ) {
                                layer2[s].setPotencial( layer2[s].getPotentialmin() );
                            }

                        }
                    }
                }

                /*! Check spike count */
                for (int j = 0; j < n; ++j) {
                    int s = layer2[j].check();
                    if( s == 1 )
                    {
                        ++spike_count[j];
                        layer2[j].set_T_rest( time[indT] + layer2[j].get_t_ref() );
                    }
                }
            }
            printf("image = %s\n",filename.c_str());
            for (int i = 0; i < n; ++i) {
                printf("spike_count[%d]=[%d]\n",i, spike_count[i]);
            }

        }
    }

    return 0;
}
