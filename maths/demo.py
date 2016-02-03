#THis file contains basic athematical tools in python
# sympy is a symbolic math package

import sympy as S
from sympy.abc import x,y,z

# Set printing
S.init_printing()

#

f= x* S.sin(x)
print "Lets Integrate: %s" % f
print "Ans: %s" % S.integrate(f,x)

f= x* S.sin(x)
print "Lets Differentiate: %s" % f
print "Ans: %s" % S.diff(f,x)

# Add all features polynomial mathematics, roots
# differential equations , trignometry etc
