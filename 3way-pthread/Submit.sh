#!/bin/bash
#SBATCH --job-name=hw4-pthread
#SBATCH --output=hw4-pthread.out
#SBATCH --error=hw4-pthread.err
#SBATCH --time=00:10:00
#SBATCH --nodes=1                   #Always 1 for pthreads doesn't use mulitple processors /cores
#SBATCH --ntasks=1                  # 1 process
#SBATCH --cpus-per-task=4           #parameter to change
#SBATCH --mem-per-cpu=1G            #parameter to change
#SBATCH --constraint=mole

make
time ./pt1 4                             #number at end to match cpus-per-task