# -*- coding: utf-8 -*-
'''
    Das Paket ledleuchtturm verbindet sich mit einer postgresql Datenbank
    und wartet auf Aktualisierungen einer definierten Maschine. Bei einer
    Aktualisierung werden definierte Ports eines Raspberry Pi ein- oder
    ausgeschaltet. Direkt nach dem Verbindungsaufbau wird zuerst der aktuelle
    Status gelesen und dann werden die entsprechenden Pins geschaltet. 
    Danach wird auf Updates gewartet. Durch das Signal Strg-C werden die Ports 
    des Raspberry Pi in ihren Anfangszustand versetzt und alle Verbindungen oder
    geöffneten Dateien geschlossen.
'''
