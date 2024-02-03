#include <iostream>
#include <SDL.h>

#if 0
#define WINDOW_X 0
#define WINDOW_Y 0
#define WINDOW_Z 0
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#else
#define WINDOW_X 10
#define WINDOW_Y 20
#define WINDOW_Z 0
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#endif

#define GRID_SIZE 10
#define GRID_DIM 400

enum{
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};
struct snake
{
    int x;
    int y;
    int dir;

    struct snake * next;
};
typedef struct snake SNAKE;

SNAKE * head;
SNAKE * tail;

void INIT_SNAKE()
{
    SNAKE *new_snake = static_cast<SNAKE *>(malloc(sizeof(SNAKE)));
    new_snake -> x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new_snake -> y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new_snake -> dir = SNAKE_UP;
    new_snake -> next = NULL;

    head = new_snake;
    tail = new_snake;

    return;
}

void increase_snake()
{
    SNAKE * new_snake = static_cast<SNAKE *>(malloc(sizeof(SNAKE)));
    new_snake -> x = tail -> x;
    new_snake -> y = tail -> y - 1;
    new_snake -> dir = tail -> dir;

    new_snake -> next = NULL;
    tail -> next = new_snake;
    tail = new_snake;

}

void move_snake()
{

    int prev_x = head -> x;
    int prev_y = head -> y;

    switch(head -> dir)
    {
        case SNAKE_UP:
            head -> y--;
            break;
        case SNAKE_DOWN:
            head -> y++;
            break;
        case SNAKE_LEFT:
            head -> x--;
            break;
        case SNAKE_RIGHT:
            head -> x++;
            break;
    }

    SNAKE  *track = head;

    if(track -> next != NULL)
        track = track -> next;

    while(track != NULL)
    {
        int save_x = track -> x;
        int save_y = track -> y;

        track -> x = prev_x;
        track -> y = prev_y;

        track = track -> next;

        prev_x = save_x;
        prev_y = save_y;
    }

    return;
}

void render_snake(SDL_Renderer * renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size;
    seg.h = seg_size;

    SNAKE *track = head;

    while(track != NULL)
    {
        seg.x = x + track -> x * seg_size;
        seg.y = y + track -> y * seg_size;

        SDL_RenderFillRect(renderer, &seg);

        track = track -> next;
    }

    return;
}

void render_grid(SDL_Renderer * renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 255);

    int cell_size =  GRID_DIM / GRID_SIZE;

    SDL_Rect cell;

    cell.w = cell_size;
    cell.h = cell_size;

    for(int i = 0; i < GRID_SIZE; i++)
    {
        for(int j = 0; j < GRID_SIZE; j++)
        {
            cell.x = x + (i * cell_size);
            cell.y = y + (j * cell_size);

            SDL_RenderDrawRect(renderer, &cell);
        }
    }
    return;
}

void reset_snake()
{
    SNAKE * track = head;
    SNAKE * temp;

    while(track != NULL)
    {
        temp = track;
        track = track -> next;
        free(temp);
    }

    INIT_SNAKE();
    increase_snake();

}


int main(int argc, char *argv[]) {

    INIT_SNAKE();
    increase_snake();
    increase_snake();


    SDL_Window *window;
    SDL_Renderer * renderer;

    if(SDL_INIT_VIDEO < 0)
    {

    }

    window = SDL_CreateWindow("SNAKE",
                              WINDOW_X, WINDOW_Y,
                              WINDOW_WIDTH, WINDOW_HEIGHT,
                              SDL_WINDOW_BORDERLESS);

    if(!window) fprintf(stderr, "EROARE");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!renderer) fprintf(stderr, "EROARE");

    int grid_x = (WINDOW_WIDTH / 2) - (GRID_DIM / 2);
    int grid_y = (WINDOW_HEIGHT / 2) - (GRID_DIM / 2);

    bool quit = false;
    SDL_Event event;

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_UP:
                            head -> dir = SNAKE_UP;
                            break;
                        case SDLK_DOWN:
                            head -> dir = SNAKE_DOWN;
                            break;
                        case SDLK_LEFT:
                            head -> dir = SNAKE_LEFT;
                            break;
                        case SDLK_RIGHT:
                            head -> dir = SNAKE_RIGHT;
                            break;
                    }
                    break;
            }
        }
        SDL_RenderClear(renderer);

        move_snake();

        render_grid(renderer, grid_x, grid_y);
        render_snake(renderer, grid_x, grid_y);

        SDL_SetRenderDrawColor(renderer, 0x11, 0x11, 0x11, 255);
        SDL_RenderPresent(renderer);

        SDL_Delay(200);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}

