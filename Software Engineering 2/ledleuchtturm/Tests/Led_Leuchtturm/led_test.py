import unittest

from ledFunc import toggleLED
from ledFunc import enableLED
from ledFunc import switchAllOff
from ledFunc import blink
from ledFunc import blinkThreadFunction
from ledFunc import killBlinkThread
from ledFunc import changeState
from ledFunc import setLEDsGlobal
from ledFunc import initLEDs

from dbFunc import testDBconnection
from dbFunc import waitForDBupdate
from dbFunc import getCurrentDBstate

from fileFunc import checkArgumentForConfigFile
from fileFunc import configFileExists
from fileFunc import configFileValidJsonFile
from fileFunc import createStdConf
from fileFunc import getJsonFileObject

from stdFunc import printConfigSettings
from stdFunc import debug

class Test_ledFunc(unittest.TestCase):
    def test_toggleLED(self):
        toggleLED()
    
    def test_enableLED(self):
        enableLED()
        
    def test_switchAllOff(self):
        switchAllOff()
    
    def test_blink(self):
        blink()
        
    def test_blinkThreadFunction(self):
        blinkThreadFunction()
        
    def test_killBlink(self):
        killBlinkThread()
        
    def test_changeState(self):
        changeState()
        
    def test_setLEDsGlobal(self):
        setLEDsGlobal()
        
    def test_initLEDs(self):
        initLEDs()

class Test_dbFunc(unittest.TestCase):
    def test_testDBconnection(self):
        testDBconnection()
    
    def test_waitForDBupdate(self):
        waitForDBupdate()
        
    def test_getCurrentDBstate(self):
        getCurrentDBstate()

class Test_fileFunc(unittest.TestCase):
    def test_checkArgumentForConfigFile(self):
        checkArgumentForConfigFile()
        
    def test_configFileExists(self):
        configFileExists()
        
    def test_configFileValidJsonFile(self):
        configFileValidJsonFile()
        
    def test_createStdConf(self):
        createStdConf()
        
    def test_getJsonFileObject(self):
        getJsonFileObject()
        
class Test_stdFunc(unittest.TestCase):
    def test_printConfigSettings(self):
        printConfigSettings()
        
    def test_debug(self):
        debug()
        
if __name__ == "__main__":
    #import svs;sys.argv = ['', 'Test.testName']
    unittest.main()
