using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameDirector : MonoBehaviour
{
    GameObject HP_BarPlayer1;
    GameObject HP_BarPlayer2;
    public GameObject Canvas1PWin; // 1P �¸� �̹���
    public GameObject Canvas2PWin; // 2P �¸� �̹���
    public bool isPlayer1ShieldActive = false; // �÷��̾�1 ���� ����
    public bool isPlayer2ShieldActive = false; // �÷��̾�2 ���� ����
    private bool isGamePaused = false;         // ���� ���� ���� Ȯ�ο� �÷���
    public AudioSource audioSource;
    public AudioClip victory;


    void Start()
    {
        this.HP_BarPlayer1 = GameObject.Find("HP_BarPlayer1"); // �÷��̾�1 ü�¹�
        this.HP_BarPlayer2 = GameObject.Find("HP_BarPlayer2"); // �÷��̾�2 ü�¹�
         // Hierarchy���� �̸����� ĵ���� ��������
        Canvas1PWin = GameObject.Find("1p_win");
        Canvas2PWin = GameObject.Find("2p_win");
        // �ʱ� ���¿��� �¸� �̹����� ��Ȱ��ȭ
        if (Canvas1PWin != null) Canvas1PWin.SetActive(false); // 1P �¸� �̹��� ��Ȱ��ȭ
        if (Canvas2PWin != null) Canvas2PWin.SetActive(false); // 2P �¸� �̹��� ��Ȱ��ȭ
        
    }

    public void DecreaseHP1(float damage)
    {
        if (isPlayer1ShieldActive || isGamePaused) return; // �ǵ� Ȱ��ȭ ���� �Ǵ� ���� ���� �� ��ȿȭ

        // ü�� ����
        this.HP_BarPlayer1.GetComponent<Image>().fillAmount -= damage;

        // ü�� 0 üũ
        if (this.HP_BarPlayer1.GetComponent<Image>().fillAmount <= 0)
        {
            ShowWinCanvas(2); // 2P �¸�
        }
    }

    public void DecreaseHP2(float damage)
    {
        if (isPlayer2ShieldActive || isGamePaused) return; // �ǵ� Ȱ��ȭ ���� �Ǵ� ���� ���� �� ��ȿȭ

        // ü�� ����
        this.HP_BarPlayer2.GetComponent<Image>().fillAmount -= damage;

        // ü�� 0 üũ
        if (this.HP_BarPlayer2.GetComponent<Image>().fillAmount <= 0)
        {
            ShowWinCanvas(1); // 1P �¸�
        }
    }

    public void IncreaseHP1(float damage)
    {
        this.HP_BarPlayer1.GetComponent<Image>().fillAmount += damage;
    }

    public void IncreaseHP2(float damage)
    {
        this.HP_BarPlayer2.GetComponent<Image>().fillAmount += damage;
    }

    private void ShowWinCanvas(int winner)
    {
        isGamePaused = true;
        Time.timeScale = 0; // ���� ����

        if (winner == 1 && Canvas1PWin != null)
        {
            Canvas1PWin.SetActive(true); // 1P �¸� �̹��� Ȱ��ȭ
            StartCoroutine(PlayVictoryAndTransition("EndScene1"));
        }
        else if (winner == 2 && Canvas2PWin != null)
        {
            Canvas2PWin.SetActive(true); // 2P �¸� �̹��� Ȱ��ȭ
            StartCoroutine(PlayVictoryAndTransition("EndScene2"));
        }
    }

    private IEnumerator PlayVictoryAndTransition(string sceneName)
    {
        Time.timeScale = 1; // �� ��ȯ �� Ÿ�ӽ����� ����

        if (audioSource != null && victory != null)
        {
            audioSource.PlayOneShot(victory); // �¸� ����� ���
            yield return new WaitForSeconds(victory.length/2); // ����� ���̸�ŭ ���
        }

        SceneManager.LoadScene(sceneName); // �� ��ȯ
    }
}