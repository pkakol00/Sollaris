from numpy import sin, cos
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
from sys import stdin

history_len = 1000
dt = 0.01

fig = plt.figure()
ax = plt.axes(projection = "3d")
ax.set(xlim3d = (0, 100), xlabel = "X")
ax.set(ylim3d = (-5, 5), ylabel = "Y")
ax.set(zlim3d = (-5, 5), zlabel = "Z")

traces = dict()
history = dict()

# file = stdin
file = open("data.txt", 'r')

def animate2(iteration):
    ids = []
    while True:
        line = file.readline().strip()
        if line == "":
            return traces.values()

        if line == "next":
            break

        line = line.split(";")
        nums = [float(n) for n in line]
        id = int(nums[0])
        ids.append(id)

        if id not in traces:
            traces[id] = ax.plot([], [], [], '.-', lw = 1, ms = 2)[0]
            history[id] = [deque(maxlen = history_len) for _ in range(3)]

        for axis in range(3):
            history[id][axis].appendleft(nums[axis + 1])

    for id in history.keys():
        if id not in ids:
            if len(history[id][0]) != 0:
                for axis in range(3):
                    history[id][axis].pop()

    for id in history.keys():
        traces[id].set_data(history[id][0], history[id][1])
        traces[id].set_3d_properties(history[id][2])

    return traces.values()

ani = animation.FuncAnimation(fig, animate2, 1000, interval = dt * 1000, blit = True)
plt.show()
