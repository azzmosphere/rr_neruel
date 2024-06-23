from telnetlib import Telnet
import time

tn = Telnet('192.168.1.14', 8080)


# MOVE FORWARD - Voltage high at  4@350  @380 5@400 
#
# Motor Driver at rest:
#    0 - Volts
#

#
# Move forward - Voltage 380 = 11.1 
#tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 380 } ] }')


# Move forward - Voltage 100 11
# tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 100 } ] }')

# 20 is 8 volt
#tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 20 } ] }')

# 5 is 3 volt
#tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 5 } ] }')

# 10 is 5
# tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 10 } ] }')

# 12 is 6 volt
tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 12 } ] }')

time.sleep(10)

tn = Telnet('192.168.1.14', 8080)
tn.write(b'{ "op" : 1, "actions": [ { "oid": 2, "name": "stop", "value": 100 } ] }')

tn.close()