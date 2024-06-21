from telnetlib import Telnet
import time

tn = Telnet('192.168.1.14', 8080)


# MOVE FORWARD
# Relatative range is between is between 1000 - 2000
# 92cm
# tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 1000 } ] }')

# 119cm
# tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 2000 } ] }')

# time.sleep(1)

# MOVE LEFT 
tn.write(b'{ "op" : 1, "actions": [ { "oid": 3, "name": "left", "value": 1500 } ] }')
time.sleep(1)

tn = Telnet('192.168.1.14', 8080)
tn.write(b'{ "op" : 1, "actions": [ { "oid": 2, "name": "stop", "value": 500 } ] }')

tn.close()