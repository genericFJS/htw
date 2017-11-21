from unittest import TestCase

from example_package.command_line import main
from example_package.command_line import joke


class TestCmd(TestCase):
    def test_basic(self):
        print "Test, ob main() funktioniert"
        main()
        
    def test_joke(self):
        print "Test, ob Witz ein String ist:"
        self.assertTrue(isinstance(joke(), basestring))