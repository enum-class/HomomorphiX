# Steps

## Number operations
1. safe operator
    1. cast
    2. multiply
    3. add
    4. sub
    5. divide round up
2. hamming weight
3. bit operators
    1. reverse
    2. get_msb_index_generic
    3. Count Leading Zeros for a 128-bit Unsigned Integer
    4. GetMSB
4. are_close
5. is_zero
6. is power of 2
7. Max64BitValue
8. is64BitOverflow
9. compare then operate
    1. add
    1. sub
    1. divide
    1. multiply
10. GetDigits
11. GreatestCommonDivisor
12. MillerRabinPrimalityTest
13. PrimeFactorize
14. NextPowerOfTwo
15. phi of n which is the number of integers m coprime to n such that 1 <= m <= n (mi's such that 1 <= mi <= n and gcd(mi,n)==1)

## Polynomial operations
1. multiply
2. add
3. sub
4. ModInverse : Multiplicative inverse for primitive unsigned integer data types
5. Returns the polynomial modulus.
6. GetCyclotomicPolynomial (Returns the m-th cyclotomic polynomial)
7. SyntheticRemainder (Returns the remainder after polynomial division of dividend with divisor = x-a. Uses synthetic division algorithm.)
8. PolynomialPower
9. Chebyshev coefficients : EvalChebyshevCoefficients Chebyshev approximation utilities
10. increment_uint_mod
11. decrement_uint_mod
12. negate_uint_mod
13. div2_uint_mod
14. barrett_reduce_64
15. dot_product_mod
16. modulo_poly_coeffs
17. negate_poly_coeffmod

## number theory
RootOfUnity
PollardRho factorization of a IntTyp
FirstPrime Finds the first prime that satisfies q = 1 mod m
NextPrime
PreviousPrime
IsGenerator : Checkes if g is a generator for any cyclic group with modulus q (non-prime moduli are supported)
FindGeneratorCyclic : Finds a generator for any cyclic group with modulus q (non-prime moduli are supported); currently q up to 64 bits only are supported
FindAutomorphismIndex2n
FindAutomorphismIndex2nComplex
FindAutomorphismIndexCyclic
PrecomputeAutoMap : Precompute a bit reversal map for a specific automorphism
ForwardTransformToBitReverse
ForwardTransform
InverseTransformFromBitReverse
InverseTransform
Precomputes the root of unity and modulus needed for NTT operation
ChineseRemainderTransformArbInterface
Computes the inverse of the cyclotomic polynomial using Newton-Iteration method.
naf : non-adjacent form 
Generate one prime with "bit_size" bits that are congruent to 1 modulo "factor"
Cooley-Tukey Radix-2 NTT
Gentleman-Sande (GS) Radix-2 InvNTT
Harvey NTT butterfly
Harvey inverse NTT butterfly

## FFT
Discrete Fourier Transform FFT
discrete weighted transform

#rns computation

====================================================================

// result[i] = cmp(operand1[i], bound) ? operand1[i] + diff
// result[i] = cmp(operand1[i], bound) ? operand1[i] + diff % modulus
// also for multiply

// (\p arg1 * \p arg2 + \p arg3)
// (\p arg1 * \p arg2 + \p arg3) % modulus
// (\p arg1 * \p arg2)
// (\p arg1 * \p arg2) % modulus

//  Montgomery Modular Multiplications
// Barrett reduction

// same for subtract

 Number-Theoretic Transform (NTT)
    Cooley-Tukey Radix-2 NTT
    Gentleman-Sande (GS) Radix-2 InvNTT
    Harvey NTT butterfly
    Harvey inverse NTT butterfly
    The NTT is equivalent to the fast Fourier transform (FFT) in a finite field : all addition and multiplications are performed with respect to the modulus q

discrete fourier transform

Computes transposed linear regression
Computes key switching in-place

distributaion generator
noise generation functionality
random generator
Polynomials in the Fourier domain have half the size of the corresponding polynomials in the standard domain

MatrixStrassen
matrix ?
norm ?

RootOfUnity
ReverseBits
Get MSB of an integer
GetDigits
GreatestCommonDivisor
MillerRabinPrimalityTest
PollardRhoFactorization
PrimeFactorize
FirstPrime
NextPrime
PreviousPrime
ModInverse
NextPowerOfTwo
GetTotient
PolyMod
PolynomialMultiplication
GetCyclotomicPolynomial
GetCyclotomicPolynomialRecursive
SyntheticRemainder
SyntheticPolyRemainder
PolynomialPower
FindAutomorphismIndex2n
PrecomputeAutoMap

Chebyshev approximation utilities

Copies \p element into \p result and calls NumberTheoreticTransform::ForwardTransformToBitReverseInPlace()
Copies \p element into \p result and calls NumberTheoreticTransform::InverseTransformFromBitReverseInPlace()
Chinese Remainder Transform for arbitrary cyclotomics.


Lattice ?

Secret Key, public key, keyswitch keys
val check : Check whether the given plaintext is valid for a given SEALContext
Class to store relinearization keys.

plaintext
cyphertext
modulus
KeyGenerator : Generates matching secret key and public key
Class to store Galois keys.
context ?

Hash functions ?

Safe integer, and checking

ComplexRoots
discrete weighted transform (DWT) and its inverse that are used to accelerate polynomial multiplications

modulo_poly_coeffs
negate_poly_coeffmod
inline void negacyclic_multiply_poly_mono_coeffmod(
sample_poly_normal

uint arithmatic mode
bitwise operation
