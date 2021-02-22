"""Run the Dimensionless Discharge model in pymt."""
import numpy as np
from pymt.models import DimensionlessDischargeBMI

#help(DimensionlessDischargeBMI)


# Instantiate the component and get its name.
m = DimensionlessDischargeBMI()
print(m.name)

# Call setup, then initialize the model.
args = m.setup('.')
m.initialize(*args)
print("variables: ", m.output_var_names)
var_name = m.output_var_names[1]
print('Variable: ',var_name)
print(' - variable type:', m.var_type(var_name))
print(' - units:', m.var_units(var_name))
print(' - itemsize:', m.var_itemsize(var_name))
print(' - nbytes:', m.var_nbytes(var_name))
print(' - location:', m.var_location(var_name))
print()
print('Start time:', m.start_time)
print('End time:', m.end_time)
print("before update:")
print("Value of: ", var_name)
print(m.get_value(var_name))
print("Value of: ", var_name)
print(m.get_value(var_name))
print("updating...")

m.update()
print("Value of: ", var_name)
print(m.get_value(var_name))
var_name = m.output_var_names[0]

print("Value of: ", var_name)
print(m.get_value(var_name))


# Finalize the model.
m.finalize()
print('Done.')