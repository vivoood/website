#!/bin/sh
killall -9 vivoood
cd /home/pi/website/build
./vivoood --docroot . --http-address 0.0.0.0 --http-port 9090 &
