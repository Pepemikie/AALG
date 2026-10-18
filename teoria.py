#!/usr/bin/env python3
# Compara average_ob observado con el valor esperado teorico (OB = comparaciones de claves)
import sys
from fractions import Fraction

def a_insert(n):                      # (n^2+3n)/4 - H_n
    h = sum(Fraction(1, k) for k in range(1, n + 1))
    return float(Fraction(n * n + 3 * n, 4) - h)

def a_bubble(n):                      # burbuja con parada anticipada (i-- en cada pasada)
    def cdf(m):                       # P(max b_j <= m), b_j uniforme en 0..j-1
        r = Fraction(1)
        for j in range(1, n + 1):
            r *= Fraction(min(j, m + 1), j)
        return r
    e = Fraction(0)
    for m in range(n):
        pm = cdf(m) - (cdf(m - 1) if m > 0 else 0)
        p = min(m + 1, n - 1)         # pasadas ejecutadas
        e += pm * (p * n - p * (p + 1) // 2)
    return float(e)

f, name = sys.argv[1], sys.argv[2]
fn = a_insert if name == "insert" else a_bubble
print("%6s %14s %14s %9s" % ("N", "observado", "teorico", "dif %"))
for line in open(f):
    c = line.split()
    n, obs = int(c[0]), float(c[3])
    t = fn(n) if n > 1 else 0.0
    print("%6d %14.2f %14.2f %9.3f" % (n, obs, t, 100 * (obs - t) / t if t else 0))