cat onet/40000-functions-and-titles.txt | tr A-Z a-z | tr -sc "0-9A-Za-z'" ' ' | sed 's/\([^aouis]\)s /\1 /g' >onet/40000-functions-and-titles-stemmed.txt
