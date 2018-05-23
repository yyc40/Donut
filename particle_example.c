#include "Particle.h" 
// to use the Particle class, we must include its header file
// this header will declare to the program what the class contains and what it can do


#include <iostream>
// now that we know what a header file is, we can explain that the above line includes
// the iostream functionality from the standard C++ library,
// which is what allows us to print our messages to the screen (via cout)
using namespace std;
// we still havent explained namespace yet doubleffffdathough ...





// rememeber, all executable programs must have a main() function
// this is where program execution starts
int main() 
{

  double mass  = 0.938; //GeV (a proton)
  double px  = 50.0; double py=40.0; double pz=39.0 ; //GeV

  // now we create a Particle object which has these values
  // this will use the normal constructor defined in Particle.cc
  Particle p1(mass,px,py,pz);

  // and here is an example of how to use functions belonging to a class (its methods)
  cout<<endl;
  cout<<"Particle 1: mass = " << p1.GetMass();
  cout<< "; momentum = " << p1.GetMomentum();
  cout<< "; energy = " << p1.GetEnergy();
  cout<<"; transverse mom= "<<p1.GetTransverseMomentum();
  cout<<"; azimuthal angle= "<<p1.GetPhi()<<" degree"<<endl;
  // we can make another particle as a different object but using the same class
  // lets say it has the same mass but a different momentum.

  double px2=40.0;double py2=10.0;double pz2=11.0;
  double new_mass=29.0;
 
  Particle p2(mass,px2,py2,pz2);

  cout<<endl;
  cout<< "Particle 2: mass = " << p2.GetMass();
  cout<< "; momentum = " << p2.GetMomentum();
  cout<< "; energy = " << p2.GetEnergy();
  cout<<"; transverse mom= "<<p2.GetTransverseMomentum();
  cout<<"; azimuthal angle= "<<p2.GetPhi()<<" degree"<<endl;
//  cout<<";set mass="<< p2.SetMass()<<endl;


  return 0;

}

