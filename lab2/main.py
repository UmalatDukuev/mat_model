import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("build/euler_results.csv")
plt.plot(data['Time'], data['Temperature'], label="Euler")

data = pd.read_csv("build/heun_results.csv")
plt.plot(data['Time'], data['Temperature'], label="Heun")

plt.xlabel("Time")
plt.ylabel("Temperature")
plt.legend()
plt.show()
