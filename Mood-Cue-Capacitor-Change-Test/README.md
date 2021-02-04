### Testing what the Analog values will be from the POT and how they change the servo value:
------

POT on turned MAX and values change for the last 10 seconds:

Without Capacitors in the Circuit:

- POT: min: ***1004***, max: ***1023*** dev: ***19*** | SERVO: min: ***175***, max: ***179*** dev: ***4*** expected: ***179***

With Capacitor in front of the POT:

- POT: min: ***1016***, max: ***1023*** dev: ***6*** | SERVO: min: ***177***, max: ***179*** dev: ***2*** expected: ***179***

With 2 Capacitor in front of the POT:

- POT: min: ***1017***, max: ***1023*** dev: ***6*** | SERVO: min: ***177***, max: ***179*** dev: ***2*** expected: ***178***

With Capacitor in front of the POT and in front of the SERVO:

- POT: min: ***1020***, max: ***1023*** dev: ***3*** | SERVO: min: ***178***, max: ***179*** dev: ***1*** expected: ***179***

***Note that the deviation is the same no matter how much the POT is turned.***
