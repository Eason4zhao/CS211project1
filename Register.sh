#!/bin/bash
#SBATCH --job-name=Register
#SBATCH --output=result.txt
#SBATCH -N 1
#SBATCH -n 32
#SBATCH -t 00:10:00
./Register 64
