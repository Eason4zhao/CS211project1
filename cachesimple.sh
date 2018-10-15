#!/bin/bash
#SBATCH --job-name=cachesimple
#SBATCH --output=resultcsimple.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 00:30:00
./cachesimple
