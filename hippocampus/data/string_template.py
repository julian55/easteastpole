#
from string import Template

#`t` is a simple template string, with $x
t=Template('aa is $x')

#`substitute` method instancialize the template
print(t.substitute({'x': 100}))

print(t.substitute(x=100))

#print a template object's location
print(t)

g=Template('$name is $age years old.')

gt=g.substitute(name = 'Lily',age = 100)
#no partial substitution allowed
# gt=g.substitute(name = 'Lily')
