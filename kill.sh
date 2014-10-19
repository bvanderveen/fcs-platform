#!/bin/bash


ssh `cat tools/host` "ps aux | grep home; killall fcs-platform um6_hardware_test"