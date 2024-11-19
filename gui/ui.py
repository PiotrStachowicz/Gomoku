import sys
import pygame
import fcntl
import os
import numpy as np
import struct

# Window settings
WINDOW_WIDTH = 1200
WINDOW_HEIGHT = 1200
MARGIN = 200
BOARD_SIZE = int(sys.argv[1])
turn = int(sys.argv[2])
SQUARE_SIZE = (WINDOW_HEIGHT - MARGIN - MARGIN) // BOARD_SIZE
HUMAN_ID = 1
COMPUTER_ID = 42

# Colours
BACKGROUND_COLOUR = (255, 253, 208)
BOARD_COLOUR = (217, 186, 140)
GRID_COLOUR = (211, 211, 211)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Setup
pygame.init()
pygame.font.init()
font = pygame.font.SysFont('Comic Sans MS', 30)
screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
clock = pygame.time.Clock()
execute = True

if turn == HUMAN_ID:
  can_play = True
else:
  can_play = False
  
pygame.display.set_caption("Gomoku")

board = [[0 for _ in range(BOARD_SIZE)] for _ in range(BOARD_SIZE)]

# Setup non-blocking communication
fd = sys.stdin.fileno()
flags = fcntl.fcntl(fd, fcntl.F_GETFL)
fcntl.fcntl(fd, fcntl.F_SETFL, flags | os.O_NONBLOCK)

# Clear pygame trash in socket's buffer
sys.stdout.write('trash')
sys.stdout.flush()


# Retrieve user input
def get_user_move(event):
  y, x = event.pos
  col = (x - MARGIN) // SQUARE_SIZE
  row = (y - MARGIN) // SQUARE_SIZE
  
  return row, col

# Draw board
def draw_board():        
  # Board
  pygame.draw.rect(screen, BOARD_COLOUR, (MARGIN, MARGIN, BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE))
  
  # Grid lines
  for i in range(0, BOARD_SIZE):
    text = font.render(str(i + 1), False, BLACK)
    screen.blit(text, (MARGIN - 5 + i * SQUARE_SIZE + SQUARE_SIZE // 2, MARGIN - 30))
    pygame.draw.line(screen, BLACK, (MARGIN + i * SQUARE_SIZE + SQUARE_SIZE // 2, MARGIN), (MARGIN + i * SQUARE_SIZE + SQUARE_SIZE // 2, WINDOW_HEIGHT - MARGIN))
  
  for i in range(0, BOARD_SIZE):
    text = font.render(str(i + 1), False, BLACK)
    screen.blit(text, (MARGIN - 30, MARGIN - 10 + i * SQUARE_SIZE + SQUARE_SIZE // 2))
    pygame.draw.line(screen, BLACK, (MARGIN, MARGIN + i * SQUARE_SIZE + SQUARE_SIZE // 2), (WINDOW_WIDTH - MARGIN, MARGIN + i * SQUARE_SIZE + SQUARE_SIZE // 2))
    
  # Players
  for row in range(BOARD_SIZE):
    for col in range(BOARD_SIZE):
      if board[row][col] == HUMAN_ID:
        pygame.draw.circle(screen, WHITE, (MARGIN + row * SQUARE_SIZE + SQUARE_SIZE // 2, MARGIN + col * SQUARE_SIZE + SQUARE_SIZE // 2), SQUARE_SIZE // 4)
      elif board[row][col] == COMPUTER_ID:
        pygame.draw.circle(screen, BLACK, (MARGIN + row * SQUARE_SIZE + SQUARE_SIZE // 2, MARGIN + col * SQUARE_SIZE + SQUARE_SIZE // 2), SQUARE_SIZE // 4)
      

# Main loop of the game
while execute:
  # Fill background
  screen.fill(BACKGROUND_COLOUR)
  
  # Check for events
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      execute = False
    if event.type == pygame.MOUSEBUTTONDOWN:
      if event.button == 1 and can_play:
        row, col = get_user_move(event)
        
        if (BOARD_SIZE > col >= 0 and BOARD_SIZE > row >= 0):
          packed_data = struct.pack('ii', row, col) 
          
          if board[row][col] == 0:
            can_play = False
            board[row][col] = HUMAN_ID
            if sys.stdout.buffer.write(packed_data) == -1:
              exit(1)
            sys.stdout.flush()
      
  # Read computer output
  computer_move = sys.stdin.read(8)

  if computer_move:
    computer_move_bytes = computer_move.encode('utf-8')
    coordinates = np.frombuffer(computer_move_bytes, dtype=np.int32)
    x = coordinates[0]
    y = coordinates[1]
    board[y][x] = COMPUTER_ID
    can_play = True
  
  draw_board()
  pygame.display.flip()
  
  # 10 FPS
  clock.tick(10)
  