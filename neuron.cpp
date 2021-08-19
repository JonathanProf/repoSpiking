/*!
 * \file neuron.cpp
 * \brief Source file of class neuron
 */

#include "neuron.h"

neuron::neuron()
{
    config();
}

void neuron::config( float Pth, float Prest, float Pmin, float D, float t_ref, float t_rest)
{
    this->Pth = Pth;
    this->t_ref = t_ref;
    this->t_rest = t_rest;
    this->P = Prest;
    this->D = D;
    this->Pmin = Pmin;
    this->Pref = Prest;
}

bool neuron::check()
{
    if ( this->P >= this->Pth )
    {
        this->P = this->Pref;
        return 1;
    }
    else if ( this->P < this->Pmin )
    {
        this->P  = this->Prest;
        return 0;
    }
    else
    {
        return 0;
    }
}

void neuron::inhibit()
{
    this->P  = this->Pmin;
}

void neuron::initial()
{
    this->t_rest = -1.0;
    this->P = this->Prest;
}

float neuron::get_t_rest(){
    return this->t_rest;
}

void neuron::setPotencial(float _pot){
    this->P = _pot;
}

float neuron::getPotencial(){
    return this->P;
}

float neuron::getPotencialRest(){
    return this->Prest;
}

float neuron::getPotencialD(){
    return this->D;
}

float neuron::getPotencialTh(){
    return this->Pth;
}

float neuron::getPotentialmin(){
    return this->Pmin;
}

void neuron::set_T_rest(float _t_rest){
    this->t_rest = _t_rest;
}

float neuron::get_t_ref(){
    return this->t_ref;
}
