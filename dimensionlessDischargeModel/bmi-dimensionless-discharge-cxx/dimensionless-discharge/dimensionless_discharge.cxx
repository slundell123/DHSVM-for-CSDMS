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

double dimensionlessDischarge::DimensionlessDischarge::GetDimensionlessDischarge(){
  return this->dimensionlessDischarge;
}

double dimensionlessDischarge::DimensionlessDischarge::CalculateDimensionlessDischarge(){
  this->dimensionlessDischarge = this->flux/sqrt(((this->soilDensity-this->waterDensityConst)/this->waterDensityConst)*this->gravityConst*this->d50);
  return this->dimensionlessDischarge;
}

void dimensionlessDischarge::DimensionlessDischarge::
advance_in_time ()
{
  const int n_elements = this->shape[0] * this->shape[1];
  dimensionless_discharge_solve_2d (this->z, this->shape, this->spacing, this->alpha, this->dt,
      this->temp_z);
  this->time += this->dt;
  //this->dimensionlessDischarge = CalculateDimensionlessDischarge();
  this->dimensionlessDischarge += 3.0;
  memcpy (this->z[0], this->temp_z[0], sizeof (double) * n_elements);
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
  this->dimensionlessDischarge = 1000.0;
  this->flux = 0.8;

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

  /* Allocate memory */
  this->temp_z = new double*[n_y];
  this->z = new double*[n_y];

  this->z[0] = new double[n_x * n_y];
  this->temp_z[0] = new double[n_x*n_y];
  for (i=1; i<n_y; i++) {
    this->z[i] = this->z[i-1] + n_x;
    this->temp_z[i] = this->temp_z[i-1] + n_x;
  }

  for (i = 0; i < len; i++)
    this->z[0][i] = rand ()*1./RAND_MAX * top_x*top_x*.5 - top_x*top_x*.25;
  for (i = 0; i < n_y; i++) {
    this->z[i][0] = 0.;
    this->z[i][n_x-1] = 0.;
  }
  for (i = 0; i < n_x; i++) {
    this->z[0][i] = 0.;
    this->z[n_y-1][i] = top_x*top_x*.25 - (i-top_x*.5) * (i-top_x*.5);
  }

  memcpy (this->temp_z[0], this->z[0], sizeof (double)*n_x*n_y);
}


dimensionlessDischarge::DimensionlessDischarge::
DimensionlessDischarge()
{
  // dimensionless Discharge variable initialization
  this->gravityConst = 9.8; //(m/s^2)
  this->waterDensityConst = 997.; //(kg/m^2)
  this->soilDensity = 1.33; //(g/cm^2)
  this->d50 = 5.8;
  this->dimensionlessDischarge = 0.0;
  this->flux = 0.0;

  // heat values
  this->alpha = 1.;
  this->t_end = 10.;
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
