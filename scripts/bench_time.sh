TIMEFORMAT="%U %S"

input="./cases.txt"
executable="./main"

unit_result=$( { time "${executable}" < "${input}" > /dev/null 2>/dev/null; } 2>&1 )

echo "${unit_result}" | awk '{ print $1 + $2 }' >> "benched_time"
