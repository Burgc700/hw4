#!/bin/bash
#SBATCH --job-name=hw4-pthread
#SBATCH --output=hw4-pthread.out
#SBATCH --error=hw4-pthread.err
#SBATCH --time=00:10:00
#SBATCH --nodes=1                   #parameter to change
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4           #parameter to change
#SBATCH --mem=1G                    #parameter to change
#SBATCH --constraint=mile

make
./pt1 4                             #number at end to match cpus-per-task