#ifndef Dimensionless_Discharge_INCLUDED
#define Dimensionless_Discharge_INCLUDED

namespace dimensionlessDischarge {
  class DimensionlessDischarge {
    private:
      double alpha;

      double **temp_z;

      void _initialize_arrays(void);

    public:
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
