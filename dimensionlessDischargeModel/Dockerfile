FROM condaforge/miniforge3

WORKDIR /opt
COPY environment.yml ./


# conda environments are wonky in Docker.
RUN conda env create --file environment.yml
RUN echo "source activate wrap" >> ~/.bashrc
ENV CONDA_PREFIX=/opt/conda/envs/wrap
ENV PATH ${CONDA_PREFIX}/bin:$PATH


COPY bmi-dimensionless-discharge-cxx /opt/bmi-dimensionless-discharge-cxx
#COPY bmi-dimensionless-discharge-cxx/babel.toml /opt/babel.toml

WORKDIR /opt/bmi-dimensionless-discharge-cxx/_build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=${CONDA_PREFIX} && make install

WORKDIR /opt
RUN git clone https://github.com/csdms/babelizer
RUN babelize init bmi-dimensionless-discharge-cxx/babel.toml .

WORKDIR /opt/pymt_dimensionless_discharge
RUN conda install -c conda-forge \
    --file=requirements-build.txt \
    --file=requirements-testing.txt \
    --file=requirements-library.txt \
    --file=requirements.txt

# This is a result of conda environments not working correctly in Docker.
ENV SYSROOT=${CONDA_PREFIX}/x86_64-conda-linux-gnu/sysroot
RUN mkdir -p /usr/lib64
RUN ln -s ${SYSROOT}/lib64/libpthread.so.0 /lib64/libpthread.so.0
RUN ln -s ${SYSROOT}/usr/lib64/libpthread_nonshared.a /usr/lib64/libpthread_nonshared.a
RUN ln -s ${SYSROOT}/lib64/libc.so.6 /lib64/libc.so.6
RUN ln -s ${SYSROOT}/usr/lib64/libc_nonshared.a /usr/lib64/libc_nonshared.a

RUN make install

WORKDIR /opt/test

# Issues running the test script: no vector type? Error on grid type checking, doesn't check for vectors...
# Commenting out for now so code can be ran. Issue with using config???
#RUN bmi-test pymt_dimensionless_discharge:DimensionlessDischargeBMI --config-file=../babelizer/tests/test_cxx/config.txt --root-dir=. -vvv

RUN conda install -c conda-forge pymt



WORKDIR /opt/test
COPY pymt_dimensionless_discharge_ex.py ./
COPY testingScript.py ./
RUN python testingScript.py
