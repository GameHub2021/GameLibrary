#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <Windows.h>
#include <time.h> 
#include <string.h>
#include <stdlib.h> // 난수 생성
#include <malloc.h>
#include <conio.h>
#include <SDL.h> // SDL 헤더파일
#include <SDL_image.h> // SDL 이미지 헤더파일

#define MAX_QUEST_SIZE 100

SDL_Window* window = NULL;

typedef struct TreeNode {
    char monster[100]; //스테이지 몬스터 이름
    struct TreeNode* left, * right;
} TreeNode;

typedef struct stage_stack {
    TreeNode* stack[MAX_QUEST_SIZE];
    int top;
} Stage_Stack;

// 구조체 선언
typedef struct skill_StackNode {//스택 구조체
    int skill;
    struct skill_StackNode* link;
}Skill_StackNode;

typedef struct Skill_LinkedStackType {
    Skill_StackNode* top;
}Skill_LinkedStackType;

typedef struct player { //플레이어 구조체
    int hp;
}Player;

typedef struct Monster { // 몬스터 구조체
    int hp; // 몬스터 체력
    char name[15]; // 몬스터 이름
    int max_skill; // 몬스터가 사용가능한 버프 횟수
}Monster;

typedef struct Monster_Queue_Node { // 몬스터 큐 구조체
    Monster QueueElements;
    struct Monster_Queue_Node* link;
}Monster_Queue_Node;

typedef struct Monster_LinkedQueueType {
    Monster_Queue_Node* front;
    Monster_Queue_Node* rear;
}Monster_LinkedQueueType;

void InitSDL();
void CleanUp(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* textures[], int count);
SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* file, SDL_Rect* srcRect);
void RenderTextures(SDL_Renderer* renderer, SDL_Texture* textures[], SDL_Rect srcRects[], SDL_Rect dstRects[], int count);

int stage0()                // 튜토리얼 스테이지 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0, src, src2;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/st1.jpg", &src0);
    SDL_Texture* texture = LoadTexture(renderer, "./img/warrior.png", &src);
    SDL_Texture* texture2 = LoadTexture(renderer, "./img/slime.png", &src2);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };
    SDL_Rect dst = { 0, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst2 = { screenWidth / 20 * 5, screenHeight / 4, screenWidth / 8, screenHeight / 5 };

    SDL_Texture* textures[] = { texture0, texture, texture2 };
    SDL_Rect srcRects[] = { src0, src, src2 };
    SDL_Rect dstRects[] = { dst0, dst, dst2 };

    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 3);
    SDL_RenderPresent(renderer);

    return 0;
}

int stage1()                // 스테이지1 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0, src, src2, src3, src4;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/st1.jpg", &src0);
    SDL_Texture* texture = LoadTexture(renderer, "./img/warrior.png", &src);
    SDL_Texture* texture2 = LoadTexture(renderer, "./img/goblin.png", &src2);
    SDL_Texture* texture3 = LoadTexture(renderer, "./img/slime.png", &src3);
    SDL_Texture* texture4 = LoadTexture(renderer, "./img/slime.png", &src4);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };
    SDL_Rect  dst = { 0, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst2 = { screenWidth / 20 * 7, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst3 = { screenWidth / 20 * 5, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst4 = { screenWidth / 20 * 3, screenHeight / 4, screenWidth / 8, screenHeight / 5 };

    SDL_Texture* textures[] = { texture0, texture, texture2, texture3, texture4 };
    SDL_Rect srcRects[] = { src0, src, src2, src3, src4 };
    SDL_Rect dstRects[] = { dst0, dst, dst2, dst3, dst4 };

    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 5);
    SDL_RenderPresent(renderer);

    return 0;
}

int stage2()                // 스테이지2 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0, src, src2, src3, src4;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/st2.jpg", &src0);
    SDL_Texture* texture = LoadTexture(renderer, "./img/warrior.png", &src);
    SDL_Texture* texture2 = LoadTexture(renderer, "./img/ork.png", &src2);
    SDL_Texture* texture3 = LoadTexture(renderer, "./img/goblin.png", &src3);
    SDL_Texture* texture4 = LoadTexture(renderer, "./img/goblin.png", &src4);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };
    SDL_Rect dst = { 0, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst2 = { screenWidth / 20 * 7, screenHeight / 7, screenWidth / 8, screenHeight / 3 };
    SDL_Rect dst3 = { screenWidth / 20 * 5, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect dst4 = { screenWidth / 20 * 3, screenHeight / 4, screenWidth / 8, screenHeight / 5 };

    SDL_Texture* textures[] = { texture0, texture, texture2, texture3, texture4 };
    SDL_Rect srcRects[] = { src0, src, src2, src3, src4 };
    SDL_Rect dstRects[] = { dst0, dst, dst2, dst3, dst4 };

    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 5);
    SDL_RenderPresent(renderer);

    return 0;
}

int stage3()                // 스테이지3 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0, src, src2, src3, src4;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/st3.jpg", &src0);
    SDL_Texture* texture = LoadTexture(renderer, "./img/warrior.png", &src);
    SDL_Texture* texture2 = LoadTexture(renderer, "./img/vamp.png", &src2);
    SDL_Texture* texture3 = LoadTexture(renderer, "./img/ork.png", &src3);
    SDL_Texture* texture4 = LoadTexture(renderer, "./img/ork.png", &src4);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };
    SDL_Rect dst = { 0, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect  dst2 = { screenWidth / 20 * 7, screenHeight / 6, screenWidth / 6, screenHeight / 4 };
    SDL_Rect  dst3 = { screenWidth / 20 * 5, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect  dst4 = { screenWidth / 20 * 3, screenHeight / 4, screenWidth / 8, screenHeight / 5 };

    SDL_Texture* textures[] = { texture0, texture, texture2, texture3, texture4 };
    SDL_Rect srcRects[] = { src0, src, src2, src3, src4 };
    SDL_Rect dstRects[] = { dst0, dst, dst2, dst3, dst4 };

    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 5);
    SDL_RenderPresent(renderer);

    return 0;
}

int stage4()                // 스테이지4 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0, src, src2, src3, src4;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/st4.jpg", &src0);
    SDL_Texture* texture = LoadTexture(renderer, "./img/warrior.png", &src);
    SDL_Texture* texture2 = LoadTexture(renderer, "./img/devil_king.png", &src2);
    SDL_Texture* texture3 = LoadTexture(renderer, "./img/vamp.png", &src3);
    SDL_Texture* texture4 = LoadTexture(renderer, "./img/vamp.png", &src4);

    SDL_Rect  dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };
    SDL_Rect  dst = { 0, screenHeight / 4, screenWidth / 8, screenHeight / 5 };
    SDL_Rect  dst2 = { screenWidth / 20 * 6, screenHeight / 8, screenWidth / 5, screenHeight / 3 };
    SDL_Rect dst3 = { screenWidth / 40 * 9, screenHeight / 5, screenWidth / 6, screenHeight / 4 };
    SDL_Rect  dst4 = { screenWidth / 40 * 5, screenHeight / 5, screenWidth / 6, screenHeight / 4 };

    SDL_Texture* textures[] = { texture0, texture, texture2, texture3, texture4 };
    SDL_Rect srcRects[] = { src0, src, src2, src3, src4 };
    SDL_Rect dstRects[] = { dst0, dst, dst2, dst3, dst4 };

    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 5);
    SDL_RenderPresent(renderer);

    return 0;
}

int victory()                // 승리창 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/victory.png", &src0);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };

    SDL_Texture* textures[] = { texture0 };
    SDL_Rect srcRects[] = { src0 };
    SDL_Rect dstRects[] = { dst0 };
    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 1);
    SDL_RenderPresent(renderer);

    return 0;
}

int defeat()                // 패배창 SDL 출력
{
    InitSDL();

    SDL_DestroyWindow(window);
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    window = SDL_CreateWindow("windowName", 0, screenHeight / 4, screenWidth / 2, screenHeight / 2 - 10, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Rect src0;
    SDL_Texture* texture0 = LoadTexture(renderer, "./img/defeat.png", &src0);

    SDL_Rect dst0 = { 0, 0, screenWidth / 2, screenHeight / 2 - 10 };

    SDL_Texture* textures[] = { texture0 };
    SDL_Rect srcRects[] = { src0 };
    SDL_Rect dstRects[] = { dst0 };
    SDL_RenderClear(renderer);
    RenderTextures(renderer, textures, srcRects, dstRects, 1);
    SDL_RenderPresent(renderer);

    return 0;
}

void InitSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        exit(1);
    }
    if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG)))
    {
        SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
}

SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* file, SDL_Rect* srcRect)
{
    SDL_Surface* surface = IMG_Load(file);
    if (!surface)
    {
        SDL_Log("Unable to load image %s: %s", file, IMG_GetError());
        return NULL;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture)
    {
        SDL_Log("Unable to create texture from %s: %s", file, SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }
    srcRect->x = 0;
    srcRect->y = 0;
    srcRect->w = surface->w;
    srcRect->h = surface->h;
    SDL_FreeSurface(surface);
    return texture;
}

void RenderTextures(SDL_Renderer* renderer, SDL_Texture* textures[], SDL_Rect srcRects[], SDL_Rect dstRects[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        SDL_RenderCopy(renderer, textures[i], &srcRects[i], &dstRects[i]);
    }
}


//생성 및 초기화 함수들
void stack_init(Skill_LinkedStackType* skill_stack) {
    skill_stack->top = NULL;
}
void queue_init(Monster_LinkedQueueType* monster_queue) {
    monster_queue->front = NULL;
    monster_queue->rear = NULL;
}
void game_story(int storyNum) {
    const char* story[] = {
       "오늘도 어김없이 과제를 위해 밤새워서 코딩을 하고 있던 상명대 공대생 A군...\n\n"
       "커피를 타러 부엌을 가던 도중 바닥에 미끄러져 그만 머리를 꽈당!!!\n\n"
       "정신을 차리고 눈을 떴을 때 보인 건 낯선 천장... 낯선 슬라임????? 나 이세계에 떨어진거야?\n\n"
       "벌레도 못죽...... 이지는 않지만 슬라임을 해치울 용기는 없었던 소심한 A군!\n\n"
       "야야 다가오지 마! 나 맛없다고!!! 다가오는 슬라임을 저지하기 위해 손을 뻗은 순간?\n\n"
       "슬라임이 느려졌다 ? ? ? 근데 왜 공격 마법은 안나가 ? ? ? \n\n"
       "하지만 A군의 소심한 성격이 반영된 것일까?? 공격 마법은 라이터 불꽃도 나오지 않는데...\n\n"
       "그때, 등장한 이세계의 용사! 슬라임을 처치하기 위해 검을 뽑아든다.\n\n"
       "A군은 용사를 응원하기 시작하는데, 용사의 힘이 강해지기 시작한다...?\n\n"
       "가라 용사몬! 해치워줘!!!\n",
       "A군은 깨달았다.자신이 받은 것은 버프와 디버프 마법만 가능한 지원가인 것을...\n\n"
       "하지만 용사는 필요했다.자신을 강하게 만들어줄 지원가를!\n\n"
       "용사는 파티 합류를 제안함과 동시에 마왕을 쓰러뜨리면 소원을 빌 수 있다고 말한다.\n\n"
       "마왕을 쓰러뜨리면 소원을 이뤄준다고? 집에 돌아갈 수 있는 거야 ???\n\n"
       "그렇게 용사 파티에 지원가로 합류한 A군! 시간은 흘러 결국 마왕을 잡으러 마왕성까지 도달한다.\n\n"
       "빨리 처리해 용사! 나 과제 제출해야 한다고!!!\n\n",
       "용사의 마지막 참격에 마왕은 결국 무릎을 꿇었다.\n\n"
       "마왕을 물리치고 얼마 안 지나 하늘에서 빛이 나오고 이세계의 신이 내려왔다.\n\n"
       "내 소원은 ......\n\n"
       "대한민국, 내 진짜 고향으로 보내줘!\n\n"
       "소원을 빌고 눈을 깜빡이니 익숙하고 그리웠던 형광등이 나를 비추고 있었다.\n\n"
       "그리움의 향수에 젖을 새 없이, 노트북으로 달려갔다.\n\n"
       "제발 현실의 시간이 많이 지나지 않았기를... 어 ? 종강...... 이라고 ? \n\n"
    };
    printf("-----------------------------------------Story-----------------------------------------\n\n");
    const char* selectedStory = story[storyNum - 1];
    for (int i = 0; selectedStory[i] != '\0'; i++) {
        putchar(selectedStory[i]);
        fflush(stdout);
        Sleep(40);
    }
    printf("\n\n---------------------------------------------------------------------------------------\n\n");
    Sleep(1000);
    system("cls");

}
// 버프 스택 관련 함수
int Stack_Is_Empty(Skill_LinkedStackType* skill_stack) { // top이 가르키는 노드가 없으면 false
    return (skill_stack->top == NULL);
}

int skill_stack_pop(Skill_LinkedStackType* skill_stack) { // 스택에서 pop하는 함수
    if (Stack_Is_Empty(skill_stack) == 1) {
        return 0;
    }
    else {
        Skill_StackNode* tmp = skill_stack->top;
        int b = tmp->skill;
        skill_stack->top = skill_stack->top->link;
        free(tmp);
        return b;
    }
}

void skill_stack_push(Skill_LinkedStackType* skill_stack, int b)
{
    Skill_StackNode* tmp = (Skill_StackNode*)malloc(sizeof(Skill_StackNode));
    tmp->skill = b;
    tmp->link = skill_stack->top;
    skill_stack->top = tmp;
}

// 몬스터 큐 관련 함수
int Monster_Is_Empty(Monster_LinkedQueueType* monster_queue)
{
    return ((monster_queue->rear == NULL) && (monster_queue->front == NULL));
}

void Monster_enqueue(Monster_LinkedQueueType* monster_queue, Monster monster)
{
    Monster_Queue_Node* temp = (Monster_Queue_Node*)malloc(sizeof(Monster_Queue_Node));
    temp->QueueElements = monster;
    temp->link = NULL;
    if (Monster_Is_Empty(monster_queue)) {
        monster_queue->front = temp;
        monster_queue->rear = temp;
    }
    else {
        monster_queue->rear->link = temp;
        monster_queue->rear = temp;
    }
}

Monster monster_dequeue(Monster_LinkedQueueType* monster_queue)
{
    Monster_Queue_Node* temp = monster_queue->front;
    Monster m;
    if (Monster_Is_Empty(monster_queue)) {
        printf("누가 마왕을 물리쳤대...!");
        exit(1);
    }
    else {
        m = temp->QueueElements;
        monster_queue->front = monster_queue->front->link;
        if (monster_queue->front == NULL) {
            monster_queue->rear = NULL;
        }
        free(temp);
        return m;
    }
}

//스테이지에 맞춰 몬스터의 종류와 정보들을 담는 함수들
void tutorial_monster_Queue(Monster_LinkedQueueType* monster_queue) // 튜토리얼 스테이지 몬스터 큐
{
    Monster slime;
    slime.hp = 1;
    strcpy(slime.name, "슬라임");
    slime.max_skill = 2;

    for (int i = 0; i < 1; i++)
    {
        Monster_enqueue(monster_queue, slime);
    }
}

void stage1_monster_Queue(Monster_LinkedQueueType* monster_queue) { // 스테이지 1 몬스터 큐
    Monster slime;
    Monster goblin;

    slime.hp = 1;
    goblin.hp = 2;
    strcpy(slime.name, "슬라임");
    strcpy(goblin.name, "고블린");
    slime.max_skill = 2;
    goblin.max_skill = 3;

    for (int i = 0; i < 2; i++)
    {
        Monster_enqueue(monster_queue, slime);
    }

    Monster_enqueue(monster_queue, goblin);
}

void stage2_monster_Queue(Monster_LinkedQueueType* monster_queue) { // 스테이지 2 몬스터 큐
    Monster Oak;
    Monster goblin;

    Oak.hp = 3;
    goblin.hp = 2;
    strcpy(Oak.name, "오크");
    strcpy(goblin.name, "고블린");
    Oak.max_skill = 4;
    goblin.max_skill = 3;

    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, goblin);
    }
    Monster_enqueue(monster_queue, Oak);

}

void stage3_monster_Queue(Monster_LinkedQueueType* monster_queue) { // 스테이지 3 몬스터 큐
    Monster Oak;
    Monster Dracula;

    Oak.hp = 3;
    Dracula.hp = 4;
    strcpy(Oak.name, "오크");
    strcpy(Dracula.name, "드라큘라 백작");
    Oak.max_skill = 4;
    Dracula.max_skill = 5;

    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, Oak);
    }
    Monster_enqueue(monster_queue, Dracula);
}

void stage4_monster_Queue(Monster_LinkedQueueType* monster_queue) { // 스테이지 4 몬스터 큐
    Monster Devil_King;
    Monster Dracula;

    Devil_King.hp = 5;
    Dracula.hp = 4;
    strcpy(Devil_King.name, "마왕");
    strcpy(Dracula.name, "드라큘라 백작");
    Devil_King.max_skill = 10;
    Dracula.max_skill = 5;


    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, Dracula);
    }
    Monster_enqueue(monster_queue, Devil_King);
}

// 전투상황 인터페이스
void battleState(Player player, Monster monster)
{
    printf("용사의 체력: %d\n", player.hp);
    printf("%s의 체력: %d\n\n", monster.name, monster.hp);
}

void stage_push(Stage_Stack* stage_stack, TreeNode* p)
{
    if (stage_stack->top < MAX_QUEST_SIZE - 1)
        stage_stack->stack[++(stage_stack->top)] = p;
}

TreeNode* stage_pop(Stage_Stack* stage_stack)
{
    TreeNode* p = NULL;
    if (stage_stack->top > -1)
        p = stage_stack->stack[(stage_stack->top)--];
    return p;
}

void preorder_iter(Stage_Stack* stage_stack, TreeNode* root)
{
    TreeNode* p;
    //if (root == NULL)
        //return NULL;
    stage_push(stage_stack, root);

    while (stage_stack->top > -1)
    {
        p = stage_pop(stage_stack);
        printf("%s", p->monster);

        if (p->right != NULL)
            stage_push(stage_stack, p->right);
        if (p->left != NULL)
            stage_push(stage_stack, p->left);
    }
}

void start_stage1() // 스테이지 1 설명 트리
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2마리 ", NULL, NULL };
    TreeNode node2 = { "(체력 : 1) ", NULL, NULL };
    TreeNode node3 = { "1마리 ", NULL, NULL };
    TreeNode node4 = { "(체력 : 2) ", NULL, NULL };
    TreeNode node5 = { "슬라임 ", &node1, &node2 };
    TreeNode node6 = { "고블린 ", &node3, &node4 };
    TreeNode root = { "앗! 야생의 몬스터들이 나타났다!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage2() // 스테이지 2 설명 트리
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2마리 ", NULL, NULL };
    TreeNode node2 = { "(체력 : 2) ", NULL, NULL };
    TreeNode node3 = { "1마리 ", NULL, NULL };
    TreeNode node4 = { "(체력 : 3) ", NULL, NULL };
    TreeNode node5 = { "고블린 ", &node1, &node2 };
    TreeNode node6 = { "오크 ", &node3, &node4 };
    TreeNode root = { "마왕성까지 앞으로 한 걸음, 근데 나타난 마왕 1소대?\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage3() // 스테이지 3 설명 트리
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2마리 ", NULL, NULL };
    TreeNode node2 = { "(체력 : 3) ", NULL, NULL };
    TreeNode node3 = { "1마리 ", NULL, NULL };
    TreeNode node4 = { "(체력 : 4) ", NULL, NULL };
    TreeNode node5 = { "오크 ", &node1, &node2 };
    TreeNode node6 = { "드라큘라 백작 ", &node3, &node4 };
    TreeNode root = { "드디어 마왕성! 위험한 몬스터 천지잖아...!모두 조심해!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage4() // 스테이지 4 설명 트리
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2마리 ", NULL, NULL };
    TreeNode node2 = { "(체력 : 4) ", NULL, NULL };
    TreeNode node3 = { "바알 ", NULL, NULL };
    TreeNode node4 = { "(체력 : 5) ", NULL, NULL };
    TreeNode node5 = { "드라큘라 백작 ", &node1, &node2 };
    TreeNode node6 = { "마왕성의 주인 ", &node3, &node4 };
    TreeNode root = { "이 앞에 엄청난 기운이 느껴져... 우리의 모험이 끝에 도달한 것 같아...!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}


//게임 관련 인터페이스 함수
int stage(int stage_level) { // 게임 시작 함수
    Player player; // 변수 선언
    Monster monster;
    Monster_LinkedQueueType monster_queue;
    Skill_LinkedStackType player_skill_stack;
    Skill_LinkedStackType monster_skill_stack;
    stack_init(&player_skill_stack);
    stack_init(&monster_skill_stack);
    queue_init(&monster_queue);

    int count = 0; // 사용자가 알맞은 버프를 사용하는지 확인 하는 변수
    int use_skill;
    srand(time(0)); //현재 시간을 기반으로 난수 생성

    if (stage_level == 1) { // 스테이지에 맞춰 몬스터 큐에 몬스터 삽입
        printf("튜토리얼을 시작합니다!\n");
        stage0();
        tutorial_monster_Queue(&monster_queue);
        player.hp = 2;
    }

    else if (stage_level == 2) {
        stage1();
        stage1_monster_Queue(&monster_queue);
        player.hp = 3;
    }

    else if (stage_level == 3) {
        stage2();
        stage2_monster_Queue(&monster_queue);
        player.hp = 4;
    }

    else if (stage_level == 4) {
        stage3();
        stage3_monster_Queue(&monster_queue);
        player.hp = 5;
    }

    else if (stage_level == 5) {
        stage4();
        stage4_monster_Queue(&monster_queue);
        player.hp = 5;
    }

    while (Monster_Is_Empty(&monster_queue) == 0) {
        printf("용사파티가 이동합니다.\n");
        Sleep(1000);
        monster = monster_dequeue(&monster_queue); // 몬스터 출현
        if (stage_level == 2) {
            start_stage1();
        }
        else if (stage_level == 3) {
            start_stage2();
        }
        else if (stage_level == 4) {
            start_stage3();
        }
        else if (stage_level == 5) {
            start_stage4();
        }
        printf("%s 등장!\n", monster.name);
        Sleep(200);
        battleState(player, monster);
        Sleep(200);

        while (monster.hp != 0) { // 몬스터의 체력이 0이 될때 까지 반복
            for (int i = 0; i < monster.max_skill; i++) { // 몬스터의 최대 버프 사용 가능만큼 버프 사용
                int random_monster_skill = (rand() % monster.max_skill) + 1; //몬스터가 사용할 수 있는 버프에 맞춰 랜덤 버프 사용
                if (random_monster_skill >= 6) {
                    random_monster_skill = rand() % 5 + 1;
                }

                switch (monster.max_skill)
                {
                case 2:   // 슬라임 스킬
                    if (random_monster_skill == 1) {
                        printf("%s은(는) 단단해지기를 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s은(는) 저주를 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 3:   // 고블린 스킬
                    if (random_monster_skill == 1) {
                        printf("%s은(는) 천갑옷을 입으려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s은(는) 오물을 던지려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s은(는) 포효를 하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 4:   // 오크 스킬
                    if (random_monster_skill == 1) {
                        printf("%s은(는) 신체를 단련하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s은(는) 기절을 걸려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s은(는) 포효를 하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s은(는) 독가스 공격을 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 5:   // 드라큘라 백작 스킬
                    if (random_monster_skill == 1) {
                        printf("%s은(는) 피의 탄환을 쏠려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s은(는) 강력한 할퀴기 공격을 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s은(는) 비명을 지르려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s은(는) 독약을 던지려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 5) {
                        printf("%s은(는) 흡혈을 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 10:   // 마왕 스킬
                    if (random_monster_skill == 1) {
                        printf("%s은(는) 프레셔를 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s은(는) 마왕의 갑주를 입으려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s은(는) 응축된 피의 탄환을 쏠려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s은(는) 기습공격을 하려고 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 5) {
                        printf("%s은(는) 마왕의 숨결을 사용하려 한다!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;
                }


            }
            printf("\n위험해! 적이 사용하려한 스킬에 대비해 버프 스킬을 사용하자!\n");

            if (1 <= monster.max_skill && monster.max_skill < 5) // 슬라임, 고블린, 오크와 전투
            {
                for (int i = 0; i < monster.max_skill;) { // 플레이어 버프 입력
                    use_skill = 0;
                    printf("1. 방어력 저하, 2. 정화, 3. 침묵, 4. 해독, 5. 마법 방어력 증가");
                    use_skill = _getch() - '0'; // 엔터 필요없이 입력

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t방어력 저하 선택!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t정화 선택!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\t침묵 선택!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t해독 선택!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t마법 방어력 증가 선택!\n\n");
                        }
                        i++; //잘못된 숫자 무시
                    }
                    else {
                        printf("\t다시 입력해주세요(1~5)!\n\n");
                    }
                    skill_stack_push(&player_skill_stack, use_skill);
                }
            }

            else if (monster.max_skill == 5)   // 드라큘라 백작과 전투
            {
                for (int i = 0; i < monster.max_skill;) { // 플레이어 버프 입력
                    use_skill = 0;
                    printf("1. 혈액 분해, 2. 방어력 증가, 3. 침묵, 4. 해독, 5. 강인한 신체");
                    use_skill = _getch() - '0'; // 엔터 필요없이 입력

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t혈액 분해 선택!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t방어력 증가 선택!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\t침묵 선택!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t해독 선택!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t강인한 신체 선택!\n\n");
                        }
                        i++; //잘못된 숫자 무시
                    }
                    else {
                        printf("\t다시 입력해주세요(1~5)!\n\n");
                    }
                    skill_stack_push(&player_skill_stack, use_skill);
                }
            }

            else if (monster.max_skill == 10)   // 마왕과 전투
            {
                for (int i = 0; i < monster.max_skill;) { // 플레이어 버프 입력
                    use_skill = 0;
                    printf("1. 정화 + 침묵, 2. 방어력 감소 + 마법 방어력 감소, 3. 혈액 분해 + 마법 방어력 증가, 4. 속도 감소 + 공격력 감소, 5. 마법 방어력 증가 * 2");
                    use_skill = _getch() - '0'; // 엔터 필요없이 입력

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t정화 + 침묵 선택!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t방어력 감소 + 마법 방어력 감소 선택!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\t혈액 분해 + 마법 방어력 증가 선택!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t속도 감소 + 공격력 감소 선택!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t마법 방어력 증가 * 2 선택!\n\n");
                        }
                        i++; //잘못된 숫자 무시
                    }
                    else {
                        printf("\t다시 입력해주세요(1~5)!\n\n");
                    }
                    skill_stack_push(&player_skill_stack, use_skill);
                }
            }

            for (int i = 0; i < monster.max_skill; i++) {
                if ((skill_stack_pop(&monster_skill_stack) == skill_stack_pop(&player_skill_stack))) {
                    count++;
                }
            }
            if (count == monster.max_skill) {
                printf("\n잘했어! 몬스터가 방심한 사이 공격하자!\n");
                monster.hp--;
                battleState(player, monster);
                Sleep(1000);
                if (monster.hp == 0) {
                    printf("%s은(는) 쓰러졌다.\n", monster.name);
                    printf("좋아 몬스터를 쓰러트렸으니깐 앞으로 나아가자.\n");
                }
                Sleep(1000);
                system("cls");
            }
            else {
                printf("\n실수한 것 같아 어떡하지... 어떡하지....\n");
                printf("으악!\n");
                player.hp--;
                battleState(player, monster);
                if (player.hp == 0) {
                    defeat();
                    return 0;
                }
                else {
                    printf("용사의 체력이 감소했습니다\n");
                    printf("남은 체력 : %d\n", player.hp);
                    Sleep(2000);
                    system("cls");
                }
            }
            count = 0;
        }
    }
    victory();
    Sleep(2000);
    return 1;
}

void win() { // 마왕을 이겼을 때
    printf("마왕을 무찔렀습니다!\n");
    Sleep(2000);
    game_story(3);
}
void lose() { // 몬스터한테 졌을 때
    printf("몬스터에게 패배해 용사가 죽었습니다...\n다음 용사를 찾으러 가볼까요.....?\n\n");
    Sleep(1000);
}

void stage_judgement() { //  스테이지와 플레이어의 승패를 구분하는 함수
    int stage_jment = 1; // 현재 스테이지 판단 처음 시작 시 스테이지 1
    int next_stage = 0; // 다음 스테이지로 넘어갈지 판단하는 변수
    while (1) {
        if (stage_jment == 1) {
            next_stage = stage(1);

            if (next_stage == 1) {
                stage_jment += 1;
            }

            else {
                lose();
                break;
            }
        }

        else if (stage_jment == 2) {
            Sleep(2000);
            game_story(2);
            next_stage = stage(2);
            if (next_stage == 1) {
                stage_jment += 1;
            }
            else {
                lose();
                break;
            }
        }
        else if (stage_jment == 3) {
            next_stage = stage(3);
            if (next_stage == 1) {
                stage_jment += 1;
            }
            else {
                lose();
                break;
            }
        }
        else if (stage_jment == 4) {
            next_stage = stage(4);
            if (next_stage == 1) {
                stage_jment += 1;
            }
            else {
                lose();
                break;
            }
        }
        else if (stage_jment == 5) {
            next_stage = stage(5);
            if (next_stage == 1) {
                win();
                break;
            }
            else {
                lose();
                break;
            }
        }
    }
}

void game_rule()        // 게임 규칙 출력
{
    printf("게임의 룰은 이렇습니다!\n\n");
    printf("1. 게임 시작 후, 플레이어는 스테이지에 진입하고 스테이지의 몬스터가 출현합니다!\n\n");
    printf("2. 스테이지 당 몬스터는 총 3마리로, 용사와 몬스터 1마리 1vs1 전투를 치르게 됩니다.\n\n");
    printf("3. 먼저 몬스터가 스킬을 사용하면 플레이어는 용사에게 몬스터가 사용한 스킬에 맞게 버프나 디버프 스킬을 사용합니다.\n");
    printf("EX) 슬라임이 저주를 걸었을 경우, 이를 해제하기 위해 정화 스킬 사용이 적절합니다..\n\n");
    printf("4. 몬스터의 스킬을 전부 알맞게 카운터 쳤을 경우 몬스터의 체력(HP)은 1 감소합니다.\n\n");
    printf("5. 몬스터의 체력(HP)이 0이 됐을 경우, 다음 몬스터와 전투가 진행되고 해당 스테이지의 몬스터를 전부 제거했을 경우 다음 스테이지로 이동합니다. \n\n");
    printf("6. 스테이지를 정복하면서 최종 마왕까지 쓰러뜨리는 것이 게임의 목표입니다.\n\n");
    printf("자 이제 들어가십쇼! 전장의 시간으로!!!\n");
    Sleep(1000);
    printf("아무 키나 입력하세요.");
#pragma warning(disable:4996)                   //getch 오류 무시
    if (getch()) {
        system("cls");
    }
}

int main(int argc, char** argv) {

    HWND consoleWindow = GetConsoleWindow();
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    SetWindowPos(consoleWindow, 0, screenWidth / 2, screenHeight / 4 - 40, screenWidth / 2, screenHeight / 2 + 30, SWP_NOZORDER);
    int choice;

    while (TRUE) {

        printf("마왕을 물리쳐야 하지만 버프 스킬 밖에 못쓰니 용사에게 버프를 겁니다!\n\n");
        printf("골라 주세요 1. 게임 시작, 2. 게임 규칙, 3. 게임 종료");
        choice = _getch() - '0';  // 엔터 필요 없이 입력

        if (choice >= 1 && choice <= 3)
        {
            printf("\t%d번 선택!\n\n", choice);

            if (choice == 1) {
                game_story(1);
                stage_judgement();
            }

            else if (choice == 2) {
                game_rule();
            }

            else if (choice == 3) {
                break;
            }
        }
        else
        {
            printf("\n올바른 번호를 입력해주세요\n\n");
        }
    }
    return 0;
}