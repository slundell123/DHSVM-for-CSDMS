FROM condaforge/miniforge3

WORKDIR /opt
COPY environment.yml ./

# conda environments are wonky in Docker.
RUN conda env create --file environment.yml
RUN echo "source activate wrap" >> ~/.bashrc
ENV CONDA_PREFIX=/opt/conda/envs/wrap
ENV PATH ${CONDA_PREFIX}/bin:$PATH

# Uncomment below line to pull example cxx from github (and comment out copy)
# RUN git clone https://github.com/csdms/bmi-example-cxx
# Use below copy command on downloaded example code
COPY bmi-example-cxx /opt/bmi-example-cxx
WORKDIR /opt/bmi-example-cxx/_build
RUN cmake .. -DCMAKE_INSTALL_PREFIX=${CONDA_PREFIX} && make install

WORKDIR /opt
RUN git clone https://github.com/csdms/babelizer
RUN babelize init babelizer/tests/test_cxx/babel.toml .

WORKDIR /opt/pymt_heat
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
RUN bmi-test pymt_heat:HeatBMI --config-file=../babelizer/tests/test_cxx/config.txt --root-dir=. -vvv

RUN conda install -c conda-forge pymt

# These are from the C example, but should also work for the C++ example.
WORKDIR /opt/babelizer/docs/source/examples
RUN cp info.yaml run.yaml parameters.yaml heat.txt /opt/pymt_heat/meta/HeatBMI

WORKDIR /opt/test
COPY pymt_heatcxx_ex.py ./
RUN python pymt_heatcxx_ex.py