/**************************************************************************
 * Provides common inline functions used by RR. 
 * NOTE: that all functions provied in this header must be re-entrant.
 * and must be inline.
**************************************************************************/

#ifndef RRUTILES_HPP
#define RRUTILES_HPP

#include <string>
#include <math.h>
#include <stdlib.h>
#include <random>

#include "Logger.hpp"

using namespace std;


static inline string trim(string s)
{
    // Removes all spaces from the beginning of the string
    while (s.size() && isspace(s.front()))
        s.erase(s.begin());

    // Removes all spaces from the end of the string
    while (!s.empty() && isspace(s[s.size() - 1]))
        s.erase(s.end() - 1);
    return s;
}


// based on https://codingnest.com/generating-random-numbers-using-c-standard-library-the-problems/
//
// In theory this code should use the /dev/urandom or any other hardware set as the random number generator.
static inline float nn_random()
{
  // Truly random seed.
  std::mt19937 rng(std::random_device{}());

  // Avoid constructing distribution all the time
  std::uniform_int_distribution<> dist(0, 100);

  float r = float(dist(rng)) / 100.0f;

  return r;
}

static inline float sigmoid(float x) {
  return 1.0f / (1 + exp(-x));
}

static inline float d_sigmoid(float x){
  return (x * (1 - x));
}

#endif