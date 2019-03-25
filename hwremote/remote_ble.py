from bluepy import btle
import time
import binascii

print "Connecting..."

dev_mac = "18:62:E4:3F:DF:F6"
dev = btle.Peripheral(dev_mac)

svc_uuid = "ffe0"
svc = dev.getServiceByUUID(btle.UUID(svc_uuid))
svc = [svc for svc in dev.services if svc.uuid == svc_uuid][0]
print svc

ch_uuid = "ffe1"
ch = svc.getCharacteristics(btle.UUID(ch_uuid))[0]
print ch
result = ch.write('\x02\x12', withResponse=True)
time.sleep(3.0)
print result
