#!/bin/bash 

FILETARGET="$1"
MULTIPLES=1;

[[ -e output.csv ]] && rm output.csv &>/dev/null; 
if [[ -z "$2" ]]; then 
    echo "No multiple entered. Using m=1"
else
    MULTIPLES=$2
fi 

if [[ -z "${1}" ]]; then 
    echo "File not found";
    exit 1; 
fi 

echo "LCSC_PN,Quantity,Customer_PN,Comment"

declare -a LINES;
mapfile -t LINES < <(tail -n+2 $1); 

for line in "${LINES[@]}"
do
    COMMENT=$(echo $line | sed -e "s/,.*//g");
    LCSC=$(echo $line | cut -d '"' -f3- | egrep -Eo "(,C[0-9]{3,20})" | sed -e "s/,//g")
    REFDES=$(echo $line | egrep -Eo ",((\".*\")|([A-Z]{1,4}[0-9]{1,3})+){1}," | egrep -Eo "([A-Z]{1,4}[0-9]{1,3}|\".*\"){1}" | sed -e "s/\"//g" | sed -e "s/,/ /g")
    n=$(echo $REFDES | wc -w);
    nREFDES=$(("$n"*"$MULTIPLES"));
    if [[ -z "$3" ]]; then 
        echo "$LCSC,$nREFDES,$REFDES" >> output.csv
    else 
        echo -e "\t\t$nREFDES\t\t$REFDES\t\t\t\t$COMMENT"
    fi
done 

