from numpy import sin, cos
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque
from sys import stdin, argv

if len(argv) == 2 and argv[1] == "help":
    print(f"usage: python {argv[0]} <history length> <xlims> <ylims> <zlims> <file path>")
    exit(0)

dt = 0.02
steps = 1000
file = open(argv[8], 'r') if len(argv) >= 9 else stdin
history_len = int(argv[1]) if len(argv) >= 2 else 1000
xlims = (float(argv[2]), float(argv[3])) if len(argv) >= 4 else (-5.0e12, 5.0e12)
ylims = (float(argv[4]), float(argv[5])) if len(argv) >= 6 else (-5.0e12, 5.0e12)
zlims = (float(argv[6]), float(argv[7])) if len(argv) >= 8 else (-5.0e12, 5.0e12)

fig = plt.figure()
ax = plt.axes(projection = "3d")
ax.set(xlim3d = xlims, xlabel = "X")
ax.set(ylim3d = ylims, ylabel = "Y")
ax.set(zlim3d = zlims, zlabel = "Z")

traces = dict()
history = dict()

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

ani = animation.FuncAnimation(fig, animate2, steps, interval = dt * 1000, blit = True)
plt.show()
