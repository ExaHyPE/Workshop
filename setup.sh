#!/bin/bash

PWD=$( pwd )

exaseis_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )

if [ ! -e ${1}/ApplicationExamples ]; then
    echo ${1}" is not an ExaHyPE path: "
    echo ${1}/ApplicationExamples" doesn't exist"
    exit 1
fi
if [ ! -e $1/ApplicationExamples/workshop ]; then
    ln -s ${exaseis_path}/Applications $1/ApplicationExamples/workshop
fi
if [ ! -e ${exaseis_path}/ExaHyPE ]; then
    ln -s ${1} ${exaseis_path}/ExaHyPE
fi
