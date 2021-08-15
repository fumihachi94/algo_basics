#!/bin/bash

NS_NAME=helloworld


# Confirm and creat Network Namespaces
nslist=`ip netns list`

if [ ! $nslist ]; then
    sudo ip netns add $NS_NAME
    echo "Create netns: $NS_NAME"
else
    for e in ${nslist[@]}; do
        if [ ${e} = $NS_NAME ]; then
            echo "Already created netns: $NS_NAME"
        else
            sudo ip netns add $NS_NAME
            echo "Create netns: $NS_NAME"
            break
        fi
    done
fi
