#!/bin/bash
#SBATCH --job-name=cacheblock
#SBATCH --output=resultcblock10.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 00:30:00
./cacheblock
