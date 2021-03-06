"""Run the Dimensionless Discharge model in pymt."""
import numpy as np
from pymt.models import DimensionlessDischargeBMI

help(DimensionlessDischargeBMI)

# variables to pass in:

flux = [3, 2,8]
d50 = [.23, .5, .9]
streamIds = [1,2,3]
soilDensity = 1330


# Instantiate the component and get its name.
m = DimensionlessDischargeBMI()
print(m.name)

# Call setup, then initialize the model.
#args = m.setup(flux, d50, streamIds, soilDensity)
m.initialize(flux, d50, streamIds, soilDensity)
print("all Variable names: ",m.output_var_names )
print("before update:")
for i in range(len(m.output_var_names)-1):
    print("Value of: ", m.output_var_names[i+1])
    print(m.get_value(m.output_var_names[i+1]))

print("updating...")

m.update()

for i in range(len(m.output_var_names)-1):
    print("Value of: ", m.output_var_names[i+1])
    print(m.get_value(m.output_var_names[i+1]))

# Finalize the model.
m.finalize()
print('Done.')