import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("solution.csv", header=None, names=['t', 'x1', 'x2', 'x3'])

plt.plot(data['t'], data['x1'], label='x1')
plt.plot(data['t'], data['x2'], label='x2')
plt.plot(data['t'], data['x3'], label='x3')

plt.xlabel('t')
plt.ylabel('x')
plt.title('Solution of the system using numerical method')
plt.legend()
plt.grid()
plt.show()
