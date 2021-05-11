#ifndef Dimensionless_Discharge_INCLUDED
#define Dimensionless_Discharge_INCLUDED

namespace dimensionlessDischarge {
  class DimensionlessDischarge {
    private:
      double alpha;

      double **temp_z;
      double **temp_dimensionlessDischarge;
      double **temp_dimensionless_flux;

      // Constant Values for dimensionless discharge
      double gravityConst;
      double waterDensityConst;


      void _initialize_arrays(void);

    public:
      // Input Values for dimensionless discharge
      double** soilDensity;
      double** dimensionless_flux;
      double** dimensionlessDischarge;
      double** d50Vector;
      double** streamSegmentIDVector;
      double* streamSegmentSlope;
      double* dimensionlessDischargeThreshold;
      int vectorShapeDimensionlessDischarge; // shape of all vectors 
      int dimensionlessDischargeShape;
      int fluxShape;
      double tempThresholdVals [138];



      int shape[2];
      double spacing[2];
      double origin[2];
      double time;
      double t_end;
      double dt;
      double **z;


      DimensionlessDischarge();
      DimensionlessDischarge(std::string config_file);
      ~DimensionlessDischarge();
      void advance_in_time ();
  };
};

#endif
