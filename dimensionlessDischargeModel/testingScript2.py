"""Run the Dimensionless Discharge model in pymt."""
import numpy as np
from pymt.models import DimensionlessDischargeBMI
import pandas as pd
from datetime import datetime, timedelta
import random
import matplotlib.pyplot as plt

# make file for output
f = open("output.txt", "w")
f.write("")
f.close()

# seed random number generation
random.seed(2021)

#help(DimensionlessDischargeBMI)

# variables to pass in:
start_date = "2018-01-02 00:00:00"
end_date = "2018-02-01 00:00:00"
date_time_obj = datetime.strptime(start_date, "%Y-%m-%d %H:%M:%S")
date_time_obj_end = datetime.strptime(end_date, "%Y-%m-%d %H:%M:%S")
dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

# original data
#df = (pd.read_csv("20210204.matilija.dhsvm.discharge.flux.csv"))

# 1/2 hr Done
#df = (pd.read_csv("20210413.matilija.dhsvm.discharge.flux.0-05h.csv"))

# 1 hr Done
df = (pd.read_csv("20210413.matilija.dhsvm.discharge.flux.1h.csv"))

# 2 hr Done
#df = (pd.read_csv("20210413.matilija.dhsvm.discharge.flux.2h.csv"))

# 6 hr Done
#df = (pd.read_csv("20210413.matilija.dhsvm.discharge.flux.6h.csv"))

# 24 hr - DOne
#df = (pd.read_csv("20210413.matilija.dhsvm.discharge.flux.24h.csv"))
print(df['datetime'])

header_list = ['segment',
               'order',
               'slope',
               'length.m',
               'class',
               'dest.channel',
               'save',
               'outlet']
mapNetworkDf = (pd.read_csv("stream.network.csv", "\t", names=header_list))
print("Num segments: ",len(df.loc[df['datetime'] == dateTime]))

numElements = 138
# UL Thresholds
C = 12.0
N = 0.85

# time step in hours
alpha = 1

# make list of slopess
slopeList = ""
for slope in mapNetworkDf['slope']:
    slopeList += str(slope)+","
# remove extra end comma:
slopeList = slopeList[0:-1]
print("Slopes:", slopeList)
# set up config file
configText = str(alpha) + '\n' + str(numElements) + "\n" + str(C) + "\n" + str(N) + "\n" + slopeList + "\n"
f = open("config.txt", "w")
f.write(configText)
f.close()

d50 = []
streamIds = []
for i in range(numElements):
    #d50.append(random.random())
    d50.append(0.015) # meters 
    #streamIds.append(i)

#flux = [3.0, 2.0,8.0]
#d50 = [.23, .5, .9]
#streamIds = [1,2,3]
soilDensity = [1330.0]


# Instantiate the component and get its name.
m = DimensionlessDischargeBMI()
print(m.name)

# https://pymt.readthedocs.io/en/latest/usage.html#model-setups
# Call setup, then initialize the model.
config_file, config_dir = m.setup(".")
print(config_dir)
print(config_file)
config_file="config.txt"
m.initialize(config_file, dir=config_dir)

print("before set:")
for i in range(len(m.output_var_names)-1):
    print("Value of: ", m.output_var_names[i+1])
    print(m.var[m.output_var_names[i+1]].data)


m.set_value("soil_density", soilDensity)
#m.set_value("dimensionless_stream_segment_id_vector", streamIds)
m.set_value("dimensionless_d50_vector", d50)

averageFlow = []
#while not df.empty:

#for i in range(552):
#for i in range(1):  

while date_time_obj <= date_time_obj_end:
    dfDate =  df.loc[df['datetime'] == dateTime]
    flux = dfDate['outflow.flux.mps']
    flow = dfDate['outflow.m3pts']
    averageFlow.append(sum(list(flow)))

    m.set_value("dimensionless_flux", flux)
    m.update()
    f = open("output.txt", "a")
    f.write(dateTime + "\n " + str(m.var[m.output_var_names[1]].data) +"\n")
    f.close()

    date_time_obj += timedelta(hours=alpha)
    dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

# Finalize the model.
m.finalize()
print('Done.')