from distutils.core import setup
import setuptools

setup(
    name='Mario',
    version='0.9.1',
    package_dir={'': '.'},
    packages=setuptools.find_packages('.'),
    author='Zubair Abid',
    author_email='zubairabid1999@gmail.com',
    test_suite='pytest',
    tests_require=['pytest'],
)
