10 mode 0 : border 26 : ink 0,0 : ink 1,26
16 ink 2,16 : ink 3,25 : ink 4,22 : ink 5,23 : ink 6,14 : ink 7,17
17 ink 8,0 : ink 9,13
18 ink 10,3 : ink 11,12 : ink 12,9 : ink 13,10 : ink 14,1 : ink 15,4
19 locate 1,12
20 print "    Color  Flood"
25 openout "heyjude"
30 memory &0fff
40 load "cf.bin"
60 call &1000
70 print "Back to BASIC."
80 input "Press ENTER.",a$
