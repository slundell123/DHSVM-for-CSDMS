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
start_date = "2018-03-01 00:00:00"
date_time_obj = datetime.strptime(start_date, "%Y-%m-%d %H:%M:%S")
dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

timeUpdateAmount = timedelta(hours=1)


df = (pd.read_csv("20210204.matilija.dhsvm.discharge.flux.csv")
      [lambda x: x['datetime'] == dateTime])

numElements = len(df)
C = 2 
theta = 4
N = 5
configText = str(numElements) + ", " + str(C) + ", " + str(theta) + ", " + str(N) + "\n"
f = open("config.txt", "w")
f.write(configText)
f.close()

d50 = []
streamIds = []
for i in range(numElements):
    d50.append(random.random())
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

for i in range(552):
#for i in range(20):    
    flux = df['outflow.flux.mpts']
    flow = df['outflow.m3pts']
    averageFlow.append(sum(list(flow)))

    m.set_value("dimensionless_flux", flux)
    m.update()
    f = open("output.txt", "a")
    f.write(dateTime + "\n " + str(m.var[m.output_var_names[1]].data) +"\n")
    f.close()

    date_time_obj += timedelta(hours=4)
    dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

    df = (pd.read_csv("20210204.matilija.dhsvm.discharge.flux.csv")
      [lambda x: x['datetime'] == dateTime])

'''
# make datafame out of output csv file
outputDf = (pd.read_csv("output.csv"))

times = list(outputDf['time'].unique())
averageDD = [0]*len(times)

for segment in outputDf['segmentId'].unique():
    segmentDf = outputDf.loc[outputDf['segmentId'] == segment]
    for i in range(len(times)):
        averageDD[i] += int(segmentDf.loc[segmentDf['time'] == times[i]]['dimensionlessDischarge'])

for i in range(len(averageDD)):
     averageDD[i] = averageDD[i]/len(outputDf['segmentId'].unique())
     averageFlow[i] = averageFlow[i]/len(outputDf['segmentId'].unique())

plt.plot(times, averageDD, label='Dimensionless Dischange')

plt.plot(times, averageFlow, label='Average Flow')

plt.ylabel('Dimensionless Dischange')

plt.xlabel('Time')
plt.savefig('outputPlot.pdf')
plt.legend()
'''

# Finalize the model.
m.finalize()
print('Done.')