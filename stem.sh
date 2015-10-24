cat $1.txt | tr A-Z a-z | tr -sc "0-9A-Za-z'" ' ' | sed 's/\([^aouis]\)s /\1 /g' >$1-stemmed.txt
