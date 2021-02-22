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
print("before update:")
print("Value of: ", m.output_var_names[2])
print(m.get_value(m.output_var_names[2]))
print("Value of: ", var_name)
print(m.get_value(var_name))
print("updating...")

m.update()
print("Value of: ", var_name)
print(m.get_value(var_name))

# Finalize the model.
m.finalize()
print('Done.')