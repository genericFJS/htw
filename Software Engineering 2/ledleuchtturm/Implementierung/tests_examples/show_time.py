import datetime

now = datetime.datetime.now()
currentTime = "%s:%s:%s am %s-%s-%s" %(now.hour, now.minute, now.second,
        now.day, now.month, now.year)
print "Es ist %s" % currentTime
