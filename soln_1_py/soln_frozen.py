
# 5M usernames
# 
# 
# 
# 100M usernames
# 
# TIME naive set: finished reading usernames, 8.01400208473 secs, 8.01400208473 total secs
# TIME naive set: finished building set, 64.9406509399 secs, 72.9546530247 total secs
# TIME naive set: finished appending inputs, 0.00190019607544 secs, 72.9565532207 total secs
# not in original usernames
# also not in original usernames
# super also not
# super super not
# TIME naive set: finished, 63.2387018204 secs, 136.195255041 total secs
#       241.23 real       134.78 user        72.77 sys
# 6844895232  maximum resident set size
#          0  average shared memory size
#          0  average unshared data size
#          0  average unshared stack size
#   14314787  page reclaims
#          0  page faults
#          0  swaps
#          1  block input operations
#         24  block output operations
#          0  messages sent
#          0  messages received
#          0  signals received
#       9653  voluntary context switches
#     777183  involuntary context switches
#

import timewith
import sys

with timewith.timewith('naive set') as timer:

    with open(sys.argv[1], 'r') as fp:
        lines = list(fp)

    timer.checkpoint('finished reading usernames')

    lines_set = frozenset(lines)

    timer.checkpoint('finished building set')

    lines.extend(['not in original usernames',
                  'also not in original usernames',
                  'super also not',
                  'super super not'])

    timer.checkpoint('finished appending inputs')

    for x in lines:
        if x not in lines_set:
            print(x)
