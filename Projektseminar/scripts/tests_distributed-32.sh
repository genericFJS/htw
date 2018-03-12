#!/bin/bash
# Ordner wechseln, um disthash auszuführen.
cd "$(dirname "$0")"
cd "../disthash"
# Tests mit entsprechenden Einstellungen ausführen: Modus und HashMap-Größe.
#    129/32=4
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 4
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 4
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 4
#    129
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129
#    645
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 645
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 645
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 645
#   1290
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 1290
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 1290
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 1290
#   3870
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 3870
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 3870
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 3870
#  25800
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 25800
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 25800
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 25800
# 129000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 129000
# 193500
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 193500
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 193500
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 193500
# 258000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 258000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 258000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 258000
# 516000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 516000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 516000
mpiexec -f ~/projektseminar/machines/machinefile -n 32 ./disthash -d -t -h 516000