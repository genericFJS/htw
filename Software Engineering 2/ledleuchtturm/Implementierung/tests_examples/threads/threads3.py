class blinkThread(threading.Thread):
    def run(self):
        global threadRun
        while threadRun == 1:
            print "1"
            #GPIO.setup(pins[2], True)
            time.sleep(0.25)

            print "0"
            #GPIO.setup(pins[2], False)
            time.sleep(0.25)


# --- define threads
class newblinkThread(threading.Thread):
    def __init__(self):
        # first call constructor
        super(newblinkThread,self).__init__()

        # create own variable
        self.stop_event = threading.Event()


    def run(self):
        while not self.stop_event.is_set():
            print "1"
            #GPIO.setup(pins[2], True)
            time.sleep(0.25)

            print "0"
            #GPIO.setup(pins[2], False)
            time.sleep(0.25)


    def stop(self):
        # stop thread with thread run
        print "stop thread"
        self.stop_event.set()



blink = newblinkThread()

blink.start()
time.sleep(1)
blink.stop()
