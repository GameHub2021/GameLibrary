#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <Windows.h>
#include <time.h> 
#include <string.h>
#include <stdlib.h> // ���� ����
#include <malloc.h>
#include <conio.h>
#include <SDL.h> // SDL �������
#include <SDL_image.h> // SDL �̹��� �������

#define MAX_QUEST_SIZE 100

SDL_Window* window = NULL;

typedef struct TreeNode {
    char monster[100]; //�������� ���� �̸�
    struct TreeNode* left, * right;
} TreeNode;

typedef struct stage_stack {
    TreeNode* stack[MAX_QUEST_SIZE];
    int top;
} Stage_Stack;

// ����ü ����
typedef struct skill_StackNode {//���� ����ü
    int skill;
    struct skill_StackNode* link;
}Skill_StackNode;

typedef struct Skill_LinkedStackType {
    Skill_StackNode* top;
}Skill_LinkedStackType;

typedef struct player { //�÷��̾� ����ü
    int hp;
}Player;

typedef struct Monster { // ���� ����ü
    int hp; // ���� ü��
    char name[15]; // ���� �̸�
    int max_skill; // ���Ͱ� ��밡���� ���� Ƚ��
}Monster;

typedef struct Monster_Queue_Node { // ���� ť ����ü
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

int stage0()                // Ʃ�丮�� �������� SDL ���
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

int stage1()                // ��������1 SDL ���
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

int stage2()                // ��������2 SDL ���
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

int stage3()                // ��������3 SDL ���
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

int stage4()                // ��������4 SDL ���
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

int victory()                // �¸�â SDL ���
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

int defeat()                // �й�â SDL ���
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


//���� �� �ʱ�ȭ �Լ���
void stack_init(Skill_LinkedStackType* skill_stack) {
    skill_stack->top = NULL;
}
void queue_init(Monster_LinkedQueueType* monster_queue) {
    monster_queue->front = NULL;
    monster_queue->rear = NULL;
}
void game_story(int storyNum) {
    const char* story[] = {
       "���õ� ������ ������ ���� ������� �ڵ��� �ϰ� �ִ� ���� ����� A��...\n\n"
       "Ŀ�Ǹ� Ÿ�� �ξ��� ���� ���� �ٴڿ� �̲����� �׸� �Ӹ��� �ʴ�!!!\n\n"
       "������ ������ ���� ���� �� ���� �� ���� õ��... ���� ������????? �� �̼��迡 �������ž�?\n\n"
       "������ ����...... ������ ������ �������� ��ġ�� ���� ������ �ҽ��� A��!\n\n"
       "�߾� �ٰ����� ��! �� �����ٰ�!!! �ٰ����� �������� �����ϱ� ���� ���� ���� ����?\n\n"
       "�������� �������� ? ? ? �ٵ� �� ���� ������ �ȳ��� ? ? ? \n\n"
       "������ A���� �ҽ��� ������ �ݿ��� ���ϱ�?? ���� ������ ������ �Ҳɵ� ������ �ʴµ�...\n\n"
       "�׶�, ������ �̼����� ���! �������� óġ�ϱ� ���� ���� �̾Ƶ��.\n\n"
       "A���� ��縦 �����ϱ� �����ϴµ�, ����� ���� �������� �����Ѵ�...?\n\n"
       "���� ����! ��ġ����!!!\n",
       "A���� ���޾Ҵ�.�ڽ��� ���� ���� ������ ����� ������ ������ �������� ����...\n\n"
       "������ ���� �ʿ��ߴ�.�ڽ��� ���ϰ� ������� ��������!\n\n"
       "���� ��Ƽ �շ��� �����԰� ���ÿ� ������ �����߸��� �ҿ��� �� �� �ִٰ� ���Ѵ�.\n\n"
       "������ �����߸��� �ҿ��� �̷��شٰ�? ���� ���ư� �� �ִ� �ž� ???\n\n"
       "�׷��� ��� ��Ƽ�� �������� �շ��� A��! �ð��� �귯 �ᱹ ������ ������ ���ռ����� �����Ѵ�.\n\n"
       "���� ó���� ���! �� ���� �����ؾ� �Ѵٰ�!!!\n\n",
       "����� ������ ���ݿ� ������ �ᱹ ������ �ݾ���.\n\n"
       "������ ����ġ�� �� �� ���� �ϴÿ��� ���� ������ �̼����� ���� �����Դ�.\n\n"
       "�� �ҿ��� ......\n\n"
       "���ѹα�, �� ��¥ �������� ������!\n\n"
       "�ҿ��� ���� ���� �����̴� �ͼ��ϰ� �׸����� �������� ���� ���߰� �־���.\n\n"
       "�׸����� ����� ���� �� ����, ��Ʈ������ �޷�����.\n\n"
       "���� ������ �ð��� ���� ������ �ʾұ⸦... �� ? ����...... �̶�� ? \n\n"
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
// ���� ���� ���� �Լ�
int Stack_Is_Empty(Skill_LinkedStackType* skill_stack) { // top�� ����Ű�� ��尡 ������ false
    return (skill_stack->top == NULL);
}

int skill_stack_pop(Skill_LinkedStackType* skill_stack) { // ���ÿ��� pop�ϴ� �Լ�
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

// ���� ť ���� �Լ�
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
        printf("���� ������ �����ƴ�...!");
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

//���������� ���� ������ ������ �������� ��� �Լ���
void tutorial_monster_Queue(Monster_LinkedQueueType* monster_queue) // Ʃ�丮�� �������� ���� ť
{
    Monster slime;
    slime.hp = 1;
    strcpy(slime.name, "������");
    slime.max_skill = 2;

    for (int i = 0; i < 1; i++)
    {
        Monster_enqueue(monster_queue, slime);
    }
}

void stage1_monster_Queue(Monster_LinkedQueueType* monster_queue) { // �������� 1 ���� ť
    Monster slime;
    Monster goblin;

    slime.hp = 1;
    goblin.hp = 2;
    strcpy(slime.name, "������");
    strcpy(goblin.name, "���");
    slime.max_skill = 2;
    goblin.max_skill = 3;

    for (int i = 0; i < 2; i++)
    {
        Monster_enqueue(monster_queue, slime);
    }

    Monster_enqueue(monster_queue, goblin);
}

void stage2_monster_Queue(Monster_LinkedQueueType* monster_queue) { // �������� 2 ���� ť
    Monster Oak;
    Monster goblin;

    Oak.hp = 3;
    goblin.hp = 2;
    strcpy(Oak.name, "��ũ");
    strcpy(goblin.name, "���");
    Oak.max_skill = 4;
    goblin.max_skill = 3;

    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, goblin);
    }
    Monster_enqueue(monster_queue, Oak);

}

void stage3_monster_Queue(Monster_LinkedQueueType* monster_queue) { // �������� 3 ���� ť
    Monster Oak;
    Monster Dracula;

    Oak.hp = 3;
    Dracula.hp = 4;
    strcpy(Oak.name, "��ũ");
    strcpy(Dracula.name, "���ŧ�� ����");
    Oak.max_skill = 4;
    Dracula.max_skill = 5;

    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, Oak);
    }
    Monster_enqueue(monster_queue, Dracula);
}

void stage4_monster_Queue(Monster_LinkedQueueType* monster_queue) { // �������� 4 ���� ť
    Monster Devil_King;
    Monster Dracula;

    Devil_King.hp = 5;
    Dracula.hp = 4;
    strcpy(Devil_King.name, "����");
    strcpy(Dracula.name, "���ŧ�� ����");
    Devil_King.max_skill = 10;
    Dracula.max_skill = 5;


    for (int i = 0; i < 2; i++) {
        Monster_enqueue(monster_queue, Dracula);
    }
    Monster_enqueue(monster_queue, Devil_King);
}

// ������Ȳ �������̽�
void battleState(Player player, Monster monster)
{
    printf("����� ü��: %d\n", player.hp);
    printf("%s�� ü��: %d\n\n", monster.name, monster.hp);
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

void start_stage1() // �������� 1 ���� Ʈ��
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2���� ", NULL, NULL };
    TreeNode node2 = { "(ü�� : 1) ", NULL, NULL };
    TreeNode node3 = { "1���� ", NULL, NULL };
    TreeNode node4 = { "(ü�� : 2) ", NULL, NULL };
    TreeNode node5 = { "������ ", &node1, &node2 };
    TreeNode node6 = { "��� ", &node3, &node4 };
    TreeNode root = { "��! �߻��� ���͵��� ��Ÿ����!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage2() // �������� 2 ���� Ʈ��
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2���� ", NULL, NULL };
    TreeNode node2 = { "(ü�� : 2) ", NULL, NULL };
    TreeNode node3 = { "1���� ", NULL, NULL };
    TreeNode node4 = { "(ü�� : 3) ", NULL, NULL };
    TreeNode node5 = { "��� ", &node1, &node2 };
    TreeNode node6 = { "��ũ ", &node3, &node4 };
    TreeNode root = { "���ռ����� ������ �� ����, �ٵ� ��Ÿ�� ���� 1�Ҵ�?\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage3() // �������� 3 ���� Ʈ��
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2���� ", NULL, NULL };
    TreeNode node2 = { "(ü�� : 3) ", NULL, NULL };
    TreeNode node3 = { "1���� ", NULL, NULL };
    TreeNode node4 = { "(ü�� : 4) ", NULL, NULL };
    TreeNode node5 = { "��ũ ", &node1, &node2 };
    TreeNode node6 = { "���ŧ�� ���� ", &node3, &node4 };
    TreeNode root = { "���� ���ռ�! ������ ���� õ���ݾ�...!��� ������!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}

void start_stage4() // �������� 4 ���� Ʈ��
{
    Stage_Stack* stage_stack = (Stage_Stack*)malloc(sizeof(Stage_Stack));
    memset(stage_stack, 0, sizeof(Stage_Stack));
    stage_stack->top = -1;
    TreeNode node1 = { "2���� ", NULL, NULL };
    TreeNode node2 = { "(ü�� : 4) ", NULL, NULL };
    TreeNode node3 = { "�پ� ", NULL, NULL };
    TreeNode node4 = { "(ü�� : 5) ", NULL, NULL };
    TreeNode node5 = { "���ŧ�� ���� ", &node1, &node2 };
    TreeNode node6 = { "���ռ��� ���� ", &node3, &node4 };
    TreeNode root = { "�� �տ� ��û�� ����� ������... �츮�� ������ ���� ������ �� ����...!\n", &node5, &node6 };
    preorder_iter(stage_stack, &root);
    printf("\n\n");
    return;
}


//���� ���� �������̽� �Լ�
int stage(int stage_level) { // ���� ���� �Լ�
    Player player; // ���� ����
    Monster monster;
    Monster_LinkedQueueType monster_queue;
    Skill_LinkedStackType player_skill_stack;
    Skill_LinkedStackType monster_skill_stack;
    stack_init(&player_skill_stack);
    stack_init(&monster_skill_stack);
    queue_init(&monster_queue);

    int count = 0; // ����ڰ� �˸��� ������ ����ϴ��� Ȯ�� �ϴ� ����
    int use_skill;
    srand(time(0)); //���� �ð��� ������� ���� ����

    if (stage_level == 1) { // ���������� ���� ���� ť�� ���� ����
        printf("Ʃ�丮���� �����մϴ�!\n");
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
        printf("�����Ƽ�� �̵��մϴ�.\n");
        Sleep(1000);
        monster = monster_dequeue(&monster_queue); // ���� ����
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
        printf("%s ����!\n", monster.name);
        Sleep(200);
        battleState(player, monster);
        Sleep(200);

        while (monster.hp != 0) { // ������ ü���� 0�� �ɶ� ���� �ݺ�
            for (int i = 0; i < monster.max_skill; i++) { // ������ �ִ� ���� ��� ���ɸ�ŭ ���� ���
                int random_monster_skill = (rand() % monster.max_skill) + 1; //���Ͱ� ����� �� �ִ� ������ ���� ���� ���� ���
                if (random_monster_skill >= 6) {
                    random_monster_skill = rand() % 5 + 1;
                }

                switch (monster.max_skill)
                {
                case 2:   // ������ ��ų
                    if (random_monster_skill == 1) {
                        printf("%s��(��) �ܴ������⸦ ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s��(��) ���ָ� ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 3:   // ��� ��ų
                    if (random_monster_skill == 1) {
                        printf("%s��(��) õ������ �������� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s��(��) ������ �������� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s��(��) ��ȿ�� �Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 4:   // ��ũ ��ų
                    if (random_monster_skill == 1) {
                        printf("%s��(��) ��ü�� �ܷ��Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s��(��) ������ �ɷ��� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s��(��) ��ȿ�� �Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s��(��) ������ ������ ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 5:   // ���ŧ�� ���� ��ų
                    if (random_monster_skill == 1) {
                        printf("%s��(��) ���� źȯ�� ����� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s��(��) ������ ������ ������ ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s��(��) ����� ������ �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s��(��) ������ �������� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 5) {
                        printf("%s��(��) ������ ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;

                case 10:   // ���� ��ų
                    if (random_monster_skill == 1) {
                        printf("%s��(��) �����Ÿ� ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 2) {
                        printf("%s��(��) ������ ���ָ� �������� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 3) {
                        printf("%s��(��) ����� ���� źȯ�� ����� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 4) {
                        printf("%s��(��) ��������� �Ϸ��� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    else if (random_monster_skill == 5) {
                        printf("%s��(��) ������ ������ ����Ϸ� �Ѵ�!\n", monster.name);
                        skill_stack_push(&monster_skill_stack, random_monster_skill);
                        Sleep(200);
                    }

                    break;
                }


            }
            printf("\n������! ���� ����Ϸ��� ��ų�� ����� ���� ��ų�� �������!\n");

            if (1 <= monster.max_skill && monster.max_skill < 5) // ������, ���, ��ũ�� ����
            {
                for (int i = 0; i < monster.max_skill;) { // �÷��̾� ���� �Է�
                    use_skill = 0;
                    printf("1. ���� ����, 2. ��ȭ, 3. ħ��, 4. �ص�, 5. ���� ���� ����");
                    use_skill = _getch() - '0'; // ���� �ʿ���� �Է�

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t���� ���� ����!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t��ȭ ����!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\tħ�� ����!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t�ص� ����!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t���� ���� ���� ����!\n\n");
                        }
                        i++; //�߸��� ���� ����
                    }
                    else {
                        printf("\t�ٽ� �Է����ּ���(1~5)!\n\n");
                    }
                    skill_stack_push(&player_skill_stack, use_skill);
                }
            }

            else if (monster.max_skill == 5)   // ���ŧ�� ���۰� ����
            {
                for (int i = 0; i < monster.max_skill;) { // �÷��̾� ���� �Է�
                    use_skill = 0;
                    printf("1. ���� ����, 2. ���� ����, 3. ħ��, 4. �ص�, 5. ������ ��ü");
                    use_skill = _getch() - '0'; // ���� �ʿ���� �Է�

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t���� ���� ����!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t���� ���� ����!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\tħ�� ����!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t�ص� ����!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t������ ��ü ����!\n\n");
                        }
                        i++; //�߸��� ���� ����
                    }
                    else {
                        printf("\t�ٽ� �Է����ּ���(1~5)!\n\n");
                    }
                    skill_stack_push(&player_skill_stack, use_skill);
                }
            }

            else if (monster.max_skill == 10)   // ���հ� ����
            {
                for (int i = 0; i < monster.max_skill;) { // �÷��̾� ���� �Է�
                    use_skill = 0;
                    printf("1. ��ȭ + ħ��, 2. ���� ���� + ���� ���� ����, 3. ���� ���� + ���� ���� ����, 4. �ӵ� ���� + ���ݷ� ����, 5. ���� ���� ���� * 2");
                    use_skill = _getch() - '0'; // ���� �ʿ���� �Է�

                    if (1 <= use_skill && use_skill <= 5) {
                        if (use_skill == 1)
                        {
                            printf("\t��ȭ + ħ�� ����!\n\n");
                        }
                        else if (use_skill == 2)
                        {
                            printf("\t���� ���� + ���� ���� ���� ����!\n\n");
                        }
                        else if (use_skill == 3)
                        {
                            printf("\t���� ���� + ���� ���� ���� ����!\n\n");
                        }
                        else if (use_skill == 4)
                        {
                            printf("\t�ӵ� ���� + ���ݷ� ���� ����!\n\n");
                        }
                        else if (use_skill == 5)
                        {
                            printf("\t���� ���� ���� * 2 ����!\n\n");
                        }
                        i++; //�߸��� ���� ����
                    }
                    else {
                        printf("\t�ٽ� �Է����ּ���(1~5)!\n\n");
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
                printf("\n���߾�! ���Ͱ� ����� ���� ��������!\n");
                monster.hp--;
                battleState(player, monster);
                Sleep(1000);
                if (monster.hp == 0) {
                    printf("%s��(��) ��������.\n", monster.name);
                    printf("���� ���͸� ����Ʈ�����ϱ� ������ ���ư���.\n");
                }
                Sleep(1000);
                system("cls");
            }
            else {
                printf("\n�Ǽ��� �� ���� �����... �����....\n");
                printf("����!\n");
                player.hp--;
                battleState(player, monster);
                if (player.hp == 0) {
                    defeat();
                    return 0;
                }
                else {
                    printf("����� ü���� �����߽��ϴ�\n");
                    printf("���� ü�� : %d\n", player.hp);
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

void win() { // ������ �̰��� ��
    printf("������ ���񷶽��ϴ�!\n");
    Sleep(2000);
    game_story(3);
}
void lose() { // �������� ���� ��
    printf("���Ϳ��� �й��� ��簡 �׾����ϴ�...\n���� ��縦 ã���� �������.....?\n\n");
    Sleep(1000);
}

void stage_judgement() { //  ���������� �÷��̾��� ���и� �����ϴ� �Լ�
    int stage_jment = 1; // ���� �������� �Ǵ� ó�� ���� �� �������� 1
    int next_stage = 0; // ���� ���������� �Ѿ�� �Ǵ��ϴ� ����
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

void game_rule()        // ���� ��Ģ ���
{
    printf("������ ���� �̷����ϴ�!\n\n");
    printf("1. ���� ���� ��, �÷��̾�� ���������� �����ϰ� ���������� ���Ͱ� �����մϴ�!\n\n");
    printf("2. �������� �� ���ʹ� �� 3������, ���� ���� 1���� 1vs1 ������ ġ���� �˴ϴ�.\n\n");
    printf("3. ���� ���Ͱ� ��ų�� ����ϸ� �÷��̾�� ��翡�� ���Ͱ� ����� ��ų�� �°� ������ ����� ��ų�� ����մϴ�.\n");
    printf("EX) �������� ���ָ� �ɾ��� ���, �̸� �����ϱ� ���� ��ȭ ��ų ����� �����մϴ�..\n\n");
    printf("4. ������ ��ų�� ���� �˸°� ī���� ���� ��� ������ ü��(HP)�� 1 �����մϴ�.\n\n");
    printf("5. ������ ü��(HP)�� 0�� ���� ���, ���� ���Ϳ� ������ ����ǰ� �ش� ���������� ���͸� ���� �������� ��� ���� ���������� �̵��մϴ�. \n\n");
    printf("6. ���������� �����ϸ鼭 ���� ���ձ��� �����߸��� ���� ������ ��ǥ�Դϴ�.\n\n");
    printf("�� ���� ���ʼ�! ������ �ð�����!!!\n");
    Sleep(1000);
    printf("�ƹ� Ű�� �Է��ϼ���.");
#pragma warning(disable:4996)                   //getch ���� ����
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

        printf("������ �����ľ� ������ ���� ��ų �ۿ� ������ ��翡�� ������ �̴ϴ�!\n\n");
        printf("��� �ּ��� 1. ���� ����, 2. ���� ��Ģ, 3. ���� ����");
        choice = _getch() - '0';  // ���� �ʿ� ���� �Է�

        if (choice >= 1 && choice <= 3)
        {
            printf("\t%d�� ����!\n\n", choice);

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
            printf("\n�ùٸ� ��ȣ�� �Է����ּ���\n\n");
        }
    }
    return 0;
}