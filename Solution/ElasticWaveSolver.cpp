// This file was generated by the ExaHyPE toolkit.
// It will NOT be regenerated or overwritten.
// Please adapt it to your own needs.
// 
// ========================
//   www.exahype.eu
// ========================

#include "ElasticWaveSolver.h"

#include "ElasticWaveSolver_Variables.h"

#include "kernels/KernelUtils.h"
#include "peano/utils/Loop.h"

tarch::logging::Log Linear::ElasticWaveSolver::_log( "Linear::ElasticWaveSolver" );


void Linear::ElasticWaveSolver::init(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants) {
  initPointSourceLocations(cmdlineargs,constants);	
}

void Linear::ElasticWaveSolver::adjustPointSolution(const double* const x,const double t,const double dt,double* const Q) {
  VariableShortcuts s;
  if (tarch::la::equals(t,0.0)) {
    //Initial Condiation Task 1
    // double r2 = (x[0])*(x[0]) + (x[1]-5.0)*(x[1]-5.0);
    // Q[s.v + 0]     = exp(-r2);
    // Q[s.v + 1]     = exp(-r2);
    //Initial Condiation Task 2
    Q[s.v + 0]     = 0.0;
    Q[s.v + 1]     = 0.0;    
    Q[s.sigma + 0] = 0.0;
    Q[s.sigma + 1] = 0.0;
    Q[s.sigma + 2] = 0.0;
    Q[s.rho]       = 2.7;
    Q[s.cp]        = 6.0;
    Q[s.cs]        = 3.464;
  }
}

void Linear::ElasticWaveSolver::boundaryValues(const double* const x,const double t,const double dt,const int faceIndex,const int direction,const double* const fluxIn,const double* const stateIn,const double* const gradStateIn,double* const fluxOut,double* const stateOut) {
  
  int normal_velocity, tangent_velocity;
  int normal_traction, tangent_traction;
  VariableShortcuts s;

  //abc
  stateOut[0] = 0;
  stateOut[1] = 0;
  stateOut[2] = 0;
  stateOut[3] = 0;
  stateOut[4] = 0;
  stateOut[5] = stateIn[5];
  stateOut[6] = stateIn[6];
  stateOut[7] = stateIn[7];

  //freeSurface Task 2
  if(faceIndex == 2){
    stateOut[0] = stateOut[0];
    stateOut[1] = stateOut[1];
    stateOut[2] = -stateIn[2];
    stateOut[3] = -stateIn[3];
    stateOut[4] = -stateIn[4];
  }

  fluxOut[0] = 0.0;
  fluxOut[1] = 0.0;
  fluxOut[2] = 0.0;
  fluxOut[3] = 0.0;
  fluxOut[4] = 0.0;
}

exahype::solvers::Solver::RefinementControl Linear::ElasticWaveSolver::refinementCriterion(const double* const luh,const tarch::la::Vector<DIMENSIONS,double>& cellCentre,const tarch::la::Vector<DIMENSIONS,double>& cellSize,double t,const int level) {
  
  return exahype::solvers::Solver::RefinementControl::Keep;
  
}

//*****************************************************************************
//******************************** PDE ****************************************
// To use other PDE terms, specify them in the specification file, delete this 
// file and its header and rerun the toolkit
//*****************************************************************************


void Linear::ElasticWaveSolver::eigenvalues(const double* const Q,const int direction,double* const lambda) {
  // Eigenvalues Task 1
  VariableShortcuts s;

  lambda[0] =  Q[s.cp];
  lambda[1] =  Q[s.cs];
  lambda[2] =  0.0;
  lambda[3] = -Q[s.cs];
  lambda[4] = -Q[s.cp];
}



void Linear::ElasticWaveSolver::flux(const double* const Q,double** const F) {

  // Flux vector Task 1
  
  VariableShortcuts s;

  const double rho  = Q[s.rho];
  const double cp   = Q[s.cp];   
  const double cs   = Q[s.cs];

  const double mu  = rho*cs*cs;
  const double lambda = rho*cp*cp-2.0*mu;  

  double sxx = Q[s.sigma + 0];
  double syy = Q[s.sigma + 1];
  double sxy = Q[s.sigma + 2];

  double u = Q[s.v + 0];
  double v = Q[s.v + 1];
    
  F[0][0] = -1.0/rho*sxx;
  F[0][1] = -1.0/rho*sxy;
  F[0][2] = -(2*mu+lambda)*u;
  F[0][3] = -lambda * u;
  F[0][4] = -mu*v;
  
  F[1][0] = -1.0/rho*sxy;
  F[1][1] = -1.0/rho*syy;
  F[1][2] = -lambda * v;
  F[1][3] = -(2*mu+lambda)*v;
  F[1][4] = -mu*u;  
}


void  Linear::ElasticWaveSolver::initPointSourceLocations(const std::vector<std::string>& cmdlineargs,const exahype::parser::ParserView& constants){
  // PointSource location Task 2
  pointSourceLocation[0][0]=0.0;
  pointSourceLocation[0][1]=0.693;
}

void  Linear::ElasticWaveSolver::pointSource(const double* const Q,const double* const x,const double t,const double dt, double* const forceVector, int n) {

  VariableShortcuts s;

  constexpr double t0 = 0.1;
  constexpr double M0 = 1000.0;
    
  double f = M0*t/(t0*t0)*std::exp(-t/t0);

  forceVector[0] = 0.0;
  forceVector[1] = 0.0;
  forceVector[2] = 0.0;
  forceVector[3] = 0.0;
  // Force Vector Task 2
  //forceVector[4] = 0.0;
  forceVector[4] = -f;
}
