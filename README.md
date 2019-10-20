# Foundations of cryptography

In the src folder there are:

**discrete_log_problem**: 

A program in C that can calculate cyclic/non cyclic group ad the cyclic generator. So it calculates the exponent i s.t a=g^i starting from the seed 'g' of the group. After this, it calculates legendre and jacobi symbols.

-----------------------------------------------------------------------------------

**diffie-hellman keys exchange (based on the discrete log problem)**:

The main idea of DH algo is create a sessione key between two principal A and B without interchange the key.
DH uses public key scheme and number theory to ensure this property.

NOTE: This program uses random number for simulation. To prevent critto-analytic attacks you have to solve pseudorandom problem in C.

-----------------------------------------------------------------------------------
