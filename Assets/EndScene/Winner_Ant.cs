using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Winner_Ant : MonoBehaviour
{
    Animator animator;

    void Start()
    {
        Application.targetFrameRate = 60;
        this.animator = GetComponent<Animator>();                                           // 개미 애니메이션 
        InvokeRepeating("Ant_Anime", 1.0f, 3.0f);                                           // 개미 애니메이션 3초마다 재생
    }

    void Ant_Anime()
    {
        this.animator.SetTrigger("AttackTrigger");                                          // 스토리 출력 시 개미 애니메이션 재생
    }
}
