import time

class timewith():
    def __init__(self, name=''):
        self.name = name
        self.start = time.time()
        self.last = self.start

    @property
    def elapsed(self):
        curr = time.time()
        ret = (curr - self.last, curr - self.start)
        self.last = curr
        return ret

    def checkpoint(self, name=''):
        since_last, since_start = self.elapsed
        print 'TIME {timer}: {checkpoint}, {since_last} secs, {since_first} total secs'.format(
            timer=self.name,
            checkpoint=name,
            since_last=since_last,
            since_first=since_start
        ).strip()

    def __enter__(self):
        return self

    def __exit__(self, type, value, traceback):
        self.checkpoint('finished')
        pass