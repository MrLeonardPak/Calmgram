#!/bin/sh

rm -rf build && mkdir build && cd build
cmake -DTESTS=OFF -DMAIN_EXE=ON -DSKIP_BUILD_TEST=ON ..
make -j$(nproc)
./main_server &
pid="$!"

while true
do
  if [ -d /proc/$pid ]; then
    wait "$pid"
    sleep 1
  else
    make -j$(nproc)
    ./main_server &
    pid="$!"
  fi
done
