10 mode 0 : border 26 : ink 0,0 : ink 1,26
16 ink 2,6 : ink 3,24 : ink 4,18 : ink 5,20 : ink 6,2 : ink 7,8
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
