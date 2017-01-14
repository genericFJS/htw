#!/bin/bash
cd s74053
javac src/filetransfer_udp/packets/*.java -d bix -sourcepath src
javac src/filetransfer_udp/*.java -d bix -sourcepath src