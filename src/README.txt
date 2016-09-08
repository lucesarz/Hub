This is source code for the Hub template.
Written by: cesar034, wormx026

It can be described sort of like a virtual Operating system. There is one Master
HUb, and many slave hubs. CURRENTLY each slave (and the master) is its own
thread within a process. The slaves can each be programmed to do something. They
communicate with the master through a FIFO. A Scheduler will be used for the
master to know how/when to check which slave's FIFO. Other forms of
communication may be used later on in development. 

Another thing to bring up is the option of making them each a process and using
pipes to communicate, but this seems like it would be much slower.


