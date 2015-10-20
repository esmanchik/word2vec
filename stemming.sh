cat 40000-onet-functions-and-titles.txt | tr A-Z a-z | tr -sc "0-9A-Za-z'" ' ' | sed 's/\([^aouis]\)s /\1 /g' >40000-onet-functions-and-titles-stemmed.txt
