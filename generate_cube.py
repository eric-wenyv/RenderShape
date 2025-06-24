import csv
import numpy as np

x_range = np.arange(0.0, 1.01, 0.1)
y_range = np.arange(0.0, 1.01, 0.1)
z_range = np.arange(0.0, 2.01, 0.1)

with open('./cube_edge_points.csv','w',newline='') as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(['x', 'y', 'z'])
    for x in x_range:
        for y in y_range:
            for z in z_range:
                writer.writerow([round(x, 2), round(y, 2), round(z, 2)])