10 mode 0 : border 0 : ink 0,0 : ink 1,26
16 ink 2,6 : ink 3,15 : ink 4,24 : ink 5,18 : ink 6,20 : ink 7, 2
19 locate 1,12
20 print "    Color  Flood"
25 openout"heyjude"
30 memory &0fff
40 load "cf.bin"
50 mode 0
60 call &1000
80 input "",a$
