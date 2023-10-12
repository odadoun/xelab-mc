# XeLab Monte Carlo Simulation

GEANT4-based physics simulation of the XeLab experiment at LPNHE (Paris, France).

## Dependencies

- CMake 3.26.3
- ROOT 6.26/10 (only if you want to open `*.root` files generated during simulation)
- GEANT4 10.7.4 with the following options enabled at the configuration step of the installation process:
  - GEANT4_BUILD_MULTITHREADED
  - GEANT4_INSTALL_DATA
  - GEANT4_USE_GDML
  - GEANT4_USE_QT
  - GEANT4_USE_RAYTRACER_X11

## How to build and run?

To build the project, do the following:

```
cd xelab-mc
mkdir build && cd build
cmake ..
make -j16
```

To run the simulation program, type `./xelab_mc`.
