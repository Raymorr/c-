#!/bin/bash

dir="/home/p/users_data"

./client < "${dir}/init_commands.txt"

for ((i=0;i<20;i++))
  do \
    ./client < "${dir}/client_commands.txt" > /tmp/res$i &
  done
wait

./client < "${dir}/finish_commands.txt"

for ((i=0;i<20;i++))
  do \
    for ((j=0;j<i;j++))
      do \
        diff -q /tmp/res$i /tmp/res$j
      done
    grep '^ *Student' /tmp/res$i | wc
  done
