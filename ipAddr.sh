#!/bin/ksh
PATH=$HOME/bin:$PATH

IPADDR=$(hostname -I)
IPV6=$(echo $IPADDR | awk '{print substr($1,5,1)}')


while [ "$IPADDR" = "" -o "$IPV6" = ":" ];do
  sleep 1
  IPADDR=$(hostname -I)
  IPV6=$(echo $IPADDR | awk '{print substr($1,5,1)}')
done

$HOME/bin/ipAddr $*
