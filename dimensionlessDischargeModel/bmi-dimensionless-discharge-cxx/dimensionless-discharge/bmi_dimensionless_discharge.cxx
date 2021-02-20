#include <stdio.h>

#include <string>
#include <cstring>
#include <cstdlib>
#include<vector>

#include "dimensionless_discharge.hxx"
#include <bmi.hxx>
#include "bmi_dimensionless_discharge.hxx"


void BmiDimensionlessDischarge::
Initialize (std::string config_file)
{
  if (config_file.compare("") != 0 )
    this->_model = dimensionlessDischarge::DimensionlessDischarge(config_file); 
}


void BmiDimensionlessDischarge::
Update()
{
  this->_model.advance_in_time();
}


void BmiDimensionlessDischarge::
UpdateUntil(double t)
{
  double time;
  double dt;

  time = this->GetCurrentTime();
  dt = this->GetTimeStep();

  {
    double n_steps = (t - time) / dt;
    double frac;

    for (int n=0; n<int(n_steps); n++)
      this->Update();

    frac = n_steps - int(n_steps);
    this->_model.dt = frac * dt;
    this->_model.advance_in_time();
    this->_model.dt = dt;
  }
}


void BmiDimensionlessDischarge::
Finalize()
{
  this->_model.~DimensionlessDischarge();
}


int BmiDimensionlessDischarge::
GetVarGrid(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return 0;
  else if (name.compare("dimensionless_discharge") == 0)
    return 1;
  else if (name.compare("dimensionless_flux") == 0)
    return 2;
  else
    return -1;
}


std::string BmiDimensionlessDischarge::
GetVarType(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "double";
  else if (name.compare("dimensionless_discharge") == 0)
    return "double";
    else if (name.compare("dimensionless_flux") == 0)
    return "double";
  else
    return "";
}


int BmiDimensionlessDischarge::
GetVarItemsize(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return sizeof(double);
  else if (name.compare("dimensionless_discharge") == 0)
    return sizeof(double);
  else if (name.compare("dimensionless_flux") == 0)
    return sizeof(double);
  else
    return 0;
}


std::string BmiDimensionlessDischarge::
GetVarUnits(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "meters";
  else if (name.compare("dimensionless_discharge") == 0)
    return "meters"; //Should be done, but it won't let me user none as a data type... 
  else if (name.compare("dimensionless_flux") == 0)
    return "meters";
  else
    return "";
}


int BmiDimensionlessDischarge::
GetVarNbytes(std::string name)
{
  int itemsize;
  int gridsize;

  itemsize = this->GetVarItemsize(name);
  gridsize = this->GetGridSize(this->GetVarGrid(name));
  
  return itemsize * gridsize;
}


std::string BmiDimensionlessDischarge::
GetVarLocation(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "node";
  else if (name.compare("dimensionless_discharge") == 0)
    return "node";
    else if (name.compare("dimensionless_flux") == 0)
    return "node";
  else
    return "";
}


void BmiDimensionlessDischarge::
GetGridShape(const int grid, int *shape)
{
  if (grid == 0) {
    shape[0] = this->_model.shape[0];
    shape[1] = this->_model.shape[1];
  }
}


void BmiDimensionlessDischarge::
GetGridSpacing (const int grid, double * spacing)
{
  if (grid == 0) {
    spacing[0] = this->_model.spacing[0];
    spacing[1] = this->_model.spacing[1];
  }
}


void BmiDimensionlessDischarge::
GetGridOrigin (const int grid, double *origin)
{
  if (grid == 0) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
  if (grid == 1) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
  if (grid == 2) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
}


int BmiDimensionlessDischarge::
GetGridRank(const int grid)
{
  if (grid == 0)
    return 2;
  if (grid == 1)
    return 2;
  if (grid == 2)
    return 2;
  else
    return -1;
}


int BmiDimensionlessDischarge::
GetGridSize(const int grid)
{
  if (grid == 0)
    return this->_model.shape[0] * this->_model.shape[1];
  if (grid == 1)
    return this->_model.dimensionlessDischargeShape[0];
  if (grid == 2)
    return this->_model.fluxShape[0];
  else
    return -1;
}


std::string BmiDimensionlessDischarge::
GetGridType(const int grid)
{
  if (grid == 0)
    return "uniform_rectilinear";
  if (grid == 1)
    return "uniform_rectilinear";
  if (grid == 2)
    return "uniform_rectilinear";
  else
    return "";
}


void BmiDimensionlessDischarge::
GetGridX(const int grid, double *x)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridY(const int grid, double *y)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridZ(const int grid, double *z)
{
  throw NotImplemented();
}


int BmiDimensionlessDischarge::
GetGridNodeCount(const int grid)
{
  if (grid == 0)
    return this->_model.shape[0] * this->_model.shape[1];
  else if (grid == 1)
    return this->_model.dimensionlessDischargeShape[0];
  else if (grid == 2)
    return this->_model.fluxShape[0];
  else
    return -1;
}


int BmiDimensionlessDischarge::
GetGridEdgeCount(const int grid)
{
  throw NotImplemented();
}


int BmiDimensionlessDischarge::
GetGridFaceCount(const int grid)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridEdgeNodes(const int grid, int *edge_nodes)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridFaceEdges(const int grid, int *face_edges)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridFaceNodes(const int grid, int *face_nodes)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetGridNodesPerFace(const int grid, int *nodes_per_face)
{
  throw NotImplemented();
}


void BmiDimensionlessDischarge::
GetValue (std::string name, void *dest)
{
  void * src = NULL;
  int nbytes = 0;

  src = this->GetValuePtr(name);
  nbytes = this->GetVarNbytes(name);

  memcpy (dest, src, nbytes);
}


void *BmiDimensionlessDischarge::
GetValuePtr (std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return (void*)this->_model.z[0];
  else if (name.compare("dimensionless_discharge") == 0)
    return this->_model.dimensionlessDischarge;
  else if (name.compare("dimensionless_flux") == 0)
    return this->_model.dimensionless_flux;
  else
    return NULL;
}


void BmiDimensionlessDischarge::
GetValueAtIndices (std::string name, void *dest, int *inds, int len)
{
  void * src = NULL;

  src = this->GetValuePtr(name);

  if (src) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    itemsize = this->GetVarItemsize(name);

    for (i=0, ptr=(char *)dest; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy(ptr, (char *)src + offset, itemsize);
    }
  }
}


void BmiDimensionlessDischarge::
SetValue (std::string name, void *src)
{
  void * dest = NULL;

  dest = this->GetValuePtr(name);

  if (dest) {
    int nbytes = 0;
    nbytes = this->GetVarNbytes(name);
    memcpy(dest, src, nbytes);
  }
}


void BmiDimensionlessDischarge::
SetValueAtIndices (std::string name, int * inds, int len, void *src)
{
  void * dest = NULL;

  dest = this->GetValuePtr(name);

  if (dest) {
    int i;
    int itemsize = 0;
    int offset;
    char *ptr;

    itemsize = this->GetVarItemsize(name);

    for (i=0, ptr=(char *)src; i<len; i++, ptr+=itemsize) {
      offset = inds[i] * itemsize;
      memcpy((char *)dest + offset, ptr, itemsize);
    }
  }
}


std::string BmiDimensionlessDischarge::
GetComponentName()
{
  return "The Dimensionless Discharge Equation";
}


int BmiDimensionlessDischarge::
GetInputItemCount()
{
  return this->input_var_name_count;
}


int BmiDimensionlessDischarge::
GetOutputItemCount()
{
  return this->output_var_name_count;
}


std::vector<std::string> BmiDimensionlessDischarge::
GetInputVarNames()
{
  std::vector<std::string> names;

  for (int i=0; i<this->input_var_name_count; i++)
    names.push_back(this->input_var_names[i]);

  return names;
}


std::vector<std::string> BmiDimensionlessDischarge::
GetOutputVarNames()
{
  std::vector<std::string> names;

  for (int i=0; i<this->input_var_name_count; i++)
    names.push_back(this->output_var_names[i]);

  return names;
}


double BmiDimensionlessDischarge::
GetStartTime () {
  return 0.;
}


double BmiDimensionlessDischarge::
GetEndTime () {
  return this->_model.t_end;
}


double BmiDimensionlessDischarge::
GetCurrentTime () {
  return this->_model.time;
}


std::string BmiDimensionlessDischarge::
GetTimeUnits() {
  return "s";
}


double BmiDimensionlessDischarge::
GetTimeStep () {
  return this->_model.dt;
}
