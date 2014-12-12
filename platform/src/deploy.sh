
#scp -oStrictHostKeyChecking=no chr-um6/tests/um6_hardware_test $host:/home/um6_hardware_test
#ssh -t $host /home/um6_hardware_test
scp -oStrictHostKeyChecking=no platform/fcs-platform $host:/home/fcs-platform
ssh -t $host /home/fcs-platform