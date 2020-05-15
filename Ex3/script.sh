#!/bin/bash

cc ping_pong.c -o ping_pong

srun -n 2 --ntasks-per-node=1 ./ping_pong > outNode.txt

srun -n 2 --ntasks-per-node=2 ./ping_pong > inNode.txt


