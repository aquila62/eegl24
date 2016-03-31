#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 #states"
echo "Example: $0 2000"
exit 1
fi
./eeglgen $1 | ./ranwlk
