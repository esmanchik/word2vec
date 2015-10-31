#!/bin/bash
# mysql -u root onet -e "select od.onetsoc_code, od.title, group_concat(at.alternate_title separator ' '), od.description from occupation_data od left join alternate_titles at on od.onetsoc_code = at.onetsoc_code group by od.onetsoc_code"
# mysql -u root onet -e "select replace(replace(od.onetsoc_code, '-', ''), '.', ''), od.title, at.alternate_title, od.description from occupation_data od left join alternate_titles at on od.onetsoc_code = at.onetsoc_code order by od.onetsoc_code" >$1

time ./word2vec -train $1.txt -output $1-vectors.bin -save-vocab $1-vocab.txt -size 500 -cbow 0 -binary 1 -min-count 3
