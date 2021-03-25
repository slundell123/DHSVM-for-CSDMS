#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "dimensionless_discharge.hxx"


#define OK (1)


int
calculateDimensionlessDischarge (double ** dimensionlessDischarge, int shape, double ** out, double ** flux, double d50, double soilD, double waterD, double g)
{
  
  {
    int i, j;
    const int top_row = shape;
    const int top_col = 1;

    for (i=1; i<top_row; i++)
      for (j=1; j<top_col; j++) {
        out[i][j] = flux[i][j];///sqrt(((soilD-waterD)/waterD)*g*d50);

      }
  }
 
  return OK;
  
}

void dimensionlessDischarge::DimensionlessDischarge::
advance_in_time ()
{
  this->time += this->dt;
  std::string fileInput = "";
  for(int j = 0; j < this->vectorShapeDimensionlessDischarge; j++){
    this->dimensionlessDischarge[0][j] = this->dimensionless_flux[0][j]/sqrt(((this->soilDensity[0][0]-this->waterDensityConst)/this->waterDensityConst)*this->gravityConst*this->d50Vector[0][j]);
    fileInput += std::to_string(this->dimensionlessDischarge[0][j]) + ",";
    std::string fileInput = std::to_string(j+1) + "," +std::to_string(this->time) + "," +std::to_string(this->dimensionlessDischarge[0][j]) + "\n";
  
    std::ofstream outputFile;
    outputFile.open ("output.csv", std::ios_base::app);
    outputFile << fileInput;
    outputFile.close();
  }

  memcpy (this->temp_dimensionlessDischarge[0], this->dimensionlessDischarge[0], sizeof (double) * dimensionlessDischargeShape);
}


dimensionlessDischarge::DimensionlessDischarge::
DimensionlessDischarge(std::string config_file)
{
  // dimensionless Discharge variable initialization with config
  // TODO: change file to read into these values instead of heat ones
  this->gravityConst = 9.8; //(m/s^2)
  this->waterDensityConst = 1000.0;
  FILE * fp;
  double alpha = 1.;
  double t_end = 0.;
  int n_x = 0;
  int n_y = 0;
  int size = 0;
  fp = fopen (config_file.c_str (), "r");
  fscanf (fp, "%d", &size);
  fclose (fp);

  this->vectorShapeDimensionlessDischarge = size;
  this->dimensionlessDischargeShape = size;
  this->fluxShape = size;

  // heat values
  this->alpha = 1.;
  this->t_end = 11.;
  this->time = 0.;
  this->shape[0] = 10;
  this->shape[1] = 20;
  this->spacing[0] = 1.;
  this->spacing[1] = 1.;
  this->origin[0] = 0.;
  this->origin[1] = 0.;
  this->dt = 1. / (4. * this->alpha);

  std::ofstream outputFile;
  outputFile.open("output.csv", std::ofstream::out | std::ofstream::trunc);
  outputFile << "segmentId,data,dimensionlessDischarge,\n";
  outputFile.close();

  this->_initialize_arrays();
}


void dimensionlessDischarge::DimensionlessDischarge::
_initialize_arrays(void)
{
  
  int i;
  const int n_y = this->shape[0];
  const int n_x = this->shape[1];
  const int len = n_x * n_y;
  double top_x = n_x - 1;

  const int dd_y = 1;
  const int dd_x = this->vectorShapeDimensionlessDischarge;
  const int ddLen = dd_x * dd_y;
  double ddTop_x = dd_x - 1;

  const int df_y = 1;
  const int df_x = this->vectorShapeDimensionlessDischarge;
  const int dfLen = dd_x * dd_y;
  double dfTop_x = dd_x - 1;



  ///Allocate memory 
  this->temp_z = new double*[n_y];
  this->z = new double*[n_y];

  this->temp_dimensionlessDischarge = new double*[dd_y];
  this->dimensionlessDischarge = new double*[dd_y];
  this->temp_dimensionless_flux = new double*[df_y];
  this->dimensionless_flux = new double*[df_y];


  this->z[0] = new double[n_x * n_y];
  this->temp_z[0] = new double[n_x*n_y];

  this->temp_dimensionlessDischarge[0] = new double[dd_x * dd_y];
  this->dimensionlessDischarge[0] = new double[dd_x * dd_y];
  this->temp_dimensionless_flux[0] = new double[df_x * df_y];
  this->dimensionless_flux[0] = new double[df_x * df_y];

  

  
  for (i=1; i<n_y; i++) {
    this->z[i] = this->z[i-1] + n_x;
    this->temp_z[i] = this->temp_z[i-1] + n_x; 
  }
  for (i=1; i<dd_y; i++) {
    this->dimensionlessDischarge[i] = this->dimensionlessDischarge[i-1] + dd_x;
    this->temp_dimensionlessDischarge[i] = this->temp_dimensionlessDischarge[i-1] + dd_x;
  }
  for (i=1; i<df_y; i++) {
    this->dimensionless_flux[i] = this->dimensionless_flux[i-1] + df_x;
    this->temp_dimensionless_flux[i] = this->temp_dimensionless_flux[i-1] + df_x;
  }

  for (i = 0; i < len; i++)
    this->z[0][i] = 1.1;
  // randomly set value in flux between 0 and 1 to try out the dimensionless discharge update function
  for (i = 0; i < ddLen; i++)
    this->dimensionless_flux[0][i] = std::rand()/RAND_MAX;
  for (i = 0; i < dfLen; i++)
    this->dimensionlessDischarge[0][i] = 1;


  // D50 vector 
  this->d50Vector = new double*[dd_y];
  this->d50Vector[0] = new double[dd_x * dd_y];

  for (i = 0; i < ddLen; i++)
    this->d50Vector[0][i] = 0;
  
  // Stream Segment ID vector 
  
  this->streamSegmentIDVector = new double*[dd_y];
  this->streamSegmentIDVector[0] = new double[dd_x * dd_y];

  for (i = 0; i < ddLen; i++) {
    this->streamSegmentIDVector[0][i] = i+1;
  }

  // soil density value 
  
  this->soilDensity = new double*[1];
  this->soilDensity[0] = new double[1];

  
  this->soilDensity[0][0] = 1388;
  


 

  memcpy (this->temp_z[0], this->z[0], sizeof (double)*n_x*n_y);
  memcpy (this->temp_dimensionlessDischarge[0], this->dimensionlessDischarge[0], sizeof (double)*dd_x*dd_y);
  memcpy (this->temp_dimensionless_flux[0], this->dimensionless_flux[0], sizeof (double)*df_x*df_y);
}


dimensionlessDischarge::DimensionlessDischarge::
DimensionlessDischarge()
{
  // dimensionless Discharge variable initialization
  this->gravityConst = 9.8; //(m/s^2)
  this->waterDensityConst = 997.; //(kg/m^3)
  this->dimensionlessDischargeShape = 2;
  this->fluxShape = 2;
  this->vectorShapeDimensionlessDischarge = 2;
  
  // heat values
  this->alpha = 1.;
  this->t_end = 11.;
  this->time = 0.;
  this->shape[0] = 10;
  this->shape[1] = 20;
  this->spacing[0] = 1.;
  this->spacing[1] = 1.;
  this->origin[0] = 0.;
  this->origin[1] = 0.;
  this->dt = 1. / (4. * this->alpha);

  this->_initialize_arrays();
  
}


dimensionlessDischarge::DimensionlessDischarge::
~DimensionlessDischarge()
{
  this->time = 0.;
}
