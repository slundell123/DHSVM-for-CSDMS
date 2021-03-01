#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dimensionless_discharge.hxx"


#define OK (1)


int
dimensionless_discharge_solve_2d (double ** z, int shape[2], double spacing[2], double alpha,
    double dt, double ** out)
{
  
  {
    int i, j;
    const int top_row = shape[0] - 1;
    const int top_col = shape[1] - 1;
    const double dx2 = spacing[1] * spacing[1];
    const double dy2 = spacing[0] * spacing[0];
    const double c = alpha * dt / (dx2 + dy2);

    for (i=1; i<top_row; i++)
      for (j=1; j<top_col; j++) {
        out[i][j] = c * (dx2 * (z[i][j - 1] + z[i][j + 1]) +
                         dy2 * (z[i - 1][j] + z[i + 1][j]) -
                         2. * (dx2 + dy2) * z[i][j]);
      }

    for (j=0; j<shape[1]; j++) {
        out[0][j] = 0.;
        out[top_row][j] = 0.;
    }
    for (i=0; i<shape[0]; i++) {
        out[i][0] = 0.;
        out[i][top_col] = 0.;
    }

    for (i=1; i<top_row; i++)
      for (j=1; j<top_col; j++)
        out[i][j] += z[i][j];
  }
 
  return OK;
  
}

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
  for(int j = 0; j < this->vectorShapeDimensionlessDischarge; j++){
    
    this->dimensionlessDischarge[0][j] = this->dimensionless_flux[0][j]/sqrt(((this->soilDensity-this->waterDensityConst)/this->waterDensityConst)*this->gravityConst*this->d50);
  }

  memcpy (this->temp_dimensionlessDischarge[0], this->dimensionlessDischarge[0], sizeof (double) * dimensionlessDischargeShape);
}


dimensionlessDischarge::DimensionlessDischarge::
DimensionlessDischarge(std::string config_file)
{
  // dimensionless Discharge variable initialization with config
  // TODO: change file to read into these values instead of heat ones
  this->gravityConst = 9.8; //(m/s^2)
  this->waterDensityConst = 997.; //(kg/m^2)
  this->soilDensity = 1.33; //(g/cm^2)
  this->d50 = 5.8;
  this->d50VectorType = false;
  //this->dimensionlessDischarge = 1000.0;

  FILE * fp;
  double alpha = 1.;
  double t_end = 0.;
  int n_x = 0;
  int n_y = 0;

  fp = fopen (config_file.c_str (), "r");

  fscanf (fp, "%lf, %lf, %d, %d", &alpha, &t_end, &n_x, &n_y);

  fclose (fp);

  this->alpha = alpha;
  this->dt = 1. / (4. * alpha);
  this->t_end = t_end;
  this->shape[0] = n_y;
  this->shape[1] = n_x;
  this->spacing[0] = 1.;
  this->spacing[1] = 1.;
  this->origin[0] = 0.;
  this->origin[1] = 0.;

  this->dimensionlessDischargeShape = 10;
  this->fluxShape = 10;
  this->vectorShapeDimensionlessDischarge = 10;

  this->_initialize_arrays();
}

dimensionlessDischarge::DimensionlessDischarge::DimensionlessDischarge(int vectorShape){
  // dimensionless Discharge variable initialization
  this->gravityConst = 9.8; //(m/s^2)
  this->waterDensityConst = 997.; //(kg/m^3)
  this->soilDensity = 1330; //(kg/m^3)
  this->d50 = 5.8; //(m?)
  this->dimensionlessDischargeShape = vectorShape; //(int)
  this->fluxShape = vectorShape; //(int)
  this->vectorShapeDimensionlessDischarge = vectorShape; //(int)
  this->d50VectorType = false;
  
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
  
  this->streamSegmentIDVector = new int*[dd_y];
  this->streamSegmentIDVector[0] = new int[dd_x * dd_y];

  for (i = 0; i < ddLen; i++) {
    this->streamSegmentIDVector[0][i] = 0;
  }


 

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
  this->soilDensity = 1330; //(kg/m^3)
  this->d50 = 5.8; //(m?)
  this->dimensionlessDischargeShape = 10;
  this->fluxShape = 10;
  this->vectorShapeDimensionlessDischarge = 10;
  this->d50VectorType = false;
  
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
