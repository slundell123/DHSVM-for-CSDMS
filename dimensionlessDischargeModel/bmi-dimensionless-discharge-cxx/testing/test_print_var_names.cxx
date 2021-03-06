#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <dimensionless_discharge.hxx>
#include <bmi.hxx>
#include <bmi_dimensionless_discharge.hxx>


void print_var_names (BmiDimensionlessDischarge model);

int
main (void)
{
  int i;
  const int n_steps = 10;
  BmiDimensionlessDischarge model;
  std::string name;

  model.Initialize("");

  name = model.GetComponentName();
  std::cout << name << std::endl;

  print_var_names (model);

  model.Finalize();

  return EXIT_SUCCESS;
}

void
print_var_names (BmiDimensionlessDischarge model)
{
  int number_of_names;
  std::vector<std::string> names;

  number_of_names = model.GetInputItemCount();
  fprintf (stdout, "Number of input names: %d\n", number_of_names);
  names = model.GetInputVarNames();
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i].c_str());
  fprintf (stdout, "\n");

  number_of_names = model.GetOutputItemCount();
  fprintf (stdout, "Number of output names: %d\n", number_of_names);
  names = model.GetOutputVarNames();
  for (int i=0; i<number_of_names; i++)
    fprintf (stdout, "%s\n", names[i].c_str());
  fprintf (stdout, "\n");
}
