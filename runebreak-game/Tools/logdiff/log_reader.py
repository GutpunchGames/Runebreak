from log_entities import Tick
from log_entities import SimFrame
from log_entities import GameLog

class Cursor:
  def __init__(self):
    self.cursor = 0
    self.lines = []

  def advance(self, count=1):
    self.cursor += count

class LogReader:
  def __init__(self):
    self.game_log = GameLog()

  def read(self, path):
    print('reading log: {path}'.format(path = path))
    f = open(path, 'r')
    lines = f.readlines()
    self.lines = [line.strip() for line in lines]
    print('read {num_lines} lines of input'.format(num_lines = len(lines)))

    game_log = GameLog()

    cursor = Cursor()
    # skip the GAME header
    cursor.advance(4)

    while (not self.lines[cursor.cursor].startswith('ENDGAME')):
      tick = self.read_tick(cursor)
      game_log.add_tick(tick)
    
    return game_log

  def read_tick(self, cursor):
    # read the STARTF line
    elements = self.get_elements(cursor)
    frame_index = int(elements[1])
    checksum = elements[2]
    tick = Tick(frame_index, checksum)
    cursor.advance()
    line = self.lines[cursor.cursor]

    while (not line.startswith('ENDTICK')):
      # todo: make the wait more obvious -- tick basically signifies a
      # wait for rift, so we return without advancing the cursor
      if line.startswith('TICK'):
        return tick
      if (line.startswith('ROLLTO')):
        self.read_rollto(cursor)
      elif (line.startswith('SYNC_RECV')):
        self.read_sync_recv(cursor)
      elif (line.startswith('SYNC_SEND')):
        self.read_sync_send(cursor)
      # tick simulation 
      elif (line.startswith('SIM')):
        self.read_sim(cursor)
      elif (line.startswith('ENDGAME')):
        return tick
      else:
        print('unsupported line: {}, {}'.format(line, cursor.cursor))
        raise(RuntimeError())
      line = self.lines[cursor.cursor]

    cursor.advance()
    return tick

  def get_elements(self, cursor):
    line = self.lines[cursor.cursor]
    return line.strip().split()

  def read_sim(self, cursor):
    # read the SIM line
    elements = self.get_elements(cursor)
    frame_index = int(elements[1])
    cursor.advance()

    start_checksum = self.get_elements(cursor)[1]
    cursor.advance()
    end_checksum = self.get_elements(cursor)[1]
    cursor.advance()

    p1_input = self.read_sim_input(cursor)
    p2_input = self.read_sim_input(cursor)

    sim_frame = SimFrame(frame_index, start_checksum, end_checksum, p1_input, p2_input)
    return sim_frame

  def read_sync_send(self, cursor):
    elements = self.get_elements(cursor)
    opcode = elements[0]
    player = elements[1]
    origin_frame = elements[2]
    num_inputs = int(elements[3])
    cursor.advance()
    self.read_sync_ack_and_inputs(cursor, num_inputs)
  
  def read_sim_input(self, cursor):
    elements = self.get_elements(cursor)
    cursor.advance()
    return elements[1]

  def read_rollto(self, cursor):
    elements = self.get_elements(cursor)
    target_frame = int(elements[1])
    target_checksum = elements[2]
    cursor.advance()

  def read_sync_recv(self, cursor):
    # read the SYNC_RECV line
    elements = self.get_elements(cursor)
    opcode = elements[0]
    player = elements[1]
    origin_frame = elements[2]
    num_inputs = int(elements[3])
    cursor.advance()
    self.read_sync_ack_and_inputs(cursor, num_inputs)

  def read_sync_ack_and_inputs(self, cursor, num_inputs):
    # read the ACK line
    elements = self.get_elements(cursor)
    ack = int(elements[1])
    cursor.advance()

    for i in range(num_inputs):
      elements = self.get_elements(cursor)
      frame_index = int(elements[0])
      input = elements[1] + ' ' + elements[2]
      cursor.advance()