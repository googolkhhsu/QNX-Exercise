#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "my_devctl.h"

int main(int argc, char **argv)
{
    int fd, ret, val;
    data_t data;

    if ((fd = open("/dev/powertrain", O_RDONLY)) == -1)
    {
        return (1);
    }

    /* Find out what the value is set to initially */
    val = -1;
    ret = devctl(fd, MY_DEVCTL_GETVAL, &val, sizeof(val), NULL);
    printf("GET returned %d w/ server value %d \n", ret, val);

    /* Set the value to something else */
    val = 25;
    ret = devctl(fd, MY_DEVCTL_SETVAL, &val, sizeof(val), NULL);
    printf("SET returned %d \n", ret);

    /* Verify we actually did set the value */
    val = -1;
    ret = devctl(fd, MY_DEVCTL_GETVAL, &val, sizeof(val), NULL);
    printf("GET returned %d w/ server value %d == 25? \n", ret, val);

    /* Now do a set/get combination */
    memset(&data, 0, sizeof(data));
    data.tx = 50;
    ret = devctl(fd, MY_DEVCTL_SETGET, &data, sizeof(data), NULL);
    printf("SETGET returned with %d w/ server value %d == 25?\n",
           ret, data.rx);

    /* Check set/get worked */
    val = -1;
    ret = devctl(fd, MY_DEVCTL_GETVAL, &val, sizeof(val), NULL);
    printf("GET returned %d w/ server value %d == 50? \n", ret, val);
    return (0);
}