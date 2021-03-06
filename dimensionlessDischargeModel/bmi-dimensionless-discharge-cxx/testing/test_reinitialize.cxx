#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <dimensionless_discharge.hxx>
#include <bmi.hxx>
#include <bmi_dimensionless_discharge.hxx>


int
main (void)
{
  int i;
  const int n_steps = 3;
  BmiDimensionlessDischarge model;
  std::string name;

  for (int i=0; i<n_steps; i++) {
    fprintf (stdout, "Reinitialize %d\n", i+1);

    model.Initialize("");

    name = model.GetComponentName();
    std::cout << name << std::endl;

    model.Finalize();
  }

  return EXIT_SUCCESS;
}
