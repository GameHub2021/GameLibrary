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
        this.animator = GetComponent<Animator>();                                           // ���� �ִϸ��̼� 
        InvokeRepeating("Ant_Anime", 1.0f, 3.0f);                                           // ���� �ִϸ��̼� 3�ʸ��� ���
    }

    void Ant_Anime()
    {
        this.animator.SetTrigger("AttackTrigger");                                          // ���丮 ��� �� ���� �ִϸ��̼� ���
    }
}
