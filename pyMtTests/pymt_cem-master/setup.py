#! /usr/bin/env python
import os
import sys
import numpy as np

import versioneer
from setuptools import find_packages, setup

from distutils.extension import Extension
from model_metadata.utils import get_cmdclass, get_entry_points


common_flags = {
    "include_dirs": [np.get_include(), os.path.join(sys.prefix, "include")],
    "library_dirs": [],
    "define_macros": [],
    "undef_macros": [],
    "extra_compile_args": [],
    "language": "c",
}

libraries = []

ext_modules = [
    Extension(
        "pymt_cem.lib.cem",
        ["pymt_cem/lib/cem.pyx"],
        libraries=libraries + ["bmi_cem"],
        **common_flags,
    ),
    Extension(
        "pymt_cem.lib.waves",
        ["pymt_cem/lib/waves.pyx"],
        libraries=libraries + ["bmi_waves"],
        **common_flags,
    ),
]

packages = find_packages()
pymt_components = [
    ("Cem=pymt_cem.bmi:Cem", "meta/Cem"),
    ("Waves=pymt_cem.bmi:Waves", "meta/Waves"),
]

cmdclass = get_cmdclass(pymt_components, cmdclass=versioneer.get_cmdclass())

setup(
    name="pymt_cem",
    author="Eric Hutton",
    description="PyMT plugin for cem",
    version=versioneer.get_version(),
    setup_requires=["cython"],
    ext_modules=ext_modules,
    packages=packages,
    cmdclass=cmdclass,
    entry_points=get_entry_points(pymt_components),
)
