#ifndef BMI_DIMENSIONLESS_DISCHARGE_H_INCLUDED
#define BMI_DIMENSIONLESS_DISCHARGE_H_INCLUDED

#include <string>
#include <iostream>

#include <bmi.hxx>
#include "dimensionless_discharge.hxx"


class NotImplemented : public std::logic_error {
  public:
  NotImplemented() : std::logic_error("Not Implemented") { };
};


class BmiDimensionlessDischarge : public bmi::Bmi {
  public:
    BmiDimensionlessDischarge() {
      this->input_var_names[0] = "plate_surface__temperature";
      this->output_var_names[0] = "plate_surface__temperature";
      this->input_var_names[1] = "dimensionless_discharge";
      this->output_var_names[1] = "dimensionless_discharge";
      this->input_var_names[2] = "dimensionless_flux";
      this->output_var_names[2] = "dimensionless_flux";
      this->input_var_names[3] = "dimensionless_d50_vector";
      this->output_var_names[3] = "dimensionless_d50_vector";
      this->input_var_names[4] = "dimensionless_stream_segment_id_vector";
      this->output_var_names[4] = "dimensionless_stream_segment_id_vector";
      this->input_var_names[5] = "soil_density";
      this->output_var_names[5] = "soil_density";
      
    };

    void Initialize(std::string config_file);
    void Update();
    void UpdateUntil(double time);
    void Finalize();

    std::string GetComponentName();
    int GetInputItemCount();
    int GetOutputItemCount();
    std::vector<std::string> GetInputVarNames();
    std::vector<std::string> GetOutputVarNames();

    int GetVarGrid(std::string name);
    std::string GetVarType(std::string name);
    int GetVarItemsize(std::string name);
    std::string GetVarUnits(std::string name);
    int GetVarNbytes(std::string name);
    std::string GetVarLocation(std::string name);

    double GetCurrentTime();
    double GetStartTime();
    double GetEndTime();
    std::string GetTimeUnits();
    double GetTimeStep();

    void GetValue(std::string name, void *dest);
    void *GetValuePtr(std::string name);
    void GetValueAtIndices(std::string name, void *dest, int *inds, int count);

    void SetValue(std::string name, void *src);
    void SetValueAtIndices(std::string name, int *inds, int len, void *src);

    int GetGridRank(const int grid);
    int GetGridSize(const int grid);
    std::string GetGridType(const int grid);

    void GetGridShape(const int grid, int *shape);
    void GetGridSpacing(const int grid, double *spacing);
    void GetGridOrigin(const int grid, double *origin);

    void GetGridX(const int grid, double *x);
    void GetGridY(const int grid, double *y);
    void GetGridZ(const int grid, double *z);

    int GetGridNodeCount(const int grid);
    int GetGridEdgeCount(const int grid);
    int GetGridFaceCount(const int grid);

    void GetGridEdgeNodes(const int grid, int *edge_nodes);
    void GetGridFaceEdges(const int grid, int *face_edges);
    void GetGridFaceNodes(const int grid, int *face_nodes);
    void GetGridNodesPerFace(const int grid, int *nodes_per_face);

  private:
    dimensionlessDischarge::DimensionlessDischarge _model;
    static const int input_var_name_count = 5;
    static const int output_var_name_count = 5;

    std::string input_var_names[5];
    std::string output_var_names[5];
};

#endif
