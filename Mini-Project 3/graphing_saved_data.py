import matplotlib.pyplot as plt
import csv

with open('data_out.csv', 'r', newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=' ', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    right_motor = next(reader)
    left_sensor = next(reader)
    right_sensor = next(reader)
    left_motor = next(reader)

# print(left_motor)
float_right_motor = []
for i in range(len(right_motor)):
    float_right_motor.append(float(right_motor[i]))
float_left_motor = []
for i in range(len(left_motor)):
    float_left_motor.append(float(left_motor[i]))

float_right_sensor = []
for i in range(len(right_sensor)):
    float_right_sensor.append(float(right_sensor[i]))
float_left_sensor = []
for i in range(len(left_sensor)):
    float_left_sensor.append(float(left_sensor[i]))

t = [i for i in range(len(left_sensor))]
plt.plot(t, float_left_sensor)
plt.plot(t, float_right_sensor)
plt.plot(t, float_left_motor)
plt.plot(t, float_right_motor)

plt.legend(["left sensor", "right sensor", "left motor", "right motor"])
plt.title("Motor and Sensor Values")
plt.xlabel("Data Points")
plt.ylabel("Motor Speeds and Sensor Values")

plt.show()