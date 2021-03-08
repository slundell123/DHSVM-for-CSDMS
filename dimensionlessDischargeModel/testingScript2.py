"""Run the Dimensionless Discharge model in pymt."""
import numpy as np
from pymt.models import DimensionlessDischargeBMI

#help(DimensionlessDischargeBMI)

# variables to pass in:

flux = [3.0, 2.0,8.0,9.0,10.0, 11.0 , 10.1, 12.12, 12.12, 23.2, 23.23, 23.23, 23.32, 23.23]
d50 = [.23, .5, .9]
streamIds = [1,2,3]
soilDensity = [1330.0]


# Instantiate the component and get its name.
m = DimensionlessDischargeBMI()
print(m.name)

# Call setup, then initialize the model.
#args = m.setup("config.txt")
m.initialize()

m.set_value("soil_density", soilDensity)
m.set_value("dimensionless_stream_segment_id_vector", streamIds)
m.set_value("dimensionless_d50_vector", d50)
m.set_value("dimensionless_flux", flux)


print("all Variable names: ",m.output_var_names )
print("before update:")
for i in range(len(m.output_var_names)-1):
    print("Value of: ", m.output_var_names[i+1])
    print(m.var[m.output_var_names[i+1]].data)

print("updating...")

m.update()

for i in range(len(m.output_var_names)-1):
    print("Value of: ", m.output_var_names[i+1])
    print(m.get_value(m.output_var_names[i+1]))

# Finalize the model.
m.finalize()
print('Done.')