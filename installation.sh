#!/bin/bash

STARPATH=`pwd`
echo "Creating ${STARPATH}/build directory."
mkdir build

echo 'Build files will be stored at the following directory:'
cd build/
pwd
cmake ..
make -j

echo 'Executable program will be stored at the following directory:'
echo "${STARPATH}"

cd ..
mv ${STARPATH}/build/exe/starware ${STARPATH}

echo 'Installation is finished.'
echo 'Thank you for installing STARWARE program.'
echo 'If you have any problem during the installation or using the program, please contact via mb0316@nuclear.korea.ac.kr.'

#echo 'Finished compiling.'

#echo 'Executable file will be created at the following directory:'
#cd ..
#echo "${STARPATH}"
#echo 'Start building executable.'
#GCC="g++ `root-config --cflags --glibs` -lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lSpectrum -lMinuit -lGui -o STARWARE src/starware.cpp src/*.cc build/*.cxx"
#$GCC
#echo 'Finished building executable.'

#echo 'Adding a command for starting the program.'
#echo "alias star='${STARPATH}'" >> ~/.bash_profile
#echo "alias STARWARE='${STARPATH}/STARWARE'" >> ~/.bash_profile
#echo 'Command STARWARE & star has been added.'
#source ~/.bash_profile
#echo 'To start STARWARE, please type STARWARE.'
#echo 'To move to STARWARE directory, please type star.'

#echo 'Start builing a soft link for STARWARE.'
#ln -s ${STARPATH}/STARWARE ~/Desktop
#echo 'The soft link has been created at Desktop.'

#source ~/.bash_profile

