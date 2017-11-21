#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on May 29, 2017

@author: jonatan
'''


def printme(stri):
    '''
    Hier wird ein String ausgegeben. Das Selbe wie print() lol :-)
    
    Insgesamt wird folgendes geleistet:
    
        - Der String wird auf der Console ausgegeben.
            1. Das ist schoen (Umlaute sind es hier in der doc nicht -- vielleicht sollte man lieber in englisch dokumentieren?).
            2. und elegant!
            3. Nachdem der Header für UTF-8 ergänzt wurde, ist auch utf8 erlaubt. Cool, odä?
        - Der String wird zurueck gegeben.
    
    Im Prinzip ist die Funktion bloss:
    
    >>> print (stri)
    return stri;
    
    Toll, oder?
    
    @type stri: String
    @param stri: Der auszugebenende String.
    @rtype: String
    @return: Der eingegebene String.
    '''
    print(stri)
    return stri;

if __name__ == '__main__':
    print("This line will be printed.")
    printme("test")
    pass
