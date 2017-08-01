from string import *
#1 striping
# strip() lstrip() rstrip()

str_2b =  "::2017-02-12::"
print('origin string : ' + str_2b)
print(str_2b.strip('-'))
print(str_2b.lstrip(':'))
print(str_2b.rstrip(':'))

''' output 1
origin string : ::2017-02-12::
::2017-02-12::
2017-02-12::
::2017-02-12
'''
print('\t')

#2. min() max() - ascii code value
print('max(\'zZ\')' + 'is ' + max('zZ'))
print('min(\'zZ\')' + 'is ' + min('zZ'))
print('\t')

''' output 2
max('zZ')is z
min('zZ')is Z
'''

#3. maketrans() translate()
str_ori =bytes("1234567890",'utf8')
str_post=bytes("0123456789",'utf8')
mapp = bytes.maketrans(str_ori,str_post)
str_target = "23425883423"
print("map "+str_target + " to ")
print(str_target.translate(mapp))
print('\t')

'''
map 23425883423 to
12314772312

'''

#4. substitution, replacement, replace()
#"AAA is BBB ".replace("AAA","CCC",1)


#5.len(), count()
str_target ="str, str, str"
print(str_target.count("str"))
print(str_target.count("str",0,10))

#6. center(),ljust(), rjust()
str_target = "Flower"
print(str_target.center(len(str_target)+10, '*'))
print(str_target.ljust(len(str_target)+10,'*'))
print(str_target.rjust(len(str_target)+10,'*'))

'''
*****Flower*****
Flower**********
**********Flower
'''

#7. isalpha(), isalnum(), isspace()
#


#8. join() use join_char to join a tuple/list of string
join_char = "++"
print(join_char.join(("A", "B", "C")))
print(join_char.join(["A", "B", "C"]))
