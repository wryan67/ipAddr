#!/bin/ksh
PATH=$HOME/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin

IPADDR=$(hostname -I)
HOSTNAME=$(hostname -s)

while [ "$IPADDR" = "" ];do
  sleep 1
  IPADDR=$(hostname -I)
done

$HOME/bin/ipAddr
