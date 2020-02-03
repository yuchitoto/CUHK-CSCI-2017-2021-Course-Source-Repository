@ECHO off
SET fil=%1
SET ser=%2
scp %fil% username@%ser%.cs.cuhk.edu.hk:~
