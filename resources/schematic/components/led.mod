* Define the LED model
.model LED D (IS=1e-14 N=1.7 Rs=10m)

* Connect the LED in series with the voltage source
D1 N001 N002 LED

* Load resistor to limit current (Optional, adjust value as needed)
R1 N002 0 330

* Simulation control
.tran 1us 10ms
.end
