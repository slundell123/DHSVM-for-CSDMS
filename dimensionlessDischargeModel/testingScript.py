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