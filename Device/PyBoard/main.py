# main.py -- put your code here!
import pyb
log = open('/sd/log.csv','w')
log.write('x,y,z,t(mS)\n')
log.close()
rtc = pyb.RTC()

rtc.wakeup(100)
accel = pyb.Accel()
while True:
	log = open('/sd/log.csv','a')
	x = accel.x()
	y = accel.y()
	z = accel.z()
	t = pyb.millis()
	log.write('{},{},{},{}\n'.format(t,x,y,z))
	log.close()
	#print(x,y,z,t)
	#pyb.delay(100)
	pyb.stop()
