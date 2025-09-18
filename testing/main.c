#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define NUMBER_PARTICLES 100 // 100

typedef struct {
  int x;
  int y;
  int lastX;
  int lastY;
  int velocityX;
  int velocityY;
} PARTICLE;

void render(char **space, int WIDTH, int HEIGHT) {
  system("clear");
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      printf("%c", space[y][x]);
    }
    printf("\n");
  }
}

void updateParticles(PARTICLE *particles, int WIDTH, int HEIGHT) {
  for (int i = 0; i < NUMBER_PARTICLES; i++) {
    PARTICLE p = particles[i];

    p.lastX = p.x;
    p.lastY = p.y;
    p.x = p.x + p.velocityX;
    p.y = p.y + p.velocityY;

    if (p.x <= 0 || p.x >= WIDTH - 1) {
      p.velocityX *= -1;
    }

    if (p.y <= 0 || p.y >= HEIGHT - 1) {
      p.velocityY *= -1;
    }

    particles[i] = p;
  }
}

void update2DSpace(PARTICLE *particles, char **space) {
  for (int i = 0; i < NUMBER_PARTICLES; i++) {
    PARTICLE p = particles[i];

    space[p.y][p.x] = '*';
  }
}

char** create2DSpace(int WIDTH, int HEIGHT) {
  char **space = malloc(HEIGHT * sizeof(char*));
  if (space == NULL) {
    perror("Failed to allocate space");
    return NULL;
  }

  for (int i = 0; i < HEIGHT; i++) {

    space[i] = malloc(WIDTH * sizeof(char));
    
    if (space[i] == NULL) {
      perror("Failed to allocate space");
    
      for (int j = 0; j < HEIGHT; j++) {
        free(space[i]);
      }
    
      free(space);
    
      return NULL;
    }
  }

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      space[i][j] = ' ';
    }
  }

  return space;
}

PARTICLE* generateParticles(int WIDTH, int HEIGHT) {
  PARTICLE *particles = malloc(NUMBER_PARTICLES * sizeof(PARTICLE));

  if (particles == NULL) {
    perror("Failed to allocate memory for particles");
    return NULL;
  }
  int blockWidth = sqrt((float) NUMBER_PARTICLES);

  int index = 0;
  for (int i = -(blockWidth / 2); i < blockWidth / 2; i++) {
    for (int j = -(blockWidth / 2); j < blockWidth / 2; j++) {
      // printf("%d - (%d, %d)\n", index, WIDTH / 2 + i, HEIGHT / 2 + j);
      PARTICLE p = {WIDTH / 2 + i, HEIGHT / 2 + j, WIDTH / 2 + i, HEIGHT / 2 + j, -1, 1};
      particles[index] = p;
      index++;
    }
  }

  return particles;
}

int main(void) {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int HEIGHT = w.ws_row;
  int WIDTH = w.ws_col;

  char **space = create2DSpace(WIDTH, HEIGHT);

  PARTICLE *particles = generateParticles(WIDTH, HEIGHT);
  
  // return 0;
  int micro = 100000;

  while (1) {
    updateParticles(particles, WIDTH, HEIGHT);
    // space = create2DSpace(WIDTH, HEIGHT); // resset grid space
    update2DSpace(particles, space);
    render(space, WIDTH, HEIGHT);
    usleep(0.5 * micro);
  }

  return 0;
}