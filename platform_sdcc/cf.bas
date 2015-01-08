10 mode 0 : border 0 : ink 0,0 : ink 1,26
19 locate 1,12
20 print "    Color  Flood"
25 openout "heyjude"
30 memory &0fff
40 load "cf.bin"
60 call &1000
70 print "Back to BASIC."
80 input "Press ENTER.",a$
