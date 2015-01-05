#!/bin/bash

ssh -o ConnectTimeout=1 `cat tools/host` "ps aux | grep home; killall fcs-platform um6_hardware_test"
