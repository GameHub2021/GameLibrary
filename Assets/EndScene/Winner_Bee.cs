using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Winner_Bee : MonoBehaviour
{
    Animator animator;

    void Start()
    {
        Application.targetFrameRate = 60;
        this.animator = GetComponent<Animator>();                                           // 벌 애니메이션 
        InvokeRepeating("Bee_Anime", 1.0f, 2.0f);                                           // 벌 애니메이션 3초마다 재생
    }

    void Bee_Anime()
    {
        this.animator.SetTrigger("WalkTrigger");                                            // 스토리 출력 시 벌 애니메이션 재생
    }
}
