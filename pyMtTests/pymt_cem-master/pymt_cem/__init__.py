#! /usr/bin/env python

from .bmi import Cem, Waves

__all__ = ["Cem", "Waves"]

from ._version import get_versions

__version__ = get_versions()["version"]
del get_versions

from ._version import get_versions

__version__ = get_versions()["version"]
del get_versions
