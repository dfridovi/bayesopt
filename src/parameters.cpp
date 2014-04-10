/*
-------------------------------------------------------------------------
   This file is part of BayesOpt, an efficient C++ library for 
   Bayesian optimization.

   Copyright (C) 2011-2013 Ruben Martinez-Cantin <rmcantin@unizar.es>
 
   BayesOpt is free software: you can redistribute it and/or modify it 
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   BayesOpt is distributed in the hope that it will be useful, but 
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with BayesOpt.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------
*/
#include <iostream>
#include "parameters.h"



learning_type str2learn(const char* name)
{
  if      (!strcmp(name,"L_FIXED"))     return L_FIXED;
  else if (!strcmp(name,"L_EMPIRICAL")) return L_EMPIRICAL;
  else if (!strcmp(name,"L_DISCRETE"))  return L_DISCRETE;
  else if (!strcmp(name,"L_MCMC"))      return L_MCMC;
  else return L_ERROR;
}




const char* learn2str(learning_type name)
{
  switch(name)
    {
    case L_FIXED:     return "L_FIXED"; 
    case L_EMPIRICAL: return "L_EMPIRICAL"; 
    case L_DISCRETE:  return "L_DISCRETE"; 
    case L_MCMC:      return "L_MCMC"; 
    case L_ERROR:
    default: return "ERROR!";
    }
}


score_type str2score(const char* name)
{
  if      (!strcmp(name,  "SC_MTL"))   return SC_MTL;
  else if (!strcmp(name,  "SC_ML"))    return SC_ML;
  else if (!strcmp(name,  "SC_MAP"))   return SC_MAP;
  else if (!strcmp(name,  "SC_LOOCV")) return SC_LOOCV;
  else return SC_ERROR;
}




const char* score2str(score_type name)
{
  switch(name)
    {
    case SC_MTL:   return "SC_MTL"; 
    case SC_ML:    return "SC_ML"; 
    case SC_MAP:   return "SC_MAP"; 
    case SC_LOOCV: return "SC_LOOCV"; 
    case SC_ERROR:
    default: return "ERROR!";
    }
}


/*
char DEF_LOG_FILE[128] = "bayesopt.log";
char DEF_SUR_NAME[128] = "sGaussianProcess";
char DEF_KERNEL_NAME[128] = "kMaternISO3";
char DEF_MEAN_NAME[128] = "mOne";
char DEF_CRITERIA_NAME[128] = "cEI";

static const kernel_parameters DEFAULT_KERNEL = {
  DEF_KERNEL_NAME, {KERNEL_THETA}, {KERNEL_SIGMA}, 1 
};

static const mean_parameters DEFAULT_MEAN = {
  DEF_MEAN_NAME, {MEAN_MU}, {MEAN_SIGMA}, 1
};


static const bopt_params DEFAULT_PARAMS = {
  DEFAULT_ITERATIONS, 
  MAX_INNER_EVALUATIONS, 
  DEFAULT_SAMPLES, 
  0, 
  1,

  DEFAULT_VERBOSE, 
  &DEF_LOG_FILE[0],
  
  &DEF_SUR_NAME[0],
  DEFAULT_SIGMA, 
  DEFAULT_NOISE,
  PRIOR_ALPHA, 
  PRIOR_BETA, 
  L_MAP, 
  0.0,
  
  DEFAULT_KERNEL, 
  DEFAULT_MEAN,
  
  DEF_CRITERIA_NAME, 
  {1.0}, 
  1
};
*/

bopt_params initialize_parameters_to_default(void)
{
  kernel_parameters kernel;
  kernel.name = new char[128];
  strcpy(kernel.name,"kMaternISO3");

  kernel.hp_mean[0] = KERNEL_THETA;
  kernel.hp_std[0] = KERNEL_SIGMA;
  kernel.n_hp = 1;
  
  mean_parameters mean;
  mean.name = new char[128];
  strcpy(mean.name,"mConst");

  mean.coef_mean[0] = MEAN_MU;
  mean.coef_std[0] = MEAN_SIGMA;
  mean.n_coef = 1;
  

  bopt_params params;
  params.n_iterations =   DEFAULT_ITERATIONS;
  params.n_inner_iterations = MAX_INNER_EVALUATIONS;
  params.n_init_samples = DEFAULT_SAMPLES;
  params.n_iter_relearn = 0;

  params.init_method = 1;
  params.use_random_seed = 1;

  params.verbose_level = DEFAULT_VERBOSE;
  params.log_filename = new char[128];
  strcpy(params.log_filename,"bayesopt.log");

  params.load_save_flag = 0;
  params.load_filename = new char[128];
  strcpy(params.log_filename,"bayesopt.dat");
  params.save_filename = new char[128];
  strcpy(params.log_filename,"bayesopt.dat");

  params.surr_name = new char[128];
  strcpy(params.surr_name,"sGaussianProcess");

  params.sigma_s = DEFAULT_SIGMA;
  params.noise = DEFAULT_NOISE;
  params.alpha = PRIOR_ALPHA;
  params.beta = PRIOR_BETA;
  params.l_all = 0;
  params.l_type = L_EMPIRICAL;
  params.sc_type = SC_MAP;
  params.epsilon = 0.0;
  
  params.crit_name = new char[128];
  strcpy(params.crit_name,"cEI");
  params.n_crit_params = 0;

  params.kernel = kernel;
  params.mean = mean;
  return params;
}
