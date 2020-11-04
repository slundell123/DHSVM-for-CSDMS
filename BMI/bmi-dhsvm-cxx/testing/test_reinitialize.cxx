#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <dhsvm.hxx>
#include <bmi.hxx>
#include <bmi_dhsvm.hxx>


int
main (void)
{
  int i;
  const int n_steps = 3;
  BmiDhsvm model;
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
