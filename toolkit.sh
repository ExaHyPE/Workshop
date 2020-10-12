#! /bin/bash

if [[ $# -eq 0 ]]; then
    specfile=$( find . -name "*.exahype" )
    arg=""
elif [[ ${!#} == "*.exahype" ]]; then
    specfile=${!#}
    arg=${@:1:$#-1}
else
    specfile=$( find ${!#} -name "*.exahype" )
    arg=${@:1:$#-1}
fi

SOURCE="${BASH_SOURCE[ 0]}"
while [  -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
    DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"
    SOURCE="$(readlink "$SOURCE")"
    [[  $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
exaseis_path="$( cd -P "$( dirname "$SOURCE" )" >/dev/null && pwd )"

IFS=' ' read -r -a array <<< "$specfile"

if [[ ${#array[@]} -ne 1 ]]; then
    echo "Available *.exahype files"
    for i in "${!array[@]}"
    do
        echo $i" :"${array[$i]}
    done
fi


${exaseis_path}/ExaHyPE/Toolkit/toolkit.sh $arg $specfile
