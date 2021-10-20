Let us define a binary operation ⊗ on three symbols a, b, c according to the following table; thus a ⊗ b = b , b ⊗ a = c , and so on. Notice that the operation defined by the table is neither associative nor commutative.
⊗ a b c
a b b a
b c b a
c a c c
Describe an efficient algorithm that examines a string of these symbols, say bbbbac, and decides whether or not it is possible to parenthesize the string in such a way that the value of the resulting expression is p = a. For example, on input bbbbac your algorithm should return yes because ((b ⊗ (b ⊗ b)) ⊗ (b ⊗ a)) ⊗ c = a.

For 1 ≤ i ≤ j ≤ n, we let T[i, j] ⊆ {a, b, c} denote the set of symbols e for which there is a parenthesization of xi..xj yielding e. We let e ⊗ b denote the product of e and b using the table. p ∈ {a, b, c} is the symbol we are considering.
Pseudocode
for i ← 1 to n do
  T[i, i] ← xi
for s ← 1 to n-1 do
  for i ← 1 to n-s do
    T[i,i + s] ← ∅
    for k ← i to i+s-1 do
      for each e ∈ T[i,k] do
        for each b ∈ T[k + 1,i + s] do
          T[i,i+s] ← T[i,i+s] ∪e ⊗ b
if p ∈ T[1,n] then
  return yes
  else
    return no
    
Extend and implement the Dynamic Programming Algorithm above so that it prints a parenthesized expression yielding the goal or “No parenthesization possible.” if no such parenthesization exists.

Input format (no need to check its validity):
- The first line contains a positive integer (say n).
- The symbols: The second line contains at least n characters (if it contains more, only the first n are relevant). These characters are the symbols of the alphabet. The last symbol is the “goal”.
- The operation: The following n lines contain at least n characters each (if a line contains more characters, only the first n are relevant). This is an nxn matrix containing the results of the operations.
- Expression: The last line of the input contains a sequence of characters, consisting of the valid symbols for which you have to seek for a parenthesization.

A sample input:
3
abc
aac
baa
caa
caaccb
and corresponding possible outputs (not exhaustive):
(c((aa)((cc)b))
(c(a(a((cc)b))))
(((ca)a)((cc)b))
(((ca)a)((cc)b))
