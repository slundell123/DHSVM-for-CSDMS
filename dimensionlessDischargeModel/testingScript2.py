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
start_date = "2017-12-01 00:00:00"
date_time_obj = datetime.strptime(start_date, "%Y-%m-%d %H:%M:%S")
dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

timeUpdateAmount = timedelta(hours=1)


df = (pd.read_csv("20210204.matilija.dhsvm.discharge.flux.csv")
      [lambda x: x['datetime'] == dateTime])

numElements = len(df)

f = open("config.txt", "w")
f.write(str(numElements))
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

#while not df.empty:
for i in range(5):    
    flux = df['outflow.flux.mpts']

    m.set_value("dimensionless_flux", flux)


    print("updating...")

    m.update()
    f = open("output.txt", "a")
    f.write(dateTime + "\n " + str(m.var[m.output_var_names[1]].data) +"\n")
    f.close()

    date_time_obj += timedelta(hours=1)
    dateTime = str(date_time_obj.date()) +"T"+str(date_time_obj.time())+"Z"

    df = (pd.read_csv("20210204.matilija.dhsvm.discharge.flux.csv")
      [lambda x: x['datetime'] == dateTime])

# make datafame out of output csv file
outputDf = (pd.read_csv("output.csv"))
print(outputDf)

for segment in outputDf['segmentId'].unique():
    dates = list(outputDf.loc[outputDf['segmentId'] == segment]['data'])
    ddValues = list(outputDf.loc[outputDf['segmentId'] == segment]['dimensionlessDischarge'])
    plt.plot(dates, ddValues)

plt.ylabel('Dimensionless Dischange')

plt.xlabel('Data')
plt.savefig('outputPlot.pdf') 


# Finalize the model.
m.finalize()
print('Done.')