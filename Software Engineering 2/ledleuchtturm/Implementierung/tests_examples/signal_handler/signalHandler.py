import signal
import sys
def signal_handler(signal, frame):
    print('You pressed Ctrl+C!')
    cleanup(string)
    sys.exit(0)


def cleanup(cleanupVar):
    print cleanupVar


# global vars
string = "cleanup called"


if __name__=="__main__":

    signal.signal(signal.SIGINT, signal_handler)
    print('Press Ctrl+C')
    signal.pause()

    print "clean up should be done"
