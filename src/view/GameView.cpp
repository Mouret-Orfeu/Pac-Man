#include "GameView.h"
#include "model/GameModel.h"
#include "model/Character.h"
#include "model/Ghost.h"

#include <SDL.h>
#include <iostream>


GameView::GameView(GameModel& gameModel) : gameModel(gameModel) {
    // Initialize game view related data here
	pWindow = SDL_CreateWindow("PacMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH , WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	win_surf = SDL_GetWindowSurface(pWindow);

    //On utilise des sprites venant des ces 2 fichiers
	spriteSheet_NES = SDL_LoadBMP("./assets/pacman_sprites_NES.bmp");
    spriteSheet_Namco = SDL_LoadBMP("./assets/pacman_sprites_Namco.bmp");

    if ((!spriteSheet_NES) || (!spriteSheet_Namco)) {
        // Handle error loading bitmap
        std::cerr << "Failed to load bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    spriteSheet_Namco_formatted = SDL_ConvertSurface(spriteSheet_Namco, win_surf->format, 0);

    // if (SDL_SaveBMP(spriteSheet_Namco_formatted, "pacman_sprites_Namco_formatted.bmp") != 0) {
    //     // handle error
    //     std::cerr << "Failed to save bitmap: " << SDL_GetError() << std::endl;
    //     SDL_Quit();
    //     exit(1);
    // }

    if(!spriteSheet_Namco_formatted) {
        // Handle error converting bitmap
        std::cerr << "Failed to convert bitmap: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(pWindow);
        SDL_Quit();
        exit(1);
    }

    //DEBUG
    //grid_surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
    //SDL_FillRect(grid_surface, NULL, SDL_MapRGB(grid_surface->format, 255, 0, 0)); // fill grid surface with red color
}

GameView::~GameView() {
    // Clean up game view related data here
    SDL_FreeSurface(spriteSheet_NES);
    SDL_FreeSurface(spriteSheet_Namco);
    SDL_FreeSurface(spriteSheet_Namco_formatted);
    SDL_DestroyWindow(pWindow);
}

void GameView::draw() {
    renderMaze();
    renderHUD();
    render(gameModel.getGhost());
    render(gameModel.getPacMan());

	SDL_UpdateWindowSurface(pWindow);
}

void GameView::draw_death(int death_sprite_count) {
    renderMaze();
    renderHUD();

    switch (death_sprite_count)
    {
        case 0:
            displayPacmanDeath(0);
            break;
        case 1:
            displayPacmanDeath(1);
            break;
        case 2:
            displayPacmanDeath(2);
            break;
        case 3:
            displayPacmanDeath(3);
            break;
        case 4:
            displayPacmanDeath(4);
            break;
        case 5:
            break;
            displayPacmanDeath(5);
        case 6:
            displayPacmanDeath(6);
            break;
        case 7:
            displayPacmanDeath(7);
            break;
        case 8:
            displayPacmanDeath(8);
            break;
        case 9:
            displayPacmanDeath(9);
            break;
        case 10:
            displayPacmanDeath(10);
            break;
        case 11:
            displayPacmanDeath(11);
            break;
        default:
            break;
    }




	SDL_UpdateWindowSurface(pWindow);
}

void GameView::render(const Ghost& ghost) {
    // petit truc pour faire tourner le fantome
    SDL_Rect ghost_sprite;
    Ghost::State state = ghost.getState();
    switch (state.direction) {
        case Ghost::Direction::RIGHT:
            ghost_sprite = Blinky_sprite_r;
            break;
        case Ghost::Direction::DOWN:
            ghost_sprite = Blinky_sprite_d;
            break;
        case Ghost::Direction::LEFT:
            ghost_sprite = Blinky_sprite_l;
            break;
        case Ghost::Direction::UP:
            ghost_sprite = Blinky_sprite_u;
            break;
    }

    // ici on change entre les 2 sprites sources pour une jolie animation.
    if ((gameModel.getCount() / 4) % 2) {
        ghost_sprite.x += 16;
    }

    renderSprite(spriteSheet_Namco_formatted, &ghost_sprite, getTopLeftPosition(state.center_position, SIZE_GHOST_SPRITE), true);
}

void GameView::render(const PacMan& pacman) {
    // petit truc pour faire tourner le fantome
    SDL_Rect pacman_sprite_in;
    PacMan::State state = pacman.getState();
    switch (state.direction) {
        case PacMan::Direction::RIGHT:
            pacman_sprite_in = pacman_sprite_r;
            break;
        case PacMan::Direction::DOWN:
            pacman_sprite_in = pacman_sprite_d;
            break;
        case PacMan::Direction::LEFT:
            pacman_sprite_in = pacman_sprite_l;
            break;
        case PacMan::Direction::UP:
            pacman_sprite_in = pacman_sprite_u;
            break;
        case PacMan::Direction::NONE:
            // TODO: set sprite to round sprite
            pacman_sprite_in = pacman_sprite_r;
            break;
    }

    // // ici on change entre les 2 sprites sources pour une jolie animation.
    // if ((gameModel.getCount() / 4) % 2) {
    //     pacman_sprite_in.x += 17;
    // }

    renderSprite(spriteSheet_Namco_formatted, &pacman_sprite_in, getTopLeftPosition(state.center_position, SIZE_PACMAN_SPRITE), true);

    TileOutline(win_surf, state.tile_position);
}

void GameView::renderMaze() {
    renderSprite(spriteSheet_Namco_formatted, &maze_Namco, {0,3*TILE_SIZE}, false);
}

// void GameView::renderHUD() {
//     // Score
//     renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({5*TILE_SIZE,TILE_SIZE}), true);
//     renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({6*TILE_SIZE,TILE_SIZE}), true);

//     // 1UP
//     renderSprite(spriteSheet_NES, &one_sprite, SDL_Point({3*TILE_SIZE,0}), true);
//     renderSprite(spriteSheet_NES, &U_sprite, SDL_Point({4*TILE_SIZE,0}), true);
//     renderSprite(spriteSheet_NES, &P_sprite, SDL_Point({5*TILE_SIZE,0}), true);

//     // Lives
//     renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({2*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
//     renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({4*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
//     renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({6*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
// }

void GameView::renderHUD() {
    SDL_SetColorKey(spriteSheet_NES, true, 0);

    // Score
    int score = gameModel.getScore();
    int highscore = gameModel.getHighScore();
    int lives = gameModel.getLives();
    drawScore(score, false);
    drawScore(highscore, true);
    drawLives(lives);
    drawText();
}


void GameView::renderSprite(SDL_Surface* sprite_sheet, const SDL_Rect* sprite, SDL_Point top_left_position, bool transparency) {
    // Set the black pixels transparency
    SDL_SetColorKey(sprite_sheet, transparency, 0);
    // Create an upscaled sprite at the right position
    int w, h;
    if (sprite != NULL) {
        w = sprite->w;
        h = sprite->h;
    } else {
        w = sprite_sheet->w;
        h = sprite_sheet->h;
    }
    SDL_Rect sprite_out = {UPSCALING_FACTOR*top_left_position.x, UPSCALING_FACTOR*top_left_position.y, UPSCALING_FACTOR*w, UPSCALING_FACTOR*h};
    // Copy the upscaled sprite to the window surface
    if(SDL_BlitScaled(sprite_sheet, sprite, win_surf, &sprite_out)<0){
        printf("SDL_BlitScaled failed: %s\n", SDL_GetError());
    }
}

SDL_Point GameView::computeCenterPosition(SDL_Point top_left_position, int size) {
    return {top_left_position.x+(size-1)/2, top_left_position.y+(size-1)/2};
}

SDL_Point GameView::computeTilePosition(SDL_Point top_left_position, int size) {
    SDL_Point center_position = computeCenterPosition(top_left_position, size);
    return {center_position.x/8, center_position.y/8};
}

SDL_Point GameView::getCoordCenterTile(SDL_Point tile_pos) {
    return {tile_pos.x*8+4, tile_pos.y*8+4};
}

SDL_Point GameView::getTopLeftPosition(SDL_Point position, int size) {
    return {position.x-(size-1)/2, position.y-(size-1)/2};
}

//DEBUG
void GameView::TileOutline(SDL_Surface* win_surf, SDL_Point tile_position) {
    int x = tile_position.x*TILE_SIZE,
        y = tile_position.y*TILE_SIZE;
    // Create a new surface with the square outline
    SDL_Surface* redSquare = SDL_CreateRGBSurface(0, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(redSquare, NULL, SDL_MapRGB(redSquare->format, 255, 0, 0));
    SDL_Rect blackSquare = { 1,1, 6,6 };
    SDL_FillRect(redSquare, &blackSquare, SDL_MapRGB(redSquare->format, 0, 0, 0));

    // Copy the square outline onto the main surface
    // SDL_Rect destRect = { x,y, 8,8 };
    SDL_SetColorKey(redSquare, true, 0);
    renderSprite(redSquare, NULL, {x,y}, true);
    // SDL_BlitSurface(redSquare, NULL, win_surf, &destRect);

    // Free the temporary surface
    SDL_FreeSurface(redSquare);
}

//DEBUG
void GameView::drawAllTileOutlines() {
    for(int i = 0; i < 28; i++)
        for (int j = 0; j < 36; j++)
            TileOutline(win_surf, {i,j});
}

void GameView::drawScore(int score, bool highscore)
{
    if (score==0) {
        if (highscore) {
            return;
        } else {
            //si le score est 0 j'affiche 00
            renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({6*TILE_SIZE,1*TILE_SIZE}), true);
            renderSprite(spriteSheet_NES, &zero_sprite, SDL_Point({5*TILE_SIZE,1*TILE_SIZE}), true);
        }
    }

    // Convert the score to a string
    std::string scoreString = std::to_string(score);

    //position en nombre de tile du nombre
    int pos=MAX_SCORE_DIGITS-1;

    if (highscore)
        pos+=11;

    // Loop through the characters in the score string
    for (int i = scoreString.length()-1; i>-1 ; i--)
    {
        // Get the sprite for the current digit
        SDL_Rect sprite;
        switch (scoreString[i])
        {
            case '0':
                sprite = zero_sprite;
                break;
            case '1':
                sprite = one_sprite;
                break;
            case '2':
                sprite = two_sprite;
                break;
            case '3':
                sprite = three_sprite;
                break;
            case '4':
                sprite = four_sprite;
                break;
            case '5':
                sprite = five_sprite;
                break;
            case '6':
                sprite = six_sprite;
                break;
            case '7':
                sprite = seven_sprite;
                break;
            case '8':
                sprite = eight_sprite;
                break;
            case '9':
                sprite = nine_sprite;
                break;
            default:
                sprite = zero_sprite;
                break;
        }

        renderSprite(spriteSheet_NES, &sprite, SDL_Point({pos*TILE_SIZE,1*TILE_SIZE}), true);

        pos--;
    }
}

void GameView::drawText()
{
    // "High Score"
    // SDL_BlitScaled(spriteSheet_NES, &H_sprite, win_surf, &H1_high_score_pos);
    renderSprite(spriteSheet_NES, &H_sprite, SDL_Point({10*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &I_sprite, win_surf, &I_high_score_pos);
    renderSprite(spriteSheet_NES, &I_sprite, SDL_Point({11*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &G_sprite, win_surf, &G_high_score_pos);
    renderSprite(spriteSheet_NES, &G_sprite, SDL_Point({12*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &H_sprite, win_surf, &H2_high_score_pos);
    renderSprite(spriteSheet_NES, &H_sprite, SDL_Point({13*TILE_SIZE, 0}), true);

    // SDL_BlitScaled(spriteSheet_NES, &S_sprite, win_surf, &S_high_score_pos);
    renderSprite(spriteSheet_NES, &S_sprite, SDL_Point({15*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &C_sprite, win_surf, &C_high_score_pos);
    renderSprite(spriteSheet_NES, &C_sprite, SDL_Point({16*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &O_sprite, win_surf, &O_high_score_pos);
    renderSprite(spriteSheet_NES, &O_sprite, SDL_Point({17*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &R_sprite, win_surf, &R_high_score_pos);
    renderSprite(spriteSheet_NES, &R_sprite, SDL_Point({18*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &E_sprite, win_surf, &E_high_score_pos);
    renderSprite(spriteSheet_NES, &E_sprite, SDL_Point({19*TILE_SIZE, 0}), true);

    // 1UP
    // SDL_BlitScaled(spriteSheet_NES, &one_sprite, win_surf, &one_up_one_pos);
    renderSprite(spriteSheet_NES, &one_sprite, SDL_Point({3*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &U_sprite, win_surf, &one_up_U_pos);
    renderSprite(spriteSheet_NES, &U_sprite, SDL_Point({4*TILE_SIZE, 0}), true);
    // SDL_BlitScaled(spriteSheet_NES, &P_sprite, win_surf, &one_up_P_pos);
    renderSprite(spriteSheet_NES, &P_sprite, SDL_Point({5*TILE_SIZE, 0}), true);
}

void GameView::drawLives(int lives)
{
    switch (lives)
    {
        case 3:
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &first_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({2*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &second_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({4*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &third_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({6*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            break;
        case 2:
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &first_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({2*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &second_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({4*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            break;
        case 1:
            // SDL_BlitScaled(spriteSheet_Namco_formatted, &life_sprite, win_surf, &first_life_pos);
            renderSprite(spriteSheet_Namco_formatted, &life_sprite, SDL_Point({2*TILE_SIZE+3,GameModel::HEIGHT-2*TILE_SIZE+2}), true);
            break;
        case 0:
            break;
        default:
            break;

    }
}

void GameView::displayPacmanDeath(int death_frame)
{

    SDL_Point position = getTopLeftPosition(gameModel.getPacMan().getCenterPosition(), SIZE_PACMAN_SPRITE);
    // SDL_Rect dest = { position.x, position.y, SIZE_PACMAN_SPRITE_RESIZED, SIZE_PACMAN_SPRITE_RESIZED };

   switch (death_frame) {
    case 1:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_1, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_1, position, true);
        break;
    case 2:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_2, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_2, position, true);
        break;
    case 3:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_3, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_3, position, true);
        break;
    case 4:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_4, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_4, position, true);
        break;
    case 5:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_5, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_5, position, true);
        break;
    case 6:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_6, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_6, position, true);
        break;
    case 7:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_7, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_7, position, true);
        break;
    case 8:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_8, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_8, position, true);
        break;
    case 9:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_9, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_9, position, true);
        break;
    case 10:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_10, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_10, position, true);
        break;
    case 11:
        // SDL_BlitScaled(spriteSheet_Namco_formatted, &pacman_death_sprite_11, win_surf, &dest);
        renderSprite(spriteSheet_Namco_formatted, &pacman_death_sprite_11, position, true);
        break;
    case 12:
        break;
    default:
        std::cout<<"Error: invalid death frame"<<std::endl;
        break;
    }

    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(100);

}
