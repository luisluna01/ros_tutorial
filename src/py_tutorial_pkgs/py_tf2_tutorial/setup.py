import os
from glob import glob

from setuptools import find_packages, setup

package_name = 'py_tf2_tutorial'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Luis Luna',
    maintainer_email='luisluna12@utexas.edu',
    description='Python pkg for learning tf2 in ROS2',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'static_turtle_tf2_broadcaster = py_tf2_tutorial.static_turtle_tf2_broadcaster:main',
            'turtle_tf2_broadcaster = py_tf2_tutorial.turtle_tf2_broadcaster:main'
        ],
    },
)
