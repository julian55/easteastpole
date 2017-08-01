'''
%d – integer
%f – float
%s – string
%x – hexadecimal
%o – octal
%r - raw
'''
d = int(1)
str_int = "%d and %d are integers "
str_raw = "%r and %r are raw "
str_hex = "%x is hexadecial representation for %d"

print(str_int %(1,2))
print(str_raw %(3.123213,'2312'))
print(str_hex %(123123, 123123))
