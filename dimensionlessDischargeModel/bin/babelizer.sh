LOCALWORKDIR=$1
PYTHONSCRIPT=$2

# Build container
cd ${LOCALWORKDIR} && \
  sudo docker build --tag=babelizer ${LOCALWORKDIR}

sudo docker container prune --filter "until=12h" --force # Start container, run python script
#sudo docker image prune

set -f && sudo docker run --rm -it \
  -v $PYTHONSCRIPT:/opt/test/pythonScript.py \
  --security-opt seccomp=unconfined \
  -t babelizer:latest \
  #conda run -n wrap \
  #python /opt/test/pythonScript.py
  /bin/bash #conda run -n wrap \
