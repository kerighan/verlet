from setuptools import setup, find_packages, Extension
from glob import glob
import pybind11
import os


ext_modules = [
    Extension(
        'verlet',
        sorted(glob("src/*.cpp")),
        language='c++',
        include_dirs=[
            pybind11.get_include(),
            pybind11.get_include(True),],
        extra_compile_args=["-Ofast"])
]


setup(
    name="verlet",
    version="0.0.0",
    packages=find_packages("src"),
    package_dir={"": "src"},
    install_requires=["pybind11"],
    ext_modules=ext_modules
)
