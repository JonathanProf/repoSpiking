/*!
 * \file neuron.h
 */
#ifndef NEURON_H
#define NEURON_H

/*!
 * \brief The neuron class allows to store the attributes corresponding to the neuron, e.g. membrane potentials, time constants, etc.
 */
class neuron
{
public:
    /*!
     * \brief Default constructor
     */
    neuron();

    /*!
     * \brief Method that allows the initialization of parameters of each neuron
     * \param Pth Potential corresponding to the firing threshold of the neuron.
     * \param Prest Resting potential
     * \param Pmin Minimum membrane potential
     * \param D Normalization potential parameter
     * \param t_ref Refractory time
     * \param t_rest Resting time
     */
    void config( float Pth = 140.0f, float Prest = 0.0f, float Pmin = -1.0, float D =0.5f, float t_ref = 4.0f, float t_rest = -1.0);

    /*!
     * \brief Checks whether the membrane potential threshold has been exceeded
     * \return **true** if the membrane potential threshold has been exceeded, **false** in other cases
     */
    bool check();

    /*!
     * \brief Membrane potential inhibition is performed to control neuron firing.
     */
    void inhibit();

    /*!
     * \brief Initial settings for each sample supplied to the network
     */
    void initial();

    /*!
     * \brief Function to return the rest time
     * \return Resting time is returned
     */
    float get_t_rest();

    /*!
     * \brief Updates membrane potential
     * \param _pot Updated membrane potential
     */
    void setPotencial( float _pot);

    /*!
     * \brief Gets the membrane potential
     * \return Membrane potential as a float value
     */
    float getPotencial();

    /*!
     * \brief Gets the resting potential
     * \return Resting potential as a float value
     */
    float getPotencialRest();

    /*!
     * \brief Gets the normalization parameter
     * \return Normalization parameter as a float value
     */
    float getPotencialD();

    /*!
     * \brief Gets the threshold potential
     * \return Threshold potential as a float value
     */
    float getPotencialTh();

    /*!
     * \brief Gets the minimum potential constant
     * \return Minimum potential constant as a float value
     */
    float getPotentialmin();

    /*!
     * \brief Sets the resting time
     * \param _t_rest Must be entered to establish the resting time considering the displacement over time
     */
    void set_T_rest( float _t_rest );

    /*!
     * \brief Gets the refractory time
     * \return refractory time as a float value
     */
    float get_t_ref();

private:
    float Pth;          //!<Potential corresponding to the firing threshold of the neuron.
    float t_ref;        //!<Refractory time
    float t_rest;       //!<Resting time
    float P;            //!<Membrane potential
    float D;            //!<Normalization potential parameter
    float Pmin;         //!<Minimum potential constant
    float Prest = 0.0f; //!<Resting potential
    float Pref;         //!<Refractory potential
};

#endif // NEURON_H
