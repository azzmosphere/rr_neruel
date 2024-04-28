// https://www.geeksforgeeks.org/ml-neural-network-implementation-in-c-from-scratch/
// http://robotics.hobbizine.com/arduinoann.html
// https://github.com/Whiax/NeuralNetworkCpp/blob/master/src/neuralmain.cpp
// https://medium.com/@doleron/deep-learning-from-scratch-in-modern-c-activation-functions-5fef24503be2
// https://ai.stackexchange.com/questions/16045/why-is-there-a-sigmoid-function-in-the-hidden-layer-of-a-neural-network
// https://home.csulb.edu/~wmartinz/content/introduction-neural-nets-part-2.html
// https://neptune.ai/blog/backpropagation-algorithm-in-neural-networks-guide
// https://mathvault.ca/hub/higher-math/math-symbols/calculus-analysis-symbols/


// Masy be use OpenNN see if it works,  could be a lot easier than inventing my own one.

// vector is a increasing/decreasing array, it can vary in size
// SNIP -- actual code here.

/******************************************************************
 * ArduinoANN - An artificial neural network for the Arduino
 * All basic settings can be controlled via the Network Configuration
 * section.
 * See robotics.hobbizine.com/arduinoann.html for details.
 ******************************************************************/

#include <math.h>
#include <cstdio>
#include <iostream>

#define DOUBLE_MERSENNE_NUMBER_1 7
#define DOUBLE_MERSENNE_NUMBER_2 127
#define DOUBLE_MERSENNE_NUMBER_3 2147483647
#define DOUBLE_MERSENNE_NUMBER_4 170141183460469231731687303715884105727

/******************************************************************
 * Network Configuration - customized per network
 ******************************************************************/
const int PatternCount = 10;
const int InputNodes = 7;
const int HiddenNodes = 8;
const int OutputNodes = 4;
const float LearningRate = 0.3;
const float Momentum = 0.9;
const float InitialWeightMax = 0.5;
const float Success = 0.0004;

/**
 * Input pattern,
 *
 * || POS || Func  || Range   ||  Description                                |
 * | ----- | -----  | -------- | ------------------------------------------- |
 * |  0    | DFW    |  0 - 255 |   Distance from wall (directly in front.)   |
 * |  1    | LL     |  0 or 1  |   1 if vehicle turned right to avoid a wall |
 * |  2    | LR     |  0 or 1  |   1 if vehicle turned left to avoid a wall  |
 * |  3    | SPD    |  0 - 255 |   Speed                                     |
 *
 */
const uint8_t Input[PatternCount][InputNodes] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {0, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
};

/**
 * Output nodes,
 * || POS || Func  || Range   ||  Description                                |
 * | ----- | -----  | -------- | ------------------------------------------- |
 * |    0  |  MTBA  | 0 - 255  | How much power to feed Motor A              |
 * |    1  |  MTBB  | 0 - 255  | How much power to fee Motor B               |
 * |    2  |  DELTA | 1 - 30   | How many seconds to wait after motor        |
 * |       |        |          | command given.                              |
 */

const uint8_t Target[PatternCount][OutputNodes] = {
    {0, 0, 0, 0}, // 0
    {0, 0, 0, 1}, // 1
    {0, 0, 1, 0}, // 2
    {0, 0, 1, 1}, // 3
    {0, 1, 0, 0}, // 4
    {0, 1, 0, 1}, // 5
    {0, 1, 1, 0}, // 6
    {0, 1, 1, 1}, // 7
    {1, 0, 0, 0}, // 8
    {1, 0, 0, 1}  // 9
};

#define A1 1

typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));

extern "C"
{
#include "stdlib.h"
}

void randomSeed(unsigned long seed)
{
  if (seed != 0)
  {
    srandom(seed);
  }
}

int analogRead(uint8_t pin)
{
  return 23;
}

long random(long howbig)
{
  return 42;
  if (howbig == 0)
  {
    return 0;
  }
  return random() % howbig;
}

// variables that I think need to maintain state.
float Hidden[HiddenNodes];
float Output[OutputNodes];
float HiddenWeights[InputNodes + 1][HiddenNodes];
float OutputWeights[HiddenNodes + 1][OutputNodes];
float HiddenDelta[HiddenNodes];
float OutputDelta[OutputNodes];
float ChangeHiddenWeights[InputNodes + 1][HiddenNodes];
float ChangeOutputWeights[HiddenNodes + 1][OutputNodes];

// local vairables that can go into setup routine.

int i, j, p, q, r;
int ReportEvery1000;
// int RandomizedIndex[PatternCount];
long TrainingCycle;
float Rando;
float Error;
float Accum;

void toTerminal();

/******************************************************************
 * Initialize HiddenWeights and ChangeHiddenWeights
 ******************************************************************/
void initializeHidden()
{
  printf("INFO: Initialize HiddenWeights and ChangeHiddenWeights\n");
  for (i = 0; i < HiddenNodes; i++)
  {
    for (j = 0; j <= InputNodes; j++)
    {
      ChangeHiddenWeights[j][i] = 0.0;
      Rando = float(random(100)) / 100;
      HiddenWeights[j][i] = 2.0 * (Rando - 0.5) * InitialWeightMax;
    }
  }
}

/******************************************************************
 * Initialize OutputWeights and ChangeOutputWeights
 ******************************************************************/
void initializeOutput()
{
  printf("INFO: Initialize OutputWeights and ChangeOutputWeights\n");
  for (i = 0; i < OutputNodes; i++)
  {
    for (j = 0; j <= HiddenNodes; j++)
    {
      ChangeOutputWeights[j][i] = 0.0;
      Rando = float(random(100)) / 100;
      OutputWeights[j][i] = 2.0 * (Rando - 0.5) * InitialWeightMax;
    }
  }
}

void backpropagate(uint8_t ingress[InputNodes])
{
  /******************************************************************
   * Compute hidden layer activations
   ******************************************************************/
  printf("INFO:  Compute hidden layer activations\n");
  for (i = 0; i < HiddenNodes; i++)
  {
    Accum = HiddenWeights[InputNodes][i];
    for (j = 0; j < InputNodes; j++)
    {
      // only want the initial vector,  not [p][j] or y x
      Accum += ingress[j] * HiddenWeights[j][i];
    }
    Hidden[i] = 1.0 / (1.0 + exp(-Accum));
  }

  //////////////////////////////

  /******************************************************************
   * Compute output layer activations and calculate errors
   ******************************************************************/
  for (i = 0; i < OutputNodes; i++)
  {
    Accum = OutputWeights[HiddenNodes][i];
    for (j = 0; j < HiddenNodes; j++)
    {
      Accum += Hidden[j] * OutputWeights[j][i];
    }
    Output[i] = 1.0 / (1.0 + exp(-Accum));
    OutputDelta[i] = (Target[p][i] - Output[i]) * Output[i] * (1.0 - Output[i]);
    Error += 0.5 * (Target[p][i] - Output[i]) * (Target[p][i] - Output[i]);
    
  }
  printf("INFO: Compute output layer activations and calculate errors %9.6f\n", Error);

  /******************************************************************
   * Backpropagate errors to hidden layer
   ******************************************************************/
  
  for (i = 0; i < HiddenNodes; i++)
  {
    Accum = 0.0;
    for (j = 0; j < OutputNodes; j++)
    {
      Accum += OutputWeights[i][j] * OutputDelta[j];
    }
    HiddenDelta[i] = Accum * Hidden[i] * (1.0 - Hidden[i]);
    printf("INFO: Backpropagate errors to hidden layer\n");
  }

  // Stop propagation.

  /******************************************************************
   * Update Inner-->Hidden Weights
   ******************************************************************/
  printf("INFO: Update Inner-->Hidden Weights\n");
  for (i = 0; i < HiddenNodes; i++)
  {
    ChangeHiddenWeights[InputNodes][i] = LearningRate * HiddenDelta[i] + Momentum * ChangeHiddenWeights[InputNodes][i];
    HiddenWeights[InputNodes][i] += ChangeHiddenWeights[InputNodes][i];
    for (j = 0; j < InputNodes; j++)
    {
      ChangeHiddenWeights[j][i] = LearningRate * ingress[j] * HiddenDelta[i] + Momentum * ChangeHiddenWeights[j][i];
      HiddenWeights[j][i] += ChangeHiddenWeights[j][i];
    }
  }

  /******************************************************************
   * Update Hidden-->Output Weights
   ******************************************************************/
  printf("INFO:  Update Hidden-->Output Weights\n");
  for (i = 0; i < OutputNodes; i++)
  {
    ChangeOutputWeights[HiddenNodes][i] = LearningRate * OutputDelta[i] + Momentum * ChangeOutputWeights[HiddenNodes][i];
    OutputWeights[HiddenNodes][i] += ChangeOutputWeights[HiddenNodes][i];
    for (j = 0; j < HiddenNodes; j++)
    {
      ChangeOutputWeights[j][i] = LearningRate * Hidden[j] * OutputDelta[i] + Momentum * ChangeOutputWeights[j][i];
      OutputWeights[j][i] += ChangeOutputWeights[j][i];
    }
  }
}

void train()
{
  // printf("Initial/Untrained Outputs: ");
  // toTerminal();
  /******************************************************************
   * Begin training
   ******************************************************************/

  for (TrainingCycle = 1; TrainingCycle < 7000; TrainingCycle++)
  {

    Error = 0.0;
    /******************************************************************
     * Cycle through each training pattern in the randomized order
     ******************************************************************/
    printf("INFO:  Cycle through each training pattern\n");
    for (p = 0; p < PatternCount; p++)
    {
      // p = RandomizedIndex[q];
      uint8_t ingress[InputNodes];
      for (i = 0; i < InputNodes; i++)
      {
        ingress[i] = Input[p][i];
      }

      backpropagate(ingress);
      printf("INFO: trainingCycle: %ld   error = %9.6f success = %9.6f \n", TrainingCycle, Error, Success);
    }

    /******************************************************************
     * If error rate is less than pre-determined threshold then end
     ******************************************************************/

    if (Error < Success) {
      printf("INFO: Training Set Solved!\n");
      break;
    }
  }

  printf("INFO: trainingCycle: %ld   error = %9.6f success = %9.6f \n", TrainingCycle, Error, Success);
  // toTerminal();

  ReportEvery1000 = 1;
}

void toTerminal()
{

  for (p = 0; p < PatternCount; p++)
  {
    printf("  Training Pattern: %d\n", p);

    printf("  Input ");
    for (i = 0; i < InputNodes; i++)
    {
      printf("%d ", Input[p][i]);
    }
    printf("  Target ");
    for (i = 0; i < OutputNodes; i++)
    {
      printf("%d ", Target[p][i]);
    }
    /******************************************************************
     * Compute hidden layer activations
     ******************************************************************/
    printf("INFO:  Compute hidden layer activations\n");
    for (i = 0; i < HiddenNodes; i++)
    {
      Accum = HiddenWeights[InputNodes][i];
      for (j = 0; j < InputNodes; j++)
      {
        Accum += Input[p][j] * HiddenWeights[j][i];
      }

      // this is the sigmoid function.
      Hidden[i] = 1.0 / (1.0 + exp(-Accum));
    }

    /******************************************************************
     * Compute output layer activations and calculate errors
     ******************************************************************/
    printf("INFO:  Compute output layer\n");
    for (i = 0; i < OutputNodes; i++)
    {
      Accum = OutputWeights[HiddenNodes][i];
      for (j = 0; j < HiddenNodes; j++)
      {
        Accum += Hidden[j] * OutputWeights[j][i];
      }
      Output[i] = 1.0 / (1.0 + exp(-Accum));
    }
    printf("  Output ");
    for (i = 0; i < OutputNodes; i++)
    {
      printf("%.5f ", Output[i]);
    }
  }
}

/*******************************/

using namespace std;

void getPrediction(uint8_t ingress[InputNodes])
{

  /******************************************************************
   * Compute hidden layer activations
   ******************************************************************/
  printf("INFO:   Compute hidden layer activations\n");
  for (i = 0; i < HiddenNodes; i++)
  {
    Accum = HiddenWeights[InputNodes][i];
    for (j = 0; j < InputNodes; j++)
    {
      Accum += ingress[j] * HiddenWeights[j][i];
    }

    // this is the sigmoid function.
    Hidden[i] = 1.0 / (1.0 + exp(-Accum));
  }

  /******************************************************************
   * Compute output layer activations and calculate errors
   ******************************************************************/
  printf("INFO:   Compute hidden layer activations\n");
  for (i = 0; i < OutputNodes; i++)
  {
    Accum = OutputWeights[HiddenNodes][i];
    for (j = 0; j < HiddenNodes; j++)
    {
      Accum += Hidden[j] * OutputWeights[j][i];
    }
    Output[i] = 1.0 / (1.0 + exp(-Accum));
  }

  for (i = 0; i < OutputNodes; i++)
  {
    printf("INFO: col: %d value: %.5f\n", i, Output[i]);
  }
}

void setup()
{
  randomSeed(analogRead(3));
  ReportEvery1000 = 1;
  for (p = 0; p < PatternCount; p++)
  {
    // RandomizedIndex[p] = p;
  }
  initializeHidden();
  initializeOutput();
  train();
  // toTerminal();
  cout << endl;
}

int main()
{
  setup();

  cout << "INFO Begin processing data." << endl;
  cout << "INFO: Prediction: 1, 1, 1, 0, 0, 0, 0 " << endl;
  cout << "INFO: Expected 0, 0, 0, 0" << endl;
  uint8_t ingress[InputNodes] = {1, 1, 1, 0, 0, 0, 0};
  getPrediction(ingress);

  cout << "INFO: Prediction: 1, 1, 0, 1, 1, 0, 1 " << endl;
  cout << "INFO: Expected 0, 0, 0, 1" << endl;
  uint8_t ingress2[InputNodes] = {1, 1, 0, 1, 1, 0, 1};
  getPrediction(ingress2);

  return 0;
}
