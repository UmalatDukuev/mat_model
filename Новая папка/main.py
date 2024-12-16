import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("solution.csv", header=None, names=["t", "x1_rk4", "x2_rk4", "x3_rk4", "x1_ab", "x2_ab", "x3_ab"])

components = ['x1', 'x2', 'x3']

for component in components:
    plt.figure(figsize=(10, 5))

    rk4_col = f'{component}_rk4'
    ab_col = f'{component}_ab'

    plt.plot(data['t'], data[rk4_col], label=f'{component} RK4', color='blue')
    plt.plot(data['t'], data[ab_col], label=f'{component} Adams-Bashforth', color='red')

    plt.xlabel('Time (t)')
    plt.ylabel(component)
    plt.title(f'Comparison of {component} between RK4 and Adams-Bashforth')
    plt.legend()
    plt.grid()
    plt.show()
