LOCALWORKDIR=~/Documents/research/dhsvm-csdms

# Build container
cd ${LOCALWORKDIR} && docker build --tag=hydromet ${LOCALWORKDIR}

# Start container, run python script
set -f && docker run --rm -it \
  --security-opt seccomp=unconfined \
  -t hydromet:latest \
  conda run -n hydrometenv \
  python
