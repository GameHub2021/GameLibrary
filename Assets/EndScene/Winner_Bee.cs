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
        this.animator = GetComponent<Animator>();                                           // �� �ִϸ��̼� 
        InvokeRepeating("Bee_Anime", 1.0f, 2.0f);                                           // �� �ִϸ��̼� 3�ʸ��� ���
    }

    void Bee_Anime()
    {
        this.animator.SetTrigger("WalkTrigger");                                            // ���丮 ��� �� �� �ִϸ��̼� ���
    }
}
