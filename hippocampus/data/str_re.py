import re

regular_exp = r"([a-zA-Z]+)([0-9]+)"
text_target = "gunta34234ewrer234124er23opzew wer w341 3421"

#1. single match
match = re.search(regular_exp,text_target)
if match != None:
    print("Match at index %s, %s" % (match.start(), match.end()))
    print("Full match: %s" % (match.group(0)))

    print("Name: %s" % (match.group(1)))
    print("Index: %s" % (match.group(2)))
else:
    print ("The regex pattern does not match.")


'''single match

Match at index 0, 10
Full match: gunta34234
Name: gunta
Index: 34234

'''

#2. match all
reg_number = '\d+'
reg_email = r"[a-zA-Z0-9_]+@[a-z0-9A-Z]\.[a-z]+"

match_number = re.findall(reg_number, text_target)
print(match_number)

'''match all
['34234', '234124', '23', '341', '3421']

'''
