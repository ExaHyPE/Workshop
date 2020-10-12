// This file was generated by the ExaHyPE toolkit.
// It will NOT be regenerated or overwritten.
// Please adapt it to your own needs.
// 
// ========================
//   www.exahype.eu
// ========================

#include "AcousticWaveSolver.h"

#include "AcousticWaveSolver_Variables.h"

#include "kernels/KernelUtils.h"
#include "peano/utils/Loop.h"

tarch::logging::Log Linear::AcousticWaveSolver::_log( "Linear::AcousticWaveSolver" );


void Linear::AcousticWaveSolver::init(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  initPointSourceLocations(cmdlineargs,constants);	
}

void Linear::AcousticWaveSolver::adjustPointSolution(const double* const x,const double t,const double dt,double* const Q) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  VariableShortcuts s;
  if (tarch::la::equals(t,0.0)) {
    Q[s.p    ] = 0.0;
    Q[s.v + 0] = 0.0;
    Q[s.v + 1] = 0.0;
    Q[s.rho]   = 1.0;
    Q[s.c]     = 1.0;
  }
}

void Linear::AcousticWaveSolver::boundaryValues(const double* const x,const double t,const double dt,const int faceIndex,const int direction,const double* const fluxIn,const double* const stateIn,const double* const gradStateIn,double* const fluxOut,double* const stateOut) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.

  //abc
  VariableShortcuts s;
  int u_ind, v_ind;

  if (direction == 0){
    u_ind = s.v + 0;
    v_ind = s.v + 1;
  }else{
    u_ind = s.v + 1;
    v_ind = s.v + 0;
  }


  //abc  
  stateOut[0]     =    stateIn[0];
  stateOut[u_ind] =    stateIn[u_ind];
  stateOut[v_ind] =    stateIn[v_ind];
  stateOut[3]     =    stateIn[3];
  stateOut[4]     =    stateIn[4];

  fluxOut[0]      =   -fluxIn[0];
  fluxOut[1]      =    fluxIn[1];
  fluxOut[2]      =    fluxIn[2];
}

exahype::solvers::Solver::RefinementControl Linear::AcousticWaveSolver::refinementCriterion(const double* const luh,const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize,double t,const int level) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  // Tip: See header file "peano/utils/Loop.h" for dimension-agnostic for loops.
  
  return exahype::solvers::Solver::RefinementControl::Keep;
}

//*****************************************************************************
//******************************** PDE ****************************************
// To use other PDE terms, specify them in the specification file, delete this 
// file and its header and rerun the toolkit
//*****************************************************************************


void Linear::AcousticWaveSolver::eigenvalues(const double* const Q,const int direction,double* const lambda) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  VariableShortcuts s;
  double c = Q[s.c];

  lambda[0] =   c;
  lambda[1] =  -c;
  lambda[2] = 0.0;
}

void Linear::AcousticWaveSolver::flux(const double* const Q,double** const F) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  VariableShortcuts s;
  
  F[0][0] = -Q[s.v + 0];
  F[0][1] =        0.0;
  F[0][2] =        0.0;
  
  F[1][0] = -Q[s.v + 1];
  F[1][1] =        0.0;
  F[1][2] =        0.0;
  
}




void  Linear::AcousticWaveSolver::nonConservativeProduct(const double* const Q,const double* const * const gradQ,double** const BgradQ) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  
  VariableShortcuts s;
  BgradQ[0][0] =        0.0;
  BgradQ[0][1] = -gradQ[0][s.p];
  BgradQ[0][2] =        0.0;
  
  BgradQ[1][0] =        0.0;
  BgradQ[1][1] =        0.0;
  BgradQ[1][2] = -gradQ[1][s.p];
  
}


void  Linear::AcousticWaveSolver::initPointSourceLocations(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants){
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.

  pointSourceLocation[0][0] = 5.0;
  pointSourceLocation[0][1] = 5.0;
}

void  Linear::AcousticWaveSolver::pointSource(const double* const Q,const double* const x,const double t,const double dt, double* const forceVector, int n) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  VariableShortcuts s;
  double pi = 3.14159265359;
  double sigma = 0.1149;
  double t0 = 0.7;
  double f = 0.0;
  double M0 = 1000.0;

  f = (1.0/(sigma*std::sqrt(2.0*pi)))*(std::exp(-((t-t0)*(t-t0))/(2.0*sigma*sigma)));

  forceVector[s.p    ] = f;
  forceVector[s.v + 0] = 0.0;
  forceVector[s.v + 1] = 0.0;
}

void Linear::AcousticWaveSolver::multiplyMaterialParameterMatrix(const double* const Q, double** const rhs) {
  // Tip: You find documentation for this method in header file "Linear::AcousticWaveSolver.h".
  // Tip: See header file "Linear::AbstractAcousticWaveSolver.h" for toolkit generated compile-time 
  //      constants such as Order, NumberOfVariables, and NumberOfParameters.
  VariableShortcuts s;
  
  double rho    = Q[s.rho];
  double c      = Q[s.c];
  double lambda = rho*c*c;
  
  // rhs[0][s.p    ] = lambda*rhs[0][s.p];
  // rhs[0][s.v + 0] = 1.0/rho*rhs[0][s.v+0];
  // rhs[0][s.v + 1] = 1.0/rho*rhs[0][s.v+1];
  
  // rhs[1][s.p    ] = lambda*rhs[1][s.p];
  // rhs[1][s.v + 0] = 1.0/rho*rhs[1][s.v+0];
  // rhs[1][s.v + 1] = 1.0/rho*rhs[1][s.v+1];
}
