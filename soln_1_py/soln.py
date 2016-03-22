
# 5M usernames
# 
# Peak memory usage: ~563 MB.
# 
# Array of pointers to string objects: 5M * 8 B
# String objects (length + string, get size of strings from
# `du usernames.txt`): 5M * 8 + ~50MB
# 
# 
# 100M usernames
# 
# Looks like 110 seconds (about 45% of total time) spent after exiting timer
# context. Releasing memory?
# 
# $ /bin/usr/time -l python soln_1_py/soln.py
# 
# TIME naive set: finished reading usernames, 8.68631696701 secs, 8.68631696701 total secs
# TIME naive set: finished building set, 63.7323050499 secs, 72.4186220169 total secs
# TIME naive set: finished appending inputs, 0.000388860702515 secs, 72.4190108776 total secs
# not in original usernames
# also not in original usernames
# super also not
# super super not
# TIME naive set: finished, 62.8483130932 secs, 135.267323971 total secs
#       246.44 real       135.09 user        77.36 sys
# 7213486080  maximum resident set size
#          0  average shared memory size
#          0  average unshared data size
#          0  average unshared stack size
#   14314137  page reclaims
#          0  page faults
#          0  swaps
#          3  block input operations
#          7  block output operations
#          0  messages sent
#          0  messages received
#          0  signals received
#       8768  voluntary context switches
#     877121  involuntary context switches

import timewith
import sys

with timewith.timewith('naive set') as timer:

    with open(sys.argv[1], 'r') as fp:
        lines = list(fp)

    timer.checkpoint('finished reading usernames')

    lines_set = set(lines)

    timer.checkpoint('finished building set')

    lines.extend(['not in original usernames',
                  'also not in original usernames',
                  'super also not',
                  'super super not'])

    timer.checkpoint('finished appending inputs')

    for x in lines:
        if x not in lines_set:
            print(x)
