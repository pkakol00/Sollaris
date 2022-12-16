# importing mplot3d toolkits, numpy and matplotlib
from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
from sys import argv

fig = plt.figure()

# syntax for 3-D projection
ax = plt.axes(projection ='3d')

planets = None

file = argv[1]

with open(file) as f:
    line = f.readline()
    f.seek(0)
    planets = [[[], [], []] for _ in range(line.count(") (") + 1)]

    for line in f:
        line = line.replace(") (", ";").replace("(", "").replace(")", "").replace(" ", "")
        for i, planet in enumerate(line.split(";")):
            tmp = [float(a) for a in planet.split(',')]
            planets[i][0].append(tmp[0])
            planets[i][1].append(tmp[1])
            planets[i][2].append(tmp[2])

# plotting
for i, planet in enumerate(planets):
    ax.plot3D(planet[0], planet[1], planet[2])

plt.legend(["Sun", "Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"])


plt.title("Układ słoneczny, 165 lat co 12h")
plt.show()


