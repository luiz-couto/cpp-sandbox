import numpy as np
import matplotlib.pyplot as plt

# Modify these values and see what happens
m = 2**32 - 1  # Modulus
a = 48271      # Multiplier
c = 0          # Increment
X0 = 42        # Seed
n_points = 1024

x_vals = np.zeros(n_points)
x_vals[0] = X0

for i in range(1, n_points):
    x_vals[i] = (a * x_vals[i-1] + c) % m
    
x_vals /= m
x = x_vals[0::2]
y = x_vals[1::2]
plt.figure(figsize=(6,6))
plt.scatter(x, y, s=5, alpha=1)
plt.xlabel("")
plt.ylabel("")
plt.xticks([])
plt.yticks([])
plt.show()
