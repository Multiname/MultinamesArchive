#!/bin/bash
MAPPER="mapper.py"
REDUCER="reducer.py"
INPUT="/user/hduser/input"
OUTPUT="/user/hduser/output"
SW=`cat sw.csv`
DARG="SW=${SW}"
/usr/local/hadoop/bin/hdfs dfs -rm -R -f $OUTPUT
/usr/local/hadoop/bin/mapred streaming -D $DARG -input $INPUT -output $OUTPUT -
mapper $MAPPER -reducer $REDUCER
/usr/local/hadoop/bin/hdfs dfs -head "$OUTPUT/part-00000"