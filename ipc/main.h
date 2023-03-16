/*
Name : Suraj Roy
Date 14/01/2023
Description : Implement communication between three processes using PIPE, FIFO and SHM
*/
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define SHMSIZE 50
