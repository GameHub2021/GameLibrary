#include <SDL.h>
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstring>
#include <thread>
#include <chrono>
#include <time.h>
#include <windows.h>
#include <random>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <string>
#include <algorithm>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = nullptr;

SDL_Texture* playerTexture;
SDL_Texture* obstTexture;

SDL_Texture* GroundTexture;                     // 땅 객체 선언
SDL_Rect Ground_rect;

SDL_Texture* BackgroundTexture;                 // 배경 객체 선언
SDL_Rect Background_rect;

SDL_Rect playerRect;

vector<SDL_Rect> obstacles;
vector<SDL_Rect> apples;
SDL_Texture* Obst_texture;          //상하단 장애물 객체 선언
SDL_Rect Obst_destination_rect1_UP;
SDL_Rect Obst_destination_rect2_UP;
SDL_Rect Obst_destination_rect3_UP;
SDL_Rect Obst_destination_rect4_UP;

SDL_Rect Obst_destination_rect1_DO;
SDL_Rect Obst_destination_rect2_DO;
SDL_Rect Obst_destination_rect3_DO;
SDL_Rect Obst_destination_rect4_DO;

SDL_Texture* appleTexture;                // 아이템 사과 객체 선언
SDL_Rect Apple_rect;

SDL_Texture* Apple_texture;
SDL_Texture* F_Obst_texture;        // 날아오는 장애물 객체 선언
SDL_Rect F_Obst_destination_rect;

SDL_Texture* Skill_Effect_texture;    // 스킬 이펙트 객체 선언 
SDL_Rect Skill_Effect_destination_rect;

SDL_Texture* AppleTree_texture;    // 스킬 이펙트 객체 선언 
SDL_Rect AppleTree_destination_rect;

//function
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file);
SDL_Texture* loadTexture_Obst(SDL_Renderer* renderer, const char* file);
SDL_Texture* loadTexture_F_Obst(SDL_Renderer* renderer, const char* file);
SDL_Texture* loadTexture_Apple(SDL_Renderer* renderer, const char* file);
SDL_Texture* loadTexture_Skill_Effect(SDL_Renderer* renderer, const char* file);
SDL_Texture* loadTexture_AppleTree(SDL_Renderer* renderer, const char* file);

int minutes, seconds;
int num1;
int num2 = 0;
int level = 0;
int repulsion_effect = 0;                                                   // 척력 작용 여부 판단 변수
int player_motion = 0;                                                      // 플레이어 달리는 장면 애니메이션 변수
int player_jump_motion = 0;                                                 // 플레이어 모션 애니메이션 변수
int playermotion_count = 0;                                                 // 애니메이션 주기 변수
bool jump_count = 0;                                                        // 플레이어 점프 여부 변수
int playerjumpmotion_count = 0;                                             // 점프 애니메이션 주기 변수
int Skill_Effect_Y = 0;                                                     // 스킬 효과 Y좌표 변수
int skill_effect_count = 0;                                                 // 스킬 효과 주기 변수
int skill_effect_number = 0;                                                // 스킬 효과 종류 변수
bool ending = 0;                                                            // 엔딩 변수
int Apple_count = 0;                                                        // 사과와 접촉했을 때 능력 강화 수치 변수



const int screen_x = 640; // 화면 가로
const int screen_y = 400; // 화면 세로
const float start_x = screen_x / 4, start_y = screen_y - 90;
const float gravity = 0.120f;
const float jump_speed = -5.0f;


SDL_Texture* loadTexture_Obst(SDL_Renderer* renderer, const char* file)          // 장애물 이미지 업로드
{
    SDL_Surface* surface;
    surface = IMG_Load(file);

    if (surface == NULL)
    {
        printf("fail to read %s\n", file);
        return NULL;
    }

    Obst_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (Obst_texture == NULL)
        printf("unable to create texture.\n");

    SDL_FreeSurface(surface);
    return Obst_texture;
}

SDL_Texture* loadTexture_F_Obst(SDL_Renderer* renderer, const char* file)          // 날아오는 장애물 이미지 업로드
{
    SDL_Surface* surface;
    surface = IMG_Load(file);

    if (surface == NULL)
    {
        printf("fail to read %s\n", file);
        return NULL;
    }

    F_Obst_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (F_Obst_texture == NULL)
        printf("unable to create texture.\n");

    F_Obst_destination_rect.x = 850;
    if (num2 % 2 == 1)                          // 3개 장애물 출현 시 50% 확률로 날아오는 장애물 타이밍 연기
        F_Obst_destination_rect.x = 1100;
    F_Obst_destination_rect.y = 175;
    F_Obst_destination_rect.w = 50;
    F_Obst_destination_rect.h = 50;
    SDL_FreeSurface(surface);
    return F_Obst_texture;
}

SDL_Texture* loadTexture_Skill_Effect(SDL_Renderer* renderer, const char* file)          // 스킬 효과 이미지 업로드
{
    SDL_Surface* surface;
    surface = IMG_Load(file);

    if (surface == NULL)
    {
        printf("fail to read %s\n", file);
        return NULL;
    }

    Skill_Effect_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (Skill_Effect_texture == NULL)
        printf("unable to create texture.\n");

    Skill_Effect_destination_rect.x = 100;
    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
    Skill_Effect_destination_rect.w = 55;
    Skill_Effect_destination_rect.h = 55;
    SDL_FreeSurface(surface);
    return Skill_Effect_texture;
}
SDL_Texture* loadTexture_Apple(SDL_Renderer* renderer, const char* file)          //사과 이미지 업로드
{
    SDL_Surface* surface;
    surface = IMG_Load(file);

    if (surface == NULL)
    {
        printf("fail to read %s\n", file);
        return NULL;
    }

    Apple_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (Apple_texture == NULL)
        printf("unable to create apple texture.\n");

    Apple_rect.x = 650;
    Apple_rect.y = 125;
    Apple_rect.w = 50;
    Apple_rect.h = 50;
    SDL_FreeSurface(surface);
    return Apple_texture;
}

SDL_Texture* loadTexture_AppleTree(SDL_Renderer* renderer, const char* file)          // 사과나무 이미지 업로드
{
    SDL_Surface* surface;
    surface = IMG_Load(file);

    if (surface == NULL)
    {
        printf("fail to read %s\n", file);
        return NULL;
    }

    AppleTree_texture = SDL_CreateTextureFromSurface(renderer, surface);

    if (AppleTree_texture == NULL)
        printf("unable to create texture.\n");

    AppleTree_destination_rect.x = 310;
    AppleTree_destination_rect.y = 170;
    AppleTree_destination_rect.w = 200;
    AppleTree_destination_rect.h = 200;
    SDL_FreeSurface(surface);
    return AppleTree_texture;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, std::string text, int x, int y) {
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }
    else {
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cerr << "Unable to create texture from rendered text! SDL_Error: " << SDL_GetError() << std::endl;
        }
        else {
            SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

SDL_Texture* renderText(const char* message, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer) {
    TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
    if (font == NULL) {
        printf("TTF_OpenFont Error: %s\n", TTF_GetError());
        return NULL;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, message, color);
    if (surface == NULL) {
        printf("TTF_RenderText_Solid Error: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        printf("SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    TTF_CloseFont(font);

    return texture;
}

void player_motion_count(int n = 0)
{
    playermotion_count += n;

    if (playermotion_count % 10 == 0)
        player_motion += 1;
}

void player_jump_motion_count(int n = 0)
{
    playerjumpmotion_count += n;

    if (playerjumpmotion_count % 23 == 0)
        player_jump_motion += 1;
}


// Object 클래스: 뉴턴 객체
class Object {
public:
    float x, y;     // 위치
    float vx, vy;   // 속도

    Object(float x, float y) : x(x), y(y), vx(0.0f), vy(0.0f) {} // 생성자

    void applyGravity(float gravity) {
        vy += gravity;
        y += vy;
    }
    void render(SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_Rect dstRect = { static_cast<int>(x), static_cast<int>(y), 45, 60 }; // 임의의 크기 설정

        switch (player_motion % 3)
        {
        case 0:
            playerTexture = loadTexture(renderer, "player1.png");
            player_motion_count(1);
            break;
        case 1:
            playerTexture = loadTexture(renderer, "player2.png");
            player_motion_count(1);
            break;
        case 2:
            playerTexture = loadTexture(renderer, "player3.png");
            player_motion_count(1);
            break;
        case 3:
            playerTexture = loadTexture(renderer, "player4.png");
            player_motion_count(1);
            break;
        }

        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }

    void jump_render(SDL_Renderer* renderer, SDL_Texture* texture) {
        SDL_Rect dstRect = { static_cast<int>(x), static_cast<int>(y - 20), 45, 60 }; // 임의의 크기 설정

        switch (player_jump_motion % 4)
        {
        case 0:
            playerTexture = loadTexture(renderer, "player_jump1.png");
            player_jump_motion_count(1);
            break;
        case 1:
            playerTexture = loadTexture(renderer, "player_jump2.png");
            player_jump_motion_count(1);
            break;
        case 2:
            playerTexture = loadTexture(renderer, "player_jump3.png");
            player_jump_motion_count(1);
            break;
        case 3:
            playerTexture = loadTexture(renderer, "player_jump4.png");
            player_jump_motion_count(1);
            break;
        case 4:
            playerTexture = loadTexture(renderer, "player_jump5.png");
            player_jump_motion_count(1);
            break;
        }

        SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    }

    void jump(float jumpSpeed) {
        vy = jumpSpeed;
    }
    void move() {
        x += vx;
        y += vy;
    }

    void resetPosition(float startY) {
        y = startY;
        vy = 0.0f;
    }

    bool isOnGround(float groundY) const {
        return y >= groundY;
    }
};

bool crashObs()
{
    return (SDL_HasIntersection(&Apple_rect, &F_Obst_destination_rect) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect1_UP) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect2_UP) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect3_UP) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect4_UP) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect1_DO) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect2_DO) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect3_DO) || SDL_HasIntersection(&Apple_rect, &Obst_destination_rect4_DO));
}
bool isPositive(bool x) {
    return x == true;
}
bool crashplayer(const Object& obj)
{
    SDL_Rect objRect = { static_cast<int>(obj.x), static_cast<int>(obj.y), 45, 60 };
    return (SDL_HasIntersection(&Apple_rect, &objRect));
}
class Apple {
private:
    SDL_Texture* Ap;
    bool active;
    vector<bool> ox;
    vector<bool> oxp;
public:

    Apple() {
        Ap = loadTexture_Apple(renderer, "apple.png");

    };
    bool isOutOfScreen() {
        return Apple_rect.x < 0;
    }
    void fly_apple(const Object& obj) {
        ox.push_back(crashObs());
        ox.push_back(crashplayer(obj));
        if (!any_of(ox.begin(), ox.end(), isPositive)) //하나라도 부딪히지 않았다면
        {
            SDL_RenderCopy(renderer, Ap, NULL, &Apple_rect);
        }
        if (crashplayer(obj))
        {
            Apple_rect.y -= 1000;
            Apple_count += 1;
        }
        Apple_rect.x -= 2;
    }
};


class Obstacle                  //장애물 클래스
{
    SDL_Texture* Obst;
    SDL_Texture* F_Obst;

public:
    Obstacle();
    void UP_Obst(int n);             // 상단 장애물
    void DO_Obst(int n);             // 하단 장애물
    void Obstacle_make_UP();            // 상단 장애물 생성 함수
    void Obstacle_make_DO();            // 하단 장애물 생성 함수
    void Fly_Obst();                 // 날아가는 장애물
};

Obstacle::Obstacle()
{
    Obst = loadTexture_Obst(renderer, "Obst_ver2.png");
    F_Obst = loadTexture_F_Obst(renderer, "Obst_ver2.png");
}

void Obstacle::UP_Obst(int n)               // 상단 장애물 종류 및 x, y축 값 설정
{
    switch (n % 4)
    {
    case 0:
        Obst_destination_rect1_UP.x = 650;
        Obst_destination_rect1_UP.y = 50;
        Obst_destination_rect1_UP.w = 50;
        Obst_destination_rect1_UP.h = 50;

        Obst_destination_rect2_UP.x = 700;
        Obst_destination_rect2_UP.y = 50;
        Obst_destination_rect2_UP.w = 50;
        Obst_destination_rect2_UP.h = 50;

        Obst_destination_rect3_UP.x = 750;
        Obst_destination_rect3_UP.y = 50;
        Obst_destination_rect3_UP.w = 50;
        Obst_destination_rect3_UP.h = 50;

        Obst_destination_rect4_UP.x = 650;
        Obst_destination_rect4_UP.y = 100;
        Obst_destination_rect4_UP.w = 50;
        Obst_destination_rect4_UP.h = 50;
        break;

    case 1:
        Obst_destination_rect1_UP.x = 650;
        Obst_destination_rect1_UP.y = 50;
        Obst_destination_rect1_UP.w = 50;
        Obst_destination_rect1_UP.h = 50;

        Obst_destination_rect2_UP.x = 700;
        Obst_destination_rect2_UP.y = 50;
        Obst_destination_rect2_UP.w = 50;
        Obst_destination_rect2_UP.h = 50;

        Obst_destination_rect3_UP.x = 750;
        Obst_destination_rect3_UP.y = 50;
        Obst_destination_rect3_UP.w = 50;
        Obst_destination_rect3_UP.h = 50;

        Obst_destination_rect4_UP.x = 700;
        Obst_destination_rect4_UP.y = 100;
        Obst_destination_rect4_UP.w = 50;
        Obst_destination_rect4_UP.h = 50;
        break;

    case 2:
        Obst_destination_rect1_UP.x = 650;
        Obst_destination_rect1_UP.y = 50;
        Obst_destination_rect1_UP.w = 50;
        Obst_destination_rect1_UP.h = 50;

        Obst_destination_rect2_UP.x = 700;
        Obst_destination_rect2_UP.y = 50;
        Obst_destination_rect2_UP.w = 50;
        Obst_destination_rect2_UP.h = 50;

        Obst_destination_rect3_UP.x = 750;
        Obst_destination_rect3_UP.y = 50;
        Obst_destination_rect3_UP.w = 50;
        Obst_destination_rect3_UP.h = 50;

        Obst_destination_rect4_UP.x = 750;
        Obst_destination_rect4_UP.y = 100;
        Obst_destination_rect4_UP.w = 50;
        Obst_destination_rect4_UP.h = 50;
        break;

    case 3:
        Obst_destination_rect1_UP.x = 650;
        Obst_destination_rect1_UP.y = 50;
        Obst_destination_rect1_UP.w = 50;
        Obst_destination_rect1_UP.h = 50;

        Obst_destination_rect2_UP.x = 700;
        Obst_destination_rect2_UP.y = 50;
        Obst_destination_rect2_UP.w = 50;
        Obst_destination_rect2_UP.h = 50;

        Obst_destination_rect3_UP.x = 650;
        Obst_destination_rect3_UP.y = 100;
        Obst_destination_rect3_UP.w = 50;
        Obst_destination_rect3_UP.h = 50;

        Obst_destination_rect4_UP.x = 700;
        Obst_destination_rect4_UP.y = 100;
        Obst_destination_rect4_UP.w = 50;
        Obst_destination_rect4_UP.h = 50;
        break;
    }
}

void Obstacle::DO_Obst(int n)                  // 하단 장애물 종류 및 x, y축 값 설정
{
    switch (n % 4)
    {
    case 0:
        Obst_destination_rect1_DO.x = 650;
        Obst_destination_rect1_DO.y = 320;
        Obst_destination_rect1_DO.w = 50;
        Obst_destination_rect1_DO.h = 50;

        Obst_destination_rect2_DO.x = 700;
        Obst_destination_rect2_DO.y = 320;
        Obst_destination_rect2_DO.w = 50;
        Obst_destination_rect2_DO.h = 50;

        Obst_destination_rect3_DO.x = 750;
        Obst_destination_rect3_DO.y = 320;
        Obst_destination_rect3_DO.w = 50;
        Obst_destination_rect3_DO.h = 50;

        Obst_destination_rect4_DO.x = 650;
        Obst_destination_rect4_DO.y = 270;
        Obst_destination_rect4_DO.w = 50;
        Obst_destination_rect4_DO.h = 50;
        break;

    case 1:
        Obst_destination_rect1_DO.x = 650;
        Obst_destination_rect1_DO.y = 320;
        Obst_destination_rect1_DO.w = 50;
        Obst_destination_rect1_DO.h = 50;

        Obst_destination_rect2_DO.x = 700;
        Obst_destination_rect2_DO.y = 320;
        Obst_destination_rect2_DO.w = 50;
        Obst_destination_rect2_DO.h = 50;

        Obst_destination_rect3_DO.x = 750;
        Obst_destination_rect3_DO.y = 320;
        Obst_destination_rect3_DO.w = 50;
        Obst_destination_rect3_DO.h = 50;

        Obst_destination_rect4_DO.x = 700;
        Obst_destination_rect4_DO.y = 270;
        Obst_destination_rect4_DO.w = 50;
        Obst_destination_rect4_DO.h = 50;
        break;

    case 2:
        Obst_destination_rect1_DO.x = 650;
        Obst_destination_rect1_DO.y = 320;
        Obst_destination_rect1_DO.w = 50;
        Obst_destination_rect1_DO.h = 50;

        Obst_destination_rect2_DO.x = 700;
        Obst_destination_rect2_DO.y = 320;
        Obst_destination_rect2_DO.w = 50;
        Obst_destination_rect2_DO.h = 50;

        Obst_destination_rect3_DO.x = 750;
        Obst_destination_rect3_DO.y = 320;
        Obst_destination_rect3_DO.w = 50;
        Obst_destination_rect3_DO.h = 50;

        Obst_destination_rect4_DO.x = 750;
        Obst_destination_rect4_DO.y = 270;
        Obst_destination_rect4_DO.w = 50;
        Obst_destination_rect4_DO.h = 50;
        break;

    case 3:
        Obst_destination_rect1_DO.x = 650;
        Obst_destination_rect1_DO.y = 320;
        Obst_destination_rect1_DO.w = 50;
        Obst_destination_rect1_DO.h = 50;

        Obst_destination_rect2_DO.x = 700;
        Obst_destination_rect2_DO.y = 320;
        Obst_destination_rect2_DO.w = 50;
        Obst_destination_rect2_DO.h = 50;

        Obst_destination_rect3_DO.x = 650;
        Obst_destination_rect3_DO.y = 270;
        Obst_destination_rect3_DO.w = 50;
        Obst_destination_rect3_DO.h = 50;

        Obst_destination_rect4_DO.x = 700;
        Obst_destination_rect4_DO.y = 270;
        Obst_destination_rect4_DO.w = 50;
        Obst_destination_rect4_DO.h = 50;
        break;
    }
}

void Obstacle::Obstacle_make_UP()                   // 장애물 생성 및 x축 좌향 이동 함수
{
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_UP))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect1_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_UP))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect2_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_UP))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect3_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_UP))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect4_UP);
    }

    if (level == 3)
    {

        if (repulsion_effect)                   // 만약 척력 지속시간이라면
        {
            Obst_destination_rect1_UP.x -= 2;
            Obst_destination_rect2_UP.x -= 2;
            Obst_destination_rect3_UP.x -= 2;
            Obst_destination_rect4_UP.x -= 2;
        }

        else
        {
            Obst_destination_rect1_UP.x -= 5;
            Obst_destination_rect2_UP.x -= 5;
            Obst_destination_rect3_UP.x -= 5;
            Obst_destination_rect4_UP.x -= 5;
        }
    }

    else
    {
        if (repulsion_effect)                   // 만약 척력 지속시간이라면
        {
            Obst_destination_rect1_UP.x -= 1;
            Obst_destination_rect2_UP.x -= 1;
            Obst_destination_rect3_UP.x -= 1;
            Obst_destination_rect4_UP.x -= 1;
        }

        else
        {
            Obst_destination_rect1_UP.x -= 4;
            Obst_destination_rect2_UP.x -= 4;
            Obst_destination_rect3_UP.x -= 4;
            Obst_destination_rect4_UP.x -= 4;
        }
    }
}

void Obstacle::Obstacle_make_DO()                   // 장애물 생성 및 x축 좌향 이동 함수
{
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_DO))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect1_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_DO))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect2_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_DO))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect3_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_DO))
    {
        SDL_RenderCopy(renderer, Obst, NULL, &Obst_destination_rect4_DO);
    }

    if (level == 3)
    {
        if (repulsion_effect)                   // 만약 척력 지속시간이라면
        {
            Obst_destination_rect1_DO.x -= 2;
            Obst_destination_rect2_DO.x -= 2;
            Obst_destination_rect3_DO.x -= 2;
            Obst_destination_rect4_DO.x -= 2;
        }

        else
        {
            Obst_destination_rect1_DO.x -= 5;
            Obst_destination_rect2_DO.x -= 5;
            Obst_destination_rect3_DO.x -= 5;
            Obst_destination_rect4_DO.x -= 5;
        }
    }

    else
    {
        if (repulsion_effect)                   // 만약 척력 지속시간이라면
        {
            Obst_destination_rect1_DO.x -= 1;
            Obst_destination_rect2_DO.x -= 1;
            Obst_destination_rect3_DO.x -= 1;
            Obst_destination_rect4_DO.x -= 1;
        }

        else
        {
            Obst_destination_rect1_DO.x -= 4;
            Obst_destination_rect2_DO.x -= 4;
            Obst_destination_rect3_DO.x -= 4;
            Obst_destination_rect4_DO.x -= 4;
        }
    }
}

bool nocrash()
{
    return (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_DO));
}

void Obstacle::Fly_Obst()                   // 날아오는 장애물 생성 및 x축 좌향 이동 함수
{
    bool h = nocrash();
    if (h)
    {
        SDL_RenderCopy(renderer, F_Obst, NULL, &F_Obst_destination_rect);
    }

    if (level == 3)                     // 3개 장애물 출현 시 날아오는 장애물 속도 증가
    {
        if (repulsion_effect)                       // 만약 척력 지속시간이라면
        {
            if (h)                                  // 장애물과 충돌하지 않았을 때
                F_Obst_destination_rect.x -= 4;
            else
                F_Obst_destination_rect.x -= 2;
        }

        else
        {
            if (h)                                  // 장애물과 충돌하지 않았을 때
                F_Obst_destination_rect.x -= 7;
            else
                F_Obst_destination_rect.x -= 5;
        }
    }

    else
    {
        if (repulsion_effect)                       // 만약 척력 지속시간이라면
        {
            if (h)                                  // 장애물과 충돌하지 않았을 때
                F_Obst_destination_rect.x -= 2;
            else
                F_Obst_destination_rect.x -= 1;
        }

        else
        {
            if (h)                                  // 장애물과 충돌하지 않았을 때
                F_Obst_destination_rect.x -= 5;
            else
                F_Obst_destination_rect.x -= 4;
        }
    }
}

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* file) {
    SDL_Surface* surface = IMG_Load(file);
    if (surface == NULL) {
        printf("%s 파일을 읽지 못했습니다.\n", file);
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int screenWidth = 620;
int screenHeight = 400;
bool storyOut = true; // 스토리 출력대기 여부

enum GameState {// 게임 상태 열거
    MENU,
    PLAYING,
    HELP,
    GAMEOVER,
    GAMECLEAR,
    QUIT
};

bool isInside(SDL_Rect* rect, int x, int y) {//클릭 좌표 확인
    return x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h;
}
// 메뉴 화면 렌더링 함수
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight) {
    IMG_Init(IMG_INIT_PNG);

    SDL_Surface* bgSurface = IMG_Load("main_1.png");
    if (!bgSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n", "배경화면", IMG_GetError());
        return;
    }
    SDL_Texture* bgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    // 배경 이미지 렌더링
    SDL_RenderCopy(renderer, bgTexture, NULL, NULL);
    SDL_DestroyTexture(bgTexture);

    SDL_Color textColor = { 0, 0, 0, 255 };

    TTF_Font* titleFont = TTF_OpenFont("mainfont.ttf", 28);

    SDL_Surface* titleSurface = TTF_RenderText_Solid(titleFont, "Newton: Power of Apple", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
    int titleWidth = titleSurface->w;
    int titleHeight = titleSurface->h;
    SDL_Rect titleRect = { (screenWidth - titleWidth) / 2, 50, titleWidth, titleHeight };
    SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);

    TTF_CloseFont(titleFont);
    // 시작 버튼 렌더링
    SDL_Surface* startSurface = TTF_RenderText_Solid(font, "Start Game", textColor);
    SDL_Texture* startTexture = SDL_CreateTextureFromSurface(renderer, startSurface);
    int startWidth = startSurface->w;
    int startHeight = startSurface->h;
    SDL_Rect startRect = { (screenWidth - startWidth) / 2, 140, startWidth, startHeight };
    SDL_RenderCopy(renderer, startTexture, NULL, &startRect);
    SDL_FreeSurface(startSurface);
    SDL_DestroyTexture(startTexture);
    // 도움말 버튼 렌더링
    SDL_Surface* helpSurface = TTF_RenderText_Solid(font, "Help", textColor);
    SDL_Texture* helpTexture = SDL_CreateTextureFromSurface(renderer, helpSurface);
    int helpWidth = helpSurface->w;
    int helpHeight = helpSurface->h;
    SDL_Rect helpRect = { (screenWidth - helpWidth) / 2, 220, helpWidth, helpHeight };
    SDL_RenderCopy(renderer, helpTexture, NULL, &helpRect);
    SDL_FreeSurface(helpSurface);
    SDL_DestroyTexture(helpTexture);
    // 종료 버튼 렌더링
    SDL_Surface* quitSurface = TTF_RenderText_Solid(font, "Exit Game", textColor);
    SDL_Texture* quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
    int quitWidth = quitSurface->w;
    int quitHeight = quitSurface->h;
    SDL_Rect quitRect = { (screenWidth - quitWidth) / 2, 300, quitWidth, quitHeight };
    SDL_RenderCopy(renderer, quitTexture, NULL, &quitRect);
    SDL_FreeSurface(quitSurface);
    SDL_DestroyTexture(quitTexture);
}
// 도움말 화면 렌더링 함수
void renderHelp(SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
    SDL_Color textColor = { 255, 255, 255, 255 };
    const char* arrowKeys[] = { "up.png", "down.png", "right.png", "spacebar.png" };
    int yOffset = 30; // 첫 번째 이미지의 Y 오프셋 
    for (int i = 0; i < 4; ++i) {
        SDL_Surface* arrowSurface = IMG_Load(arrowKeys[i]);
        if (!arrowSurface) {
            printf("Unable to load image %s! SDL_image Error: %s\n", arrowKeys[i], IMG_GetError());
            return;
        }
        SDL_Texture* arrowTexture = SDL_CreateTextureFromSurface(renderer, arrowSurface);
        int arrowWidth = arrowSurface->w;
        int arrowHeight = arrowSurface->h;
        SDL_Rect arrowRect = { (screenWidth - arrowWidth) / 2 - 200, yOffset, arrowWidth, arrowHeight };
        SDL_RenderCopy(renderer, arrowTexture, NULL, &arrowRect);
        SDL_FreeSurface(arrowSurface);
        SDL_DestroyTexture(arrowTexture);
        yOffset += arrowHeight - 20; // 다음 이미지의 Y 오프셋

    }
    // 도움말 텍스트 렌더링
    SDL_Surface* upHelpSurface = TTF_RenderText_Solid(font, "Middle Obstacle Rise", textColor);
    SDL_Texture* upHelpTexture = SDL_CreateTextureFromSurface(renderer, upHelpSurface);
    int upHelpWidth = upHelpSurface->w;
    int upHelpX = (screenWidth - upHelpWidth) / 2 + 40;
    int upHelpY = 50;
    SDL_Rect upHelpRect = { upHelpX, upHelpY, upHelpWidth, upHelpSurface->h };
    SDL_RenderCopy(renderer, upHelpTexture, NULL, &upHelpRect);
    SDL_FreeSurface(upHelpSurface);
    SDL_DestroyTexture(upHelpTexture);

    SDL_Surface* downHelpSurface = TTF_RenderText_Solid(font, "Middle Obstacle Down", textColor);
    SDL_Texture* downHelpTexture = SDL_CreateTextureFromSurface(renderer, downHelpSurface);
    int downHelpWidth = downHelpSurface->w;
    int downHelpX = (screenWidth - downHelpWidth) / 2 + 54;
    int downHelpY = 128;
    SDL_Rect downHelpRect = { downHelpX, downHelpY, downHelpWidth, downHelpSurface->h };
    SDL_RenderCopy(renderer, downHelpTexture, NULL, &downHelpRect);
    SDL_FreeSurface(downHelpSurface);
    SDL_DestroyTexture(downHelpTexture);

    SDL_Surface* rightHelpSurface = TTF_RenderText_Solid(font, "Reduce Obstacle Speed", textColor);
    SDL_Texture* rightHelpTexture = SDL_CreateTextureFromSurface(renderer, rightHelpSurface);
    int rightHelpWidth = rightHelpSurface->w;
    int rightHelpX = (screenWidth - downHelpWidth) / 2 + 54;
    int rightHelpY = 202;
    SDL_Rect rightHelpRect = { rightHelpX, rightHelpY, rightHelpWidth, rightHelpSurface->h };
    SDL_RenderCopy(renderer, rightHelpTexture, NULL, &rightHelpRect);
    SDL_FreeSurface(rightHelpSurface);
    SDL_DestroyTexture(rightHelpTexture);

    SDL_Surface* SBHelpSurface = TTF_RenderText_Solid(font, "Newton jumps", textColor);
    SDL_Texture* SBHelpTexture = SDL_CreateTextureFromSurface(renderer, SBHelpSurface);
    int SBHelpWidth = SBHelpSurface->w;
    int SBHelpX = (screenWidth - upHelpWidth) / 2 + 45;
    int SBHelpY = 280;
    SDL_Rect SBHelpRect = { SBHelpX, SBHelpY, SBHelpWidth, SBHelpSurface->h };
    SDL_RenderCopy(renderer, SBHelpTexture, NULL, &SBHelpRect);
    SDL_FreeSurface(SBHelpSurface);
    SDL_DestroyTexture(SBHelpTexture);

    // 뒤로 가기 버튼 렌더링
    SDL_Surface* backSurface = TTF_RenderText_Solid(font, "Back", textColor);
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurface);
    int backWidth = backSurface->w;
    int backHeight = backSurface->h;
    SDL_Rect backRect = { (screenWidth - backWidth) / 2, 330, backWidth, backHeight };
    SDL_RenderCopy(renderer, backTexture, NULL, &backRect);
    SDL_FreeSurface(backSurface);
    SDL_DestroyTexture(backTexture);
}
// SDL 및 게임 초기화 함수
bool init(SDL_Window*& window, SDL_Renderer*& renderer, TTF_Font*& font) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL 초기화 실패! (" << SDL_GetError() << ")\n";
        return false;
    }

    if (TTF_Init() == -1) {
        cout << "SDL_ttf 초기화 실패! (" << TTF_GetError() << ")\n";
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("Newton: Power of Apple", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 400, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        cout << "윈도우 생성 실패! (" << SDL_GetError() << ")\n";
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        cout << "렌더러 생성 실패! (" << SDL_GetError() << ")\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image 초기화 실패! (" << IMG_GetError() << ")\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    font = TTF_OpenFont("mainfont.ttf", 28);
    if (font == NULL) {
        cout << "폰트 로드 실패! (" << TTF_GetError() << ")\n";
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}
// SDL 및 게임 종료 함수
void close(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* appleTexture) {
    SDL_DestroyTexture(appleTexture);
    TTF_CloseFont(font);
    font = nullptr;
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(obstTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
// 게임 오버 화면 렌더링 함수
void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight) { //게임오버 화면 렌더링
    SDL_Color textColor1 = { 255, 0, 0, 255 }; //붉은색 글자
    SDL_Color textColor = { 255, 255, 255, 255 }; // 하얀색 글자
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    TTF_Font* gameOverFont = TTF_OpenFont("mainfont.ttf", 40);
    //게임 오버 타이틀 렌더링
    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(gameOverFont, "Game Over", textColor1); // 붉은색으로 출력
    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);
    int gameOverWidth = gameOverSurface->w;
    int gameOverHeight = gameOverSurface->h;
    SDL_Rect gameOverRect = { (screenWidth - gameOverWidth) / 2, 50, gameOverWidth, gameOverHeight };
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);

    TTF_CloseFont(gameOverFont);
    // 생존시간 렌더링
    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, "Time: 00:00", textColor); // 하얀색으로 출력
    SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
    int timeWidth = timeSurface->w;
    int timeHeight = timeSurface->h;
    SDL_Rect timeRect = { (screenWidth - timeWidth) / 2, 140, timeWidth, timeHeight };
    SDL_RenderCopy(renderer, timeTexture, NULL, &timeRect);
    SDL_FreeSurface(timeSurface);
    SDL_DestroyTexture(timeTexture);
    // 메인메뉴 버튼 렌더링
    SDL_Surface* continueSurface = TTF_RenderText_Solid(font, "Continue", textColor);
    SDL_Texture* continueTexture = SDL_CreateTextureFromSurface(renderer, continueSurface);
    int continueWidth = continueSurface->w;
    int continueHeight = continueSurface->h;
    SDL_Rect continueRect = { (screenWidth - continueWidth) / 2, 220, continueWidth, continueHeight };
    SDL_RenderCopy(renderer, continueTexture, NULL, &continueRect);
    SDL_FreeSurface(continueSurface);
    SDL_DestroyTexture(continueTexture);
    // 게임 종료 버튼 렌더링
    SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "ExitGame", textColor);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    int exitWidth = exitSurface->w;
    int exitX = (screenWidth - exitWidth) / 2;
    int exitY = 300;
    SDL_Rect exitRect = { exitX, exitY, exitWidth, exitSurface->h };
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    SDL_FreeSurface(exitSurface);
    SDL_DestroyTexture(exitTexture);

    SDL_RenderPresent(renderer);
}

void GameClearStory() {//엔딩스토리 출력
    const char* story = "달려나가다 보니 점점 물체들이 더 빨리 날아오는 걸 뉴턴은 느꼈고,\n\n"
        "이에 뉴턴은 근원지에 가까워지고 있다는 확신을 했다.\n\n\n"

        "그렇게 점점 근원지가 보이기 시작한 뉴턴은 놀라게 되는데...\n\n"
        "처음 자신이 위치했던 그 사과나무로부터 물체들이 날아오는 것이었다.\n\n\n"

        "아니 더 정확히 말하면, \n\n"
        "뉴턴이 근원지를 본 시점에는 근원지가 너무 빨리 다가오는 것이 아닌가!\n\n\n"

        "그렇다. 뉴턴은 어딘가에서 뉴턴을 향해 물체를 던지는 줄만 알았는데\n\n"
        "알고 보니 날아오던 여러 물체도, 사과나무도 모두 뉴턴이 끌어당기고 있었던 것이었고,\n\n"
        "뉴턴이 달려가며 사과나무에 가까워지니, \n\n"
        "사과나무가 뉴턴을 끌어당기는 힘이 점점 강해져 물체 또한 더 빠르게 날아오는 것처럼 보였던 것이다.\n\n\n"

        "그렇게 그 힘이 계속 강해져 결국 뉴턴은 사과나무에 부딪히게 되며 꿈에서 깨게 된다.\n\n\n"

        "꿈에서 깬 뉴턴은, \"아무리 밀어내려 해도 결국 모든 것은 서로 끌어당기기 마련이구나!\"라는 깨달음을 얻는다. \n\n\n"
        "그렇게 뉴턴은 이 깨달음을 바탕으로 1687년에 논문을 발표하게 되는데,\n\n"
        "이로써 현대의 우리가 알고 있는 '만유인력의 법칙'이 세상에 알려지게 된다.";

    size_t length = strlen(story); // 문자열의 길이를 구함

    for (size_t i = 0; i < length; ++i) {
        cout << story[i]; // 한 글자씩 출력
        this_thread::sleep_for(chrono::milliseconds(25));
    }
}
void renderGameClear(SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight, int minutes, int seconds) {// 게임클리어 화면 렌더링

    SDL_Color textColor = { 255, 255, 0, 255 }; //글자 노란색 설정
    SDL_Color textColor2 = { 255, 255, 255, 255 };
    SDL_SetRenderDrawColor(renderer, 0x87, 0xCE, 0xEB, 0xFF); // 배경 하늘색 설정
    SDL_RenderClear(renderer);

    TTF_Font* gameClearFont = TTF_OpenFont("mainfont.ttf", 40);

    SDL_Surface* gameClearSurface = TTF_RenderText_Solid(gameClearFont, "GameClear", textColor);
    SDL_Texture* gameClearTexture = SDL_CreateTextureFromSurface(renderer, gameClearSurface);
    int gameClearWidth = gameClearSurface->w;
    int gameClearHeight = gameClearSurface->h;
    SDL_Rect gameClearRect = { (screenWidth - gameClearWidth) / 2, 50, gameClearWidth, gameClearHeight };
    SDL_RenderCopy(renderer, gameClearTexture, NULL, &gameClearRect);
    SDL_FreeSurface(gameClearSurface);
    SDL_DestroyTexture(gameClearTexture);

    TTF_CloseFont(gameClearFont);
    string endingtime = "Time: " + to_string(minutes) + ":" + to_string(seconds);
    const char* endingtime_cstr = endingtime.c_str();
    SDL_Surface* timeSurface = TTF_RenderText_Solid(font, endingtime_cstr, textColor2); // 하얀색으로 출력
    SDL_Texture* timeTexture = SDL_CreateTextureFromSurface(renderer, timeSurface);
    int timeWidth = timeSurface->w;
    int timeHeight = timeSurface->h;
    SDL_Rect timeRect = { (screenWidth - timeWidth) / 2, 140, timeWidth, timeHeight };
    SDL_RenderCopy(renderer, timeTexture, NULL, &timeRect);
    SDL_FreeSurface(timeSurface);
    SDL_DestroyTexture(timeTexture);

    SDL_Surface* restartSurface = TTF_RenderText_Solid(font, "Continue", textColor2);
    SDL_Texture* restartTexture = SDL_CreateTextureFromSurface(renderer, restartSurface);
    int restartWidth = restartSurface->w;
    int restartHeight = restartSurface->h;
    SDL_Rect restartRect = { (screenWidth - restartWidth) / 2, 220, restartWidth, restartHeight };
    SDL_RenderCopy(renderer, restartTexture, NULL, &restartRect);
    SDL_FreeSurface(restartSurface);
    SDL_DestroyTexture(restartTexture);

    SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "ExitGame", textColor2);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    int exitWidth = exitSurface->w;
    int exitX = (screenWidth - exitWidth) / 2;
    int exitY = 300;
    SDL_Rect exitRect = { exitX, exitY, exitWidth, exitSurface->h };
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    SDL_FreeSurface(exitSurface);
    SDL_DestroyTexture(exitTexture);

    SDL_RenderPresent(renderer);
}

void timeinit(const char* title, SDL_Window* gwindow, SDL_Renderer* grenderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }

    grenderer = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
    if (!grenderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
}
bool createWindowAndRenderer(const char* title, int x, int y, int w, int h,
    SDL_Window** window, SDL_Renderer** renderer) {
    *window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        return false;
    }

    return true;
}

void createGameOverWindow() {
    SDL_Window* gameOverWindow = NULL;
    SDL_Renderer* gameOverRenderer = NULL;
    if (!createWindowAndRenderer("Game Over", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 250, &gameOverWindow, &gameOverRenderer)) {
        return;
    }
    string text = "Play Time: ";
    SDL_Color color = { 255, 0, 0, 255 };
    SDL_Texture* gameOverTexture = renderText("Game Over", "mainfont.ttf", color, 48, gameOverRenderer);

    if (gameOverTexture == NULL) {
        SDL_DestroyRenderer(gameOverRenderer);
        SDL_DestroyWindow(gameOverWindow);
        return;
    }

    // 게임 오버 메시지 렌더링
    SDL_SetRenderDrawColor(gameOverRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gameOverRenderer);
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(gameOverTexture, NULL, NULL, &texW, &texH);
    SDL_Rect dstRect = { (400 - texW) / 2, (300 - texH) / 2, texW, texH };
    SDL_RenderCopy(gameOverRenderer, gameOverTexture, NULL, &dstRect);
    SDL_RenderPresent(gameOverRenderer);

    // 잠시 대기
    SDL_Delay(3000);

    // 자원 해제
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyRenderer(gameOverRenderer);
    SDL_DestroyWindow(gameOverWindow);

    exit(0);
}

void skill_gravity()                    // 중력 스킬 함수
{
    F_Obst_destination_rect.y += (25 + 25 * Apple_count);
    Apple_rect.y += (25 + 25 * Apple_count);
}

void skill_gravity_effect()                    // 중력 스킬 효과 함수
{
    Skill_Effect_texture = loadTexture_Skill_Effect(renderer, "Gravity.jpg");
    skill_effect_count = 200;
}

void skill_reverse_gravity()            // 역중력 스킬 함수
{
    F_Obst_destination_rect.y -= (25 + 25 * Apple_count);
    Apple_rect.y -= (25 + 25 * Apple_count);
}

void skill_reverse_gravity_effect()                    // 역중력 스킬 효과 함수
{
    Skill_Effect_texture = loadTexture_Skill_Effect(renderer, "ReverseGravity.jpg");
    skill_effect_count = 200;
}

void skill_repulsion(int n = 0)         // 척력 스킬 함수
{
    repulsion_effect = n;
}

void skill_repulsion_effect()                    // 척력 스킬 효과 함수
{
    Skill_Effect_texture = loadTexture_Skill_Effect(renderer, "Repulsion.jpg");
    skill_effect_count = 200;
}

void appletree()                    // 중력 스킬 효과 함수
{
    SDL_RenderCopy(renderer, AppleTree_texture, NULL, &AppleTree_destination_rect);
    AppleTree_destination_rect.x -= 1;
}

bool checkCollision(const Object& obj) {
    SDL_Rect objRect = { static_cast<int>(obj.x), static_cast<int>(obj.y), 45, 60 };
    vector<SDL_Rect> obstacles;
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_UP)) {
        obstacles.push_back(Obst_destination_rect1_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_UP)) {
        obstacles.push_back(Obst_destination_rect2_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_UP)) {
        obstacles.push_back(Obst_destination_rect3_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_UP)) {
        obstacles.push_back(Obst_destination_rect4_UP);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_DO)) {
        obstacles.push_back(Obst_destination_rect1_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_DO)) {
        obstacles.push_back(Obst_destination_rect2_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_DO)) {
        obstacles.push_back(Obst_destination_rect3_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_DO)) {
        obstacles.push_back(Obst_destination_rect4_DO);
    }
    if (!SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_UP) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect1_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect2_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect3_DO) && !SDL_HasIntersection(&F_Obst_destination_rect, &Obst_destination_rect4_DO))
    {
        obstacles.push_back(F_Obst_destination_rect);
    }
    for (auto it = obstacles.begin(); it != obstacles.end(); it++)
    {
        if (SDL_HasIntersection(&objRect, &(*it))) {
            return true;
        }
    }
    return false;
}

void runGame(SDL_Renderer* renderer, TTF_Font* font) {


    Uint32 startTime = SDL_GetTicks();
    Uint32 gameOverTime = 0;
    Uint32 gameClearTime = 0;
    Uint32 playingStartTime = 0;

    bool quit = false;
    bool gameOver = false;
    SDL_Event e;
    GameState state = MENU;

    SDL_Rect startButton, helpButton, quitButton, backButton, continueButton, exitButton;
    int startWidth, startHeight, helpWidth, helpHeight, quitWidth, quitHeight, backWidth, backHeight, continueWidth, continueHeight, exitWidth, exitHeight;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                if (state == MENU) {
                    if (isInside(&startButton, x, y)) {
                        state = PLAYING;
                        playingStartTime = SDL_GetTicks();
                    }
                    else if (isInside(&helpButton, x, y)) {
                        state = HELP;
                    }
                    else if (isInside(&quitButton, x, y)) {
                        quit = true;
                    }
                }
                else if (state == HELP) {
                    if (isInside(&backButton, x, y)) {
                        state = MENU;
                    }
                }
                else if (state == GAMEOVER) {
                    if (isInside(&continueButton, x, y)) {
                        state = MENU;
                        apples.clear();
                    }
                    else if (isInside(&exitButton, x, y)) {
                        quit = true;
                    }
                }
                else if (state == GAMECLEAR) {
                    if (isInside(&continueButton, x, y)) {
                        state = MENU;
                        apples.clear();
                    }
                    else if (isInside(&exitButton, x, y)) {
                        quit = true;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        if (state == MENU) {
            storyOut = true;
            renderMenu(renderer, font, screenWidth, screenHeight);

            SDL_Surface* startSurface = TTF_RenderText_Solid(font, "Start Game", { 255, 255, 255, 255 });
            startWidth = startSurface->w;
            startHeight = startSurface->h;
            SDL_FreeSurface(startSurface);
            startButton = { (screenWidth - startWidth) / 2, 140, startWidth, startHeight };

            SDL_Surface* helpSurface = TTF_RenderText_Solid(font, "Help", { 255, 255, 255, 255 });
            helpWidth = helpSurface->w;
            helpHeight = helpSurface->h;
            SDL_FreeSurface(helpSurface);
            helpButton = { (screenWidth - helpWidth) / 2, 220, helpWidth, helpHeight };

            SDL_Surface* quitSurface = TTF_RenderText_Solid(font, "Exit Game", { 255, 255, 255, 255 });
            quitWidth = quitSurface->w;
            quitHeight = quitSurface->h;
            SDL_FreeSurface(quitSurface);
            quitButton = { (screenWidth - quitWidth) / 2, 300, quitWidth, quitHeight };
        }
        else if (state == HELP) {//도움말창
            renderHelp(renderer, font, screenWidth, screenHeight);

            SDL_Surface* backSurface = TTF_RenderText_Solid(font, "Back", { 255, 255, 255, 255 });
            backWidth = backSurface->w;
            backHeight = backSurface->h;
            SDL_FreeSurface(backSurface);
            backButton = { (screenWidth - backWidth) / 2, 330, backWidth, backHeight };
        }
        else if (state == PLAYING) {//게임실행창
            int n = 0;

            clock_t start_time, end_time, last_apple_time;
            clock_t cooltime_start = 0;
            clock_t cooltime_end = 0;              // 척력 쿨타임 변수
            double elapsed_time, apple_elapsed_time, playingTime;
            start_time = clock();
            last_apple_time = start_time;

            Object obj(start_x - 70, start_y);
            playerTexture = loadTexture(renderer, "player1.png");

            playerRect = { static_cast<int>(obj.x) , static_cast<int>(obj.y + 50) , 50, 100 };

            bool appleCreated = false;
            bool running = true;
            SDL_Event event;
            int c = 0;
            bool jumping = false;
            Apple apple;
            string text = "Play Time: ";
            AppleTree_texture = loadTexture_AppleTree(renderer, "AppleTree.png");
            while (running)
            {
                end_time = clock();

                elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                apple_elapsed_time = (double)(end_time - last_apple_time) / CLOCKS_PER_SEC;
                playingTime = (double)(end_time - playingStartTime) / CLOCKS_PER_SEC;

                if (playingTime >= 15.0 && apple_elapsed_time >= 15.0) {
                    apple = Apple();
                    last_apple_time = clock();
                    appleCreated = true;
                }

                if (0 <= elapsed_time && elapsed_time < 30)             // 초반 게임 진행 30초 동안은 난이도 1 선정, 장애물 1개 출현
                {

                    level = 1;           // 난이도 1 (하)
                    n = rand();          // 상하단 결정 변수 랜덤 생성
                    srand(time(0));

                    Obstacle obstacle;



                    if (n % 2 == 0)         // 변수가 짝수면 상단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.UP_Obst(num1);

                        while (1)
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0)
                            {
                                if (event.type == SDL_QUIT)
                                    running = false;

                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }
                                        break;
                                    }

                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion(); // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임


                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }

                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }


                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }

                            if (elapsed_time < 4)
                                appletree();

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);
                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Obstacle_make_UP();
                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;

                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);
                            SDL_RenderPresent(renderer);
                            if (Obst_destination_rect3_UP.x < -200 && Obst_destination_rect4_UP.x < -200)         // 상단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }

                    else                    // 변수가 홀수면 하단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.DO_Obst(num1);

                        while (1)
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0)
                            {
                                if (event.type == SDL_QUIT)
                                    running = false;

                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }
                                        break;
                                    }

                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion(); // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임

                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }

                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }

                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }

                            if (elapsed_time < 4)
                                appletree();

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);

                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Obstacle_make_DO();
                            if (appleCreated) {
                                apple.fly_apple(obj);
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }
                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;

                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);
                            SDL_RenderPresent(renderer);
                            if (Obst_destination_rect3_DO.x < -200 && Obst_destination_rect4_DO.x < -200)         // 상단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }
                }

                else if (elapsed_time >= 30 && elapsed_time < 60)             // 게임 진행 30~60초 동안 난이도 2 선정, 장애물 2개(날아오는 장애물 1 + 상하단 장애물 中 1개) 출현
                {
                    level = 2;           // 난이도 2 (중)
                    n = rand();          // 상하단 결정 변수 랜덤 생성
                    srand(time(0));

                    Obstacle obstacle;

                    if (n % 2 == 0)         // 변수가 짝수면 상단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.UP_Obst(num1);

                        while (1)         // 상단 장애물, 날아오는 장애물 생성 및 이동
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    running = false;
                                }
                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }

                                        break;
                                    }
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion();  // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임

                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }

                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }
                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                // Check if the apple is out of the screen
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }
                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;
                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);
                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Fly_Obst();
                            obstacle.Obstacle_make_UP();
                            SDL_RenderPresent(renderer);

                            if (Obst_destination_rect3_UP.x < -200 && Obst_destination_rect4_UP.x < -200)         // 상단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }

                    else                  // 변수가 홀수면 하단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.DO_Obst(num1);

                        while (1)         // 하단 장애물, 날아오는 장애물 생성 및 이동
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    running = false;
                                }
                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }

                                        break;
                                    }

                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion();  // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임

                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }

                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }

                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                // Check if the apple is out of the screen
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }
                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;
                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);
                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Fly_Obst();
                            obstacle.Obstacle_make_DO();
                            SDL_RenderPresent(renderer);

                            if (Obst_destination_rect3_DO.x < -200 && Obst_destination_rect4_DO.x < -200)         // 하단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }
                }

                else if (elapsed_time >= 60 && elapsed_time < 90)                     // 게임 진행 90초 이후 난이도 3 선정, 장애물 3개(날아오는 장애물 1 + 상단 장애물 1개 + 하단 장애물 1개) 출현
                {
                    n = rand();          // 상하단 결정 변수 랜덤 생성
                    srand(time(0));
                    level = 3;           // 난이도 3(상)

                    Obstacle obstacle;

                    if (n % 2 == 0)         // 변수가 짝수면 상단 장애물 먼저 생성 후 하단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.UP_Obst(num1);

                        num2 = rand() + 1;
                        srand(time(0));
                        obstacle.DO_Obst(num2);

                        if (num2 % 3 == 0)
                        {
                            Obst_destination_rect1_DO.x += 700;
                            Obst_destination_rect2_DO.x += 700;
                            Obst_destination_rect3_DO.x += 700;
                            Obst_destination_rect4_DO.x += 700;
                        }

                        else if (num2 % 3 == 1)
                        {
                            Obst_destination_rect1_DO.x += 900;
                            Obst_destination_rect2_DO.x += 900;
                            Obst_destination_rect3_DO.x += 900;
                            Obst_destination_rect4_DO.x += 900;
                        }

                        else
                        {
                            Obst_destination_rect1_DO.x += 1100;
                            Obst_destination_rect2_DO.x += 1100;
                            Obst_destination_rect3_DO.x += 1100;
                            Obst_destination_rect4_DO.x += 1100;
                        }

                        while (1)         // 상단, 하단 장애물, 날아오는 장애물 생성 및 이동
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    running = false;
                                }
                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }
                                        break;
                                    }
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion();  // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임

                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }

                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }
                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }

                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;
                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);
                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Fly_Obst();
                            obstacle.Obstacle_make_UP();
                            obstacle.Obstacle_make_DO();
                            SDL_RenderPresent(renderer);

                            if (Obst_destination_rect3_DO.x < -200 && Obst_destination_rect4_DO.x < -200)         // 하단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }

                    else                // 변수가 홀수면 하단 장애물 먼저 생성 후 상단 장애물 생성
                    {
                        num1 = rand();
                        srand(time(0));
                        obstacle.UP_Obst(num1);

                        if (num1 % 3 == 0)
                        {
                            Obst_destination_rect1_UP.x += 700;
                            Obst_destination_rect2_UP.x += 700;
                            Obst_destination_rect3_UP.x += 700;
                            Obst_destination_rect4_UP.x += 700;
                        }

                        else if (num1 % 3 == 1)
                        {
                            Obst_destination_rect1_UP.x += 900;
                            Obst_destination_rect2_UP.x += 900;
                            Obst_destination_rect3_UP.x += 900;
                            Obst_destination_rect4_UP.x += 900;
                        }

                        else
                        {
                            Obst_destination_rect1_UP.x += 1100;
                            Obst_destination_rect2_UP.x += 1100;
                            Obst_destination_rect3_UP.x += 1100;
                            Obst_destination_rect4_UP.x += 1100;
                        }

                        num2 = rand() + 1;
                        srand(time(0));
                        obstacle.DO_Obst(num2);

                        while (1)         // 상단, 하단 장애물, 날아오는 장애물 생성 및 이동
                        {
                            Skill_Effect_Y = obj.y;

                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    running = false;
                                }
                                else if (event.type == SDL_KEYDOWN)
                                {
                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_SPACE:
                                        if (obj.isOnGround(start_y))
                                        {
                                            obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                            jump_count = true;
                                        }

                                        break;
                                    }

                                    switch (event.key.keysym.sym)
                                    {
                                    case SDLK_DOWN:                 // 중력 발동
                                        skill_gravity();
                                        skill_effect_number = 1;
                                        break;

                                    case SDLK_UP:                   // 역중력 발동
                                        skill_reverse_gravity();
                                        skill_effect_number = 2;
                                        break;

                                    case SDLK_RIGHT:                // 척력 발동
                                        if (elapsed_time > cooltime_end)
                                        {
                                            cooltime_start = elapsed_time; // 쿨타임 시작
                                            cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                            skill_repulsion(1); // 척력 스킬 함수 호출
                                            skill_effect_number = 3;
                                        }
                                        break;
                                    }
                                }
                            }

                            int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                            if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                                skill_repulsion();  // 척력 스킬 효과 소멸

                            // 공의 위치 업데이트
                            obj.applyGravity(gravity);
                            obj.move(); // 공을 움직임

                            // 공이 땅에 닿으면 위치를 초기화
                            if (obj.isOnGround(start_y))
                            {
                                obj.resetPosition(start_y);
                                jump_count = false;
                            }
                            gameOver = checkCollision(obj);

                            // 충돌 감지
                            if (gameOver) {
                                // 충돌 조건을 감지하면 게임 오버 창 생성
                                // 여기서는 임의의 조건으로 gameOver를 true로 설정
                                // 실제 게임에서는 충돌 감지 로직을 여기에 추가
                                gameOver = true;
                                createGameOverWindow();
                                running = false; // 게임 루프 종료
                            }
                            SDL_RenderClear(renderer);

                            Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                            BackgroundTexture = loadTexture(renderer, "Background.png");
                            SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                            SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                            SDL_RenderFillRect(renderer, &skyRect);

                            Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                            GroundTexture = loadTexture(renderer, "Ground.png");
                            SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                            if (appleCreated) {
                                apple.fly_apple(obj);
                                if (apple.isOutOfScreen()) {
                                    appleCreated = false;
                                }
                            }
                            Uint32 currentTime = SDL_GetTicks();
                            Uint32 playingTime = currentTime - playingStartTime;
                            Uint32 elapsedTime = currentTime - startTime;
                            int minutes = (playingTime / 1000) / 60;
                            int seconds = (playingTime / 1000) % 60;
                            renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);

                            if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                                obj.jump_render(renderer, playerTexture);
                            else
                                obj.render(renderer, playerTexture);

                            if (skill_effect_number != 0)                   // 스킬 효과 함수
                            {
                                switch (skill_effect_number)                // 스킬 효과 종류 설정
                                {
                                case 1:
                                    skill_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 2:
                                    skill_reverse_gravity_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 3:
                                    skill_repulsion_effect();
                                    skill_effect_number = 4;
                                    break;
                                case 4:
                                    Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                    break;
                                }

                                if (skill_effect_count > 0)
                                {
                                    SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                    skill_effect_count -= 2;

                                    if (skill_effect_count == 0)
                                        skill_effect_number = 0;
                                }
                            }

                            obstacle.Fly_Obst();
                            obstacle.Obstacle_make_UP();
                            obstacle.Obstacle_make_DO();
                            SDL_RenderPresent(renderer);

                            if (Obst_destination_rect3_UP.x < -200 && Obst_destination_rect4_UP.x < -200)         // 상단 장애물이 화면 밖으로 이동했을 때 새로운 장애물 생성
                                break;
                        }
                    }
                }
                else if (elapsed_time >= 90 && !ending)
                {
                    AppleTree_destination_rect.x = 730;
                    while (1)
                    {
                        Skill_Effect_Y = obj.y;

                        while (SDL_PollEvent(&event) != 0) {
                            if (event.type == SDL_QUIT) {
                                running = false;
                            }
                            else if (event.type == SDL_KEYDOWN)
                            {
                                switch (event.key.keysym.sym)
                                {
                                case SDLK_SPACE:
                                    if (obj.isOnGround(start_y))
                                    {
                                        obj.jump(jump_speed); // 스페이스 키가 눌리면 점프
                                        jump_count = true;
                                    }

                                    break;
                                }

                                switch (event.key.keysym.sym)
                                {
                                case SDLK_DOWN:                 // 중력 발동
                                    skill_gravity();
                                    skill_effect_number = 1;
                                    break;

                                case SDLK_UP:                   // 역중력 발동
                                    skill_reverse_gravity();
                                    skill_effect_number = 2;
                                    break;

                                case SDLK_RIGHT:                // 척력 발동
                                    if (elapsed_time > cooltime_end)
                                    {
                                        cooltime_start = elapsed_time; // 쿨타임 시작
                                        cooltime_end = elapsed_time + (30 - 5 * Apple_count); // 쿨타임 종료(30초 뒤), 사과를 먹으면 개당 쿨타임 5초 감소
                                        skill_repulsion(1); // 척력 스킬 함수 호출
                                        skill_effect_number = 3;
                                    }
                                    break;
                                }
                            }
                        }

                        int effect_time = (double)(clock()) / CLOCKS_PER_SEC;

                        if (effect_time - cooltime_start > 3) // 지속시간 3초가 지났을 경우
                            skill_repulsion();  // 척력 스킬 효과 소멸

                        // 공의 위치 업데이트
                        obj.applyGravity(gravity);
                        obj.move(); // 공을 움직임

                        // 공이 땅에 닿으면 위치를 초기화
                        if (obj.isOnGround(start_y))
                        {
                            obj.resetPosition(start_y);
                            jump_count = false;
                        }

                        SDL_RenderClear(renderer);

                        Background_rect = { 0, screen_y - 350, screen_x, 300 };                      // 배경 구현 구현
                        BackgroundTexture = loadTexture(renderer, "Background.png");
                        SDL_RenderCopy(renderer, BackgroundTexture, NULL, &Background_rect);

                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);                        // 상단 창 구현
                        SDL_Rect skyRect = { 0, screen_y - 400, screen_x, 50 };
                        SDL_RenderFillRect(renderer, &skyRect);

                        Ground_rect = { 0, screen_y - 30, screen_x, 30 };                            // 하단 땅 구현
                        GroundTexture = loadTexture(renderer, "Ground.png");
                        SDL_RenderCopy(renderer, GroundTexture, NULL, &Ground_rect);

                        Uint32 currentTime = SDL_GetTicks();
                        Uint32 playingTime = currentTime - playingStartTime;
                        Uint32 elapsedTime = currentTime - startTime;
                        int minutes = (playingTime / 1000) / 60;
                        int seconds = (playingTime / 1000) % 60;
                        renderText(renderer, font, text + to_string(minutes) + ":" + to_string(seconds), 0, 0);

                        if (jump_count)                                 // 플레이어가 점프 행동을 취했을 경우
                            obj.jump_render(renderer, playerTexture);
                        else
                            obj.render(renderer, playerTexture);

                        if (skill_effect_number != 0)                   // 스킬 효과 함수
                        {
                            switch (skill_effect_number)                // 스킬 효과 종류 설정
                            {
                            case 1:
                                skill_gravity_effect();
                                skill_effect_number = 4;
                                break;
                            case 2:
                                skill_reverse_gravity_effect();
                                skill_effect_number = 4;
                                break;
                            case 3:
                                skill_repulsion_effect();
                                skill_effect_number = 4;
                                break;
                            case 4:
                                Skill_Effect_destination_rect.y = Skill_Effect_Y - 100;
                                break;
                            }

                            if (skill_effect_count > 0)
                            {
                                SDL_RenderCopy(renderer, Skill_Effect_texture, NULL, &Skill_Effect_destination_rect);
                                skill_effect_count -= 2;

                                if (skill_effect_count == 0)
                                    skill_effect_number = 0;
                            }
                        }
                        appletree();
                        SDL_RenderPresent(renderer);

                        if (AppleTree_destination_rect.x == 110)                        // 엔딩 조건
                        {
                            ending = true;
                            break;
                        }
                    }
                }


                else if (elapsed_time >= 90 && ending)
                {
                    Uint32 currentTime = SDL_GetTicks();
                    Uint32 playingTime = currentTime - playingStartTime;
                    Uint32 elapsedTime = currentTime - startTime;
                    int minutes = (playingTime / 1000) / 60;
                    int seconds = (playingTime / 1000) % 60;
                    state = GAMECLEAR;
                    break;
                }
            }
        }
        else if (state == GAMEOVER) {
            renderGameOver(renderer, font, screenWidth, screenHeight);
            SDL_Surface* continueSurface = TTF_RenderText_Solid(font, "Continue", { 255, 255, 255, 255 });
            continueWidth = continueSurface->w;
            continueHeight = continueSurface->h;
            SDL_FreeSurface(continueSurface);
            continueButton = { (screenWidth - continueWidth) / 2, 220, continueWidth, continueHeight };

            SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", { 255, 255, 255, 255 });
            exitWidth = exitSurface->w;
            exitHeight = exitSurface->h;
            SDL_FreeSurface(exitSurface);
            exitButton = { (screenWidth - exitWidth) / 2, 300, exitWidth, exitHeight };
        }

        else if (state == GAMECLEAR) {
            Uint32 currentTime = SDL_GetTicks();
            Uint32 playingTime = currentTime - playingStartTime;
            Uint32 elapsedTime = currentTime - startTime;
            int minutes = (playingTime / 1000) / 60;
            int seconds = (playingTime / 1000) % 60;
            renderGameClear(renderer, font, screenWidth, screenHeight, minutes, seconds);
            SDL_Surface* continueSurface = TTF_RenderText_Solid(font, "Continue", { 255, 255, 255, 255 });
            continueWidth = continueSurface->w;
            continueHeight = continueSurface->h;
            SDL_FreeSurface(continueSurface);
            continueButton = { (screenWidth - continueWidth) / 2, 220, continueWidth, continueHeight };

            SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", { 255, 255, 255, 255 });
            exitWidth = exitSurface->w;
            exitHeight = exitSurface->h;
            SDL_FreeSurface(exitSurface);
            exitButton = { (screenWidth - exitWidth) / 2, 300, exitWidth, exitHeight };
            if (storyOut == true) {
                storyOut = false;
                GameClearStory();
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(appleTexture);
}

int main(int argc, char* args[]) {
    TTF_Font* font = NULL;

    PlaySound(L"GameBGM.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);       // 게임 BGM 재생

    if (!init(window, renderer, font)) {
        cout << "초기화 실패!\n";
        return 1;
    }

    runGame(renderer, font);

    close(window, renderer, font, NULL);
    system("pause");                                                            // 게임 BGM 종료
    return 0;
}
