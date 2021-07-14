# Dimensionless-Discharge-for-CSDMS
This is a model based on Tang et al. 2019 paper "Developing and Testing Physically Based Triggering Thresholds for Runoff-Generated Debris Flows". It implements the formula from this article to calculate the dimensionless discharge value for segments in given streams. This value is then compared to a threshold value to determine whether or not a debris flow would be expected in any given segment.
## Setup
- Install Docker: https://docs.docker.com/get-docker/
- cd into bin directory Dimensionless-Discharge-for-CSDMS/dimensionlessDischargeModel/bin/
- Currently, you will need to change the python file you would like to run by going into the docker file and changing the file name on lines 60 and 62 (should be the same file name on both lines). Dockerfile can be found at: Dimensionless-Discharge-for-CSDMS/dimensionlessDischargeModel/Dockerfile 
- Update line 32 in dimensionlessDischargeModel/bmi-dimensionless-discharge-cxx/dimensionless-discharge/dimensionless_discharge.hxx with the number of stream segments you are using
- Any data you would like to use should be added into a data folder in the dimensionlessDischargeModel directory.
- Run: ```source babelizer.sh [path to dimensionlessDischargeModel directory]```
