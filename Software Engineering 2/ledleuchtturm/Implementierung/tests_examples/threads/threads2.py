import threading
import time

loop = 1

class MyThread(threading.Thread):
    def __init__(self):
        self.loop = 1

    def run(self):
        # needed to stop the thread

        # run the thread until loop is set to 0
        while self.loop is 1:
            #print 'Thread: running'
            #time.sleep(1)
            print 'Thread: 0'
            time.sleep(0.25)

            print 'Thread: 1'
            time.sleep(0.25)

        # last action of thread
        print 'Thread: I\'m done'

    def stop(self):
        self.loop = 0

print 'start thread'
MyThread().start()
time.sleep(5)
loop = 0
print 'thread stoped'
