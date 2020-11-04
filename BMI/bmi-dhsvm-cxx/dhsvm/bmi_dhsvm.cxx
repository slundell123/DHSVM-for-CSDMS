#include <stdio.h>

#include <string>
#include <cstring>
#include <cstdlib>
#include<vector>

#include "dhsvm.hxx"
#include <bmi.hxx>
#include "bmi_dhsvm.hxx"


void BmiDhsvm::
Initialize (std::string config_file)
{
  if (config_file.compare("") != 0 )
    this->_model = dhsvm::Dhsvm(config_file);
}


void BmiDhsvm::
Update()
{
  this->_model.advance_in_time();
}


void BmiDhsvm::
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


void BmiDhsvm::
Finalize()
{
  this->_model.~Dhsvm();
}


int BmiDhsvm::
GetVarGrid(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return 0;
  else
    return -1;
}


std::string BmiDhsvm::
GetVarType(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "double";
  else
    return "";
}


int BmiDhsvm::
GetVarItemsize(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return sizeof(double);
  else
    return 0;
}


std::string BmiDhsvm::
GetVarUnits(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "meters";
  else
    return "";
}


int BmiDhsvm::
GetVarNbytes(std::string name)
{
  int itemsize;
  int gridsize;

  itemsize = this->GetVarItemsize(name);
  gridsize = this->GetGridSize(this->GetVarGrid(name));
  
  return itemsize * gridsize;
}


std::string BmiDhsvm::
GetVarLocation(std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return "node";
  else
    return "";
}


void BmiDhsvm::
GetGridShape(const int grid, int *shape)
{
  if (grid == 0) {
    shape[0] = this->_model.shape[0];
    shape[1] = this->_model.shape[1];
  }
}


void BmiDhsvm::
GetGridSpacing (const int grid, double * spacing)
{
  if (grid == 0) {
    spacing[0] = this->_model.spacing[0];
    spacing[1] = this->_model.spacing[1];
  }
}


void BmiDhsvm::
GetGridOrigin (const int grid, double *origin)
{
  if (grid == 0) {
    origin[0] = this->_model.origin[0];
    origin[1] = this->_model.origin[1];
  }
}


int BmiDhsvm::
GetGridRank(const int grid)
{
  if (grid == 0)
    return 2;
  else
    return -1;
}


int BmiDhsvm::
GetGridSize(const int grid)
{
  if (grid == 0)
    return this->_model.shape[0] * this->_model.shape[1];
  else
    return -1;
}


std::string BmiDhsvm::
GetGridType(const int grid)
{
  if (grid == 0)
    return "uniform_rectilinear";
  else
    return "";
}


void BmiDhsvm::
GetGridX(const int grid, double *x)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridY(const int grid, double *y)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridZ(const int grid, double *z)
{
  throw NotImplemented();
}


int BmiDhsvm::
GetGridNodeCount(const int grid)
{
  if (grid == 0)
    return this->_model.shape[0] * this->_model.shape[1];
  else
    return -1;
}


int BmiDhsvm::
GetGridEdgeCount(const int grid)
{
  throw NotImplemented();
}


int BmiDhsvm::
GetGridFaceCount(const int grid)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridEdgeNodes(const int grid, int *edge_nodes)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridFaceEdges(const int grid, int *face_edges)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridFaceNodes(const int grid, int *face_nodes)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetGridNodesPerFace(const int grid, int *nodes_per_face)
{
  throw NotImplemented();
}


void BmiDhsvm::
GetValue (std::string name, void *dest)
{
  void * src = NULL;
  int nbytes = 0;

  src = this->GetValuePtr(name);
  nbytes = this->GetVarNbytes(name);

  memcpy (dest, src, nbytes);
}


void *BmiDhsvm::
GetValuePtr (std::string name)
{
  if (name.compare("plate_surface__temperature") == 0)
    return (void*)this->_model.z[0];
  else
    return NULL;
}


void BmiDhsvm::
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


void BmiDhsvm::
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


void BmiDhsvm::
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


std::string BmiDhsvm::
GetComponentName()
{
  return "The 2D Dhsvm Equation";
}


int BmiDhsvm::
GetInputItemCount()
{
  return this->input_var_name_count;
}


int BmiDhsvm::
GetOutputItemCount()
{
  return this->output_var_name_count;
}


std::vector<std::string> BmiDhsvm::
GetInputVarNames()
{
  std::vector<std::string> names;

  for (int i=0; i<this->input_var_name_count; i++)
    names.push_back(this->input_var_names[i]);

  return names;
}


std::vector<std::string> BmiDhsvm::
GetOutputVarNames()
{
  std::vector<std::string> names;

  for (int i=0; i<this->input_var_name_count; i++)
    names.push_back(this->output_var_names[i]);

  return names;
}


double BmiDhsvm::
GetStartTime () {
  return 0.;
}


double BmiDhsvm::
GetEndTime () {
  return this->_model.t_end;
}


double BmiDhsvm::
GetCurrentTime () {
  return this->_model.time;
}


std::string BmiDhsvm::
GetTimeUnits() {
  return "s";
}


double BmiDhsvm::
GetTimeStep () {
  return this->_model.dt;
}
