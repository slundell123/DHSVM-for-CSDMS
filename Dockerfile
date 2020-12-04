# Use miniconda as a parent image
FROM continuumio/miniconda3

WORKDIR /bmi

# Create and activate conda environment
COPY environment.yml /bmi
RUN conda --version \
  && conda env create -f /bmi/environment.yml \
  && source activate wrap
#RUN conda env create -f /bmi/environment.yml
ENV PATH /opt/conda/envs/wrap/bin:$PATH


#ENV PATH /opt/conda/envs/wrap/bin:$PATH
#RUN source activate wrap





# Install example package
COPY bmi-example-cxx /bmi/bmi-example-cxx
WORKDIR /bmi/bmi-example-cxx/build
RUN /bin/bash -c "cmake .. -DCMAKE_INSTALL_PREFIX=$CONDA_PREFIX"
RUN /bin/bash -c "make"
RUN /bin/bash -c "make install"
RUN /bin/bash -c "babelize init babel_heatcxx.toml ."
WORKDIR /bmi/bmi-example-cxx/build/pymt_heatcxx
RUN conda install -c conda-forge --file=requirements-build.txt --file=requirements-testing.txt --file=requirements-library.txt --file=requirements.txt
RUN make install
WORKDIR /bmi/bmi-example-cxx/build