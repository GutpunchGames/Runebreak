class Tick:
  def __init__(self, frame, checksum):
    self.frame = frame
    self.checksum = checksum

  def pretty_string(self):
    fmt = 'Frame: {frame} -- {chksum}'
    return fmt.format(
      frame = self.frame,
      chksum = self.checksum)

  def pretty_print(self):
    print(self.pretty_string())

class SimFrame:
  def __init__(self, frame, start_checksum, end_checksum, p1_input, p2_input):
    self.frame = frame
    self.start_checksum = start_checksum
    self.end_checksum = end_checksum
    self.p1_input = p1_input
    self.p2_input = p2_input

  def pretty_print(self):
    fmt = 'Sim: Frame {frame} Start: {start_checksum} End: {end_checksum} P1: {p1_input} P2: {p2_input}'
    print(fmt.format(
      frame = self.frame,
      start_checksum = self.start_checksum,
      end_checksum = self.end_checksum,
      p1_input = self.p1_input,
      p2_input = self.p2_input))
  
class GameLog:
  def __init__(self):
    self.ticks = []

  def add_tick(self, tick):
    self.ticks.append(tick)

  def pretty_print(self):
    last_tick = self.ticks[-1]
    frame = last_tick.frame
    print('Total ticks: {total} -- Frame: {frame}'.format(total = len(self.ticks), frame = frame))
  