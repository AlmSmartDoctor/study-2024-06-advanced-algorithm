class Fancy:
    MOD = 10**9 + 7

    def __init__(self):
        self.sequence = []
        self.add_accum = 0
        self.mul_accum = 1

    def append(self, val: int) -> None:
        normalized_val = (val - self.add_accum + self.MOD) * pow(self.mul_accum, self.MOD - 2, self.MOD) % self.MOD
        self.sequence.append(normalized_val)

    def addAll(self, inc: int) -> None:
        self.add_accum = (self.add_accum + inc) % self.MOD

    def multAll(self, m: int) -> None:
        self.add_accum = self.add_accum * m % self.MOD
        self.mul_accum = self.mul_accum * m % self.MOD

    def getIndex(self, idx: int) -> int:
        if idx >= len(self.sequence):
            return -1
        return (self.sequence[idx] * self.mul_accum + self.add_accum) % self.MOD
        


# Your Fancy object will be instantiated and called as such:
# obj = Fancy()
# obj.append(val)
# obj.addAll(inc)
# obj.multAll(m)
# param_4 = obj.getIndex(idx)