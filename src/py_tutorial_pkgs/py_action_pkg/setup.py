from setuptools import find_packages, setup

package_name = 'py_action_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Luis Luna',
    maintainer_email='luisluna12@utexas.edu',
    description='Example pkg for creating and action server and client',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'fibonacci_action_server = py_action_pkg.fibonacci_action_server:main',
            'fibonacci_action_client = py_action_pkg.fibonacci_action_client:main'
        ],
    },
)
