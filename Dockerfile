# Use miniconda as a parent image
FROM continuumio/miniconda3

WORKDIR /bmi

# Create and activate conda environment
COPY environment.yml /bmi
RUN conda env create -f /bmi/environment.yml
ENV PATH /opt/conda/envs/bmienv/bin:$PATH
RUN /bin/bash -c "source activate wrap"

# Install example package
COPY bmi-example-cxx /bmi
WORKDIR /bmi/bmi-example-cxx/build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX
RUN make
RUN make install
RUN test -f $CONDA_PREFIX/include/bmi_heat.h
