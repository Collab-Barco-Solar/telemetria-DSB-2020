import random
from itertools import count
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.style.use('fivethirtyeight')

x_vals = []
y_vals = []

index = count()


def animate(i):
    data = pd.read_csv('dados.csv')
    x = data['Canal 1']
    y1 = data['Canal 2']
    y2 = data['Canal 3']

    plt.cla()

    plt.plot(x, y1, label='Canal 1')
    plt.plot(x, y2, label='Canal 2')

    plt.legend(loc='upper left')
    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate, interval=1000)

plt.tight_layout()
plt.show()
