#!/bin/bash
#SBATCH --job-name=hw4-mpi
#SBATCH --output=hw4-mpi.out
#SBATCH --error=hw4-mpi.err
#SBATCH --time=00:10:00
#SBATCH --nodes=1           #param to change
#SBATCH --ntasks=4          #param to change
#SBATCH --cpus-per-task=1   #Keep at 1
#SBATCH --mem-per-cpu=1G    #param to change
#SBATCH --constraint=moles

make
time srun ./pt2