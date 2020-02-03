@ECHO off
SET ser=%1
ssh -oHostKeyAlgorithms=+ssh-dss username@%ser%.cs.cuhk.hk
