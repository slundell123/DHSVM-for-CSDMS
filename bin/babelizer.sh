LOCALWORKDIR=~/Documents/research/dhsvm-csdms/DHSVM-for-CSDMS

# Build container
cd ${LOCALWORKDIR} && docker build --tag=babelizer ${LOCALWORKDIR}

# Start container, run python script
set -f && docker run --rm -it \
  --security-opt seccomp=unconfined \
  -t babelizer:latest \
  /bin/bash #conda run -n wrap \
  #test -f $CONDA_PREFIX/include/bmi_heat.h
