from telnetlib import Telnet
import time

with Telnet('192.168.1.14', 8080) as tn:
    tn.interact()

tn.write(b'{ "op" : 1, "actions": [ { "oid": 1, "name": "moveforward", "value": 500 } ] }')
time.sleep(1)
tn.write(b'{ "op" : 1, "actions": [ { "oid": 2, "name": "stop", "value": 500 } ] }')

tn.close()