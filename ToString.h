/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ToString.h
 * Author: osmc
 *
 * Created on 24 October 2016, 19:19
 */

#ifndef TOSTRING_H
#define TOSTRING_H

#include <sstream>
#include <string>

template <class T>
std::string ToString(T value)
{
	std::ostringstream ostrm;
	ostrm << value;
	return ostrm.str();
}


#endif /* TOSTRING_H */

