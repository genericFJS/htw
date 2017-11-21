from unittest import TestCase

from example_package.command_line import joke


class TestJoke(TestCase):
    def test_is_string(self):
        print "Test, ob Witz ein String ist:"
        self.assertTrue(isinstance(joke(), basestring))