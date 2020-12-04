# Use miniconda as a parent image
FROM continuumio/miniconda3

WORKDIR /bmi

# Create and activate conda environment
COPY environment.yml /bmi
COPY babel_heatcxx.toml /bmi

RUN conda env create -f /bmi/environment.yml
ENV PATH /opt/conda/envs/wrap/bin:$PATH
#RUN /bin/bash -c "source activate wrap"

# Install example package
COPY bmi-example-cxx /bmi/bmi-example-cxx
WORKDIR /bmi/bmi-example-cxx/build

RUN conda run -n wrap cmake .. -DCMAKE_INSTALL_PREFIX='/opt/conda/envs/wrap'
RUN conda run -n wrap make
RUN conda run -n wrap make install

RUN conda run -n wrap /bin/bash -c "babelize init /bmi/babel_heatcxx.toml ."
WORKDIR /bmi/bmi-example-cxx/build/pymt_heatcxx
RUN conda install -n wrap -c conda-forge --file=requirements-build.txt --file=requirements-testing.txt --file=requirements-library.txt --file=requirements.txt
RUN conda run -n wrap make install
WORKDIR /bmi/bmi-example-cxx/build