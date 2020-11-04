#ifndef DHSVM_INCLUDED
#define DHSVM_INCLUDED

namespace dhsvm {
  class Dhsvm {
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

      Dhsvm();
      Dhsvm(std::string config_file);
      ~Dhsvm();
      void advance_in_time ();
  };
};

#endif
