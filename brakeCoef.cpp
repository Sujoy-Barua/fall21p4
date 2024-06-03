/*
Sujoy Barua (uniqname: sujoysb)
Partner: None
Lab Section: 020
Date: 11/03/2021

Program Description: The following program takes in 3 input from the user: initial velocity (v0), shuttle's coefficient of drag (c_d), 
and the length of the runway (runwayLength). Then it outputs the optimal braking coefficient determined using
several mathematical caulculations.
*/

#include <iostream>
using namespace std;

int main() {

  double V0; // initializing v0 and prompting user for input
  cout << "v0 (m/s): ";
  cin >> V0; 
  double Cd; // initializing cd and prompting user for input
  cout << "c_d (1/m): ";
  cin >> Cd;
  double runwayLength; // initializing runwayLength and prompting user for input
  cout << "runwayLength (m): ";
  cin >> runwayLength;

  //initializing the variables needed throughout the code
  double bNodrag = (V0*V0) / (2.0 * runwayLength);
  double bMin = 0; // minimum braking coefficient possible (while not using the brakes at all)
  double bMax = bNodrag;
  double bMid = (bMin + bMax)/2.0; // midpoint of the initial range
  double tolerance = 0.000001;
  double deltaT = 0.00001;
  double v = V0;
  double x = 0;
  double a;
  double simDist;
  double bOptimal;

  // creating a while loop that runs while the range of braking coefficient is greater than or equal to tolerance
  while (bMax - bMin >= tolerance) { 
    bMid = (bMin + bMax)/2.0; // calculating new bMid
    v = V0;                   // setting v equal to user's input of initial velocity
    x = 0;                    // setting x equal to 0 or the beginning of the runway 

    // runs while velocity is positive
    while (v > 0) {          
      a = - bMid - Cd*(v*v);
      v = v + a * deltaT;
      x = x + v * deltaT;
    }
    simDist = x; // sets simulated distance equal to the final distance calculated by the loop above 
    
    // if we stopped early, change the range to the first half of old range (bMin remains the same)
    if (simDist < runwayLength) { 
      bMax = bMid;                
    } 
    
    // if we stopped late, change the range to second half of old range (bMax remains the same)
    else { 
      bMin = bMid;                
    }
  }
  bOptimal = (bMin + bMax)/2; // Optimal braking coefficient should be quite close to the bMid of the final range
  cout << "b_Optimal = "<< bOptimal << endl;
  return 0;
}
