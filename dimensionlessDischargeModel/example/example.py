"""Run the Dimensionless Discharge model in pymt."""
import numpy as np
from pymt.models import DimensionlessDischargeBMI
import pandas as pd
from datetime import datetime, timedelta
import random
import matplotlib.pyplot as plt

# seed random number generation
# This example uses random numbers in place of data
random.seed(2021)

# number of stream segments 
# NOTE: This is currently hardcoded to be 138. To change, update the value of 
# tempThresholdVals in bmi-dimensionless-dischnage-cxx/dimensionless-dischnage.hxx
numStreamSegments = 138

# Threshold C value
C = 12.0

# Threshold N value
N = 0.85

# time step (in hours)
alpha = 1

# make list of slopes for each segment in the stream 
# (needs to be string to append to config file)
slopeList = ""
for slope in range(numStreamSegments):
    slopeList += str(slope)+","
# remove extra end comma from slope list:
slopeList = slopeList[0:-1]

# set up the config file
configText = str(alpha) +'\n' \
    + str(numStreamSegments) + "\n" \
    + str(C) + "\n" \
    + str(N) + "\n" \
    + slopeList + "\n"
configFile = open("configExample.txt", "w")
configFile.write(configText)
configFile.close()

# set value of d50 (in meters)
# requires one d50 value for each stream segment
d50 = []
for i in range(numStreamSegments):
    d50.append(0.015) # meters 

# set soil density(in kg/m^3)
# must be one value for entire area.
soilDensity = 1330.0 # kg/m^3


# Instantiate the model and get its name.
model = DimensionlessDischargeBMI()
print(model.name)

# to read more about a pymt setup, read here: https://pymt.readthedocs.io/en/latest/usage.html#model-setups
# Call setup, then initialize the model with a config file.
# Config file must be provided for this model.
config_file, config_dir = model.setup(".")
config_file="configExample.txt"
model.initialize(config_file, dir=config_dir)

# List the model's exchange items.
print('Number of input vars:', len(model.input_var_names))
for var in model.input_var_names:
    print(' - {}'.format(var))
print('Number of output vars:', len(model.output_var_names))
for var in model.output_var_names:
    print(' - {}'.format(var))

# variable in model before initialization
print("before set:")
for i in range(len(model.output_var_names)-1):
    print("Value of: ", model.output_var_names[i+1])
    print(model.var[model.output_var_names[i+1]].data)

# setting values that the model does not set from the config
model.set_value("soil_density", [soilDensity])
model.set_value("dimensionless_d50_vector", d50)

print("after set:")
for i in range(len(model.output_var_names)-1):
    print("Value of: ", model.output_var_names[i+1])
    print(model.var[model.output_var_names[i+1]].data)

# Get variable info.
var_name = model.output_var_names[0]
print('Variable {}'.format(var_name))
print(' - variable type:', model.var_type(var_name))
print(' - units:', model.var_units(var_name))
print(' - itemsize:', model.var_itemsize(var_name))
print(' - nbytes:', model.var_nbytes(var_name))
print(' - location:', model.var_location(var_name))

# Get grid info for variable.
grid_id = model.var_grid(var_name)
print(' - grid id:', grid_id)
print(' - grid type:', model.grid_type(grid_id))
print(' - rank:', model.grid_ndim(grid_id))
# print(' - size:', model.grid_node_count(grid_id))
print(' - shape:', model.grid_shape(grid_id))

# Get time information from the model.
print('Start time:', model.start_time)
print('End time:', model.end_time)
print('Current time:', model.time)
print('Time step:', model.time_step)
print('Time units:', model.time_units)

# Advance the model by one time step.
# The update function calculates the dimensionless-dischnage value 
# for each stream segment and produces a boolean values of 1 if 
# this value is over the threshold for that segment of a 0 if it 
# is below. These values are stored in output.csv.
model.update()
print('Update: current time:', model.time)

print("variables after update:")
for i in range(len(model.output_var_names)-1):
    print("Value of: ", model.output_var_names[i+1])
    print(model.var[model.output_var_names[i+1]].data)


# Finalize the model.
model.finalize()
print('Done.')