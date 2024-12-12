using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameDirector : MonoBehaviour
{
    GameObject HP_BarPlayer1;
    GameObject HP_BarPlayer2;
    public GameObject Canvas1PWin; // 1P 승리 이미지
    public GameObject Canvas2PWin; // 2P 승리 이미지
    public bool isPlayer1ShieldActive = false; // 플레이어1 쉴드 상태
    public bool isPlayer2ShieldActive = false; // 플레이어2 쉴드 상태
    private bool isGamePaused = false;         // 게임 정지 상태 확인용 플래그
    public AudioSource audioSource;
    public AudioClip victory;


    void Start()
    {
        this.HP_BarPlayer1 = GameObject.Find("HP_BarPlayer1"); // 플레이어1 체력바
        this.HP_BarPlayer2 = GameObject.Find("HP_BarPlayer2"); // 플레이어2 체력바
         // Hierarchy에서 이름으로 캔버스 가져오기
        Canvas1PWin = GameObject.Find("1p_win");
        Canvas2PWin = GameObject.Find("2p_win");
        // 초기 상태에서 승리 이미지는 비활성화
        if (Canvas1PWin != null) Canvas1PWin.SetActive(false); // 1P 승리 이미지 비활성화
        if (Canvas2PWin != null) Canvas2PWin.SetActive(false); // 2P 승리 이미지 비활성화
        
    }

    public void DecreaseHP1(float damage)
    {
        if (isPlayer1ShieldActive || isGamePaused) return; // 실드 활성화 상태 또는 게임 정지 시 무효화

        // 체력 감소
        this.HP_BarPlayer1.GetComponent<Image>().fillAmount -= damage;

        // 체력 0 체크
        if (this.HP_BarPlayer1.GetComponent<Image>().fillAmount <= 0)
        {
            ShowWinCanvas(2); // 2P 승리
        }
    }

    public void DecreaseHP2(float damage)
    {
        if (isPlayer2ShieldActive || isGamePaused) return; // 실드 활성화 상태 또는 게임 정지 시 무효화

        // 체력 감소
        this.HP_BarPlayer2.GetComponent<Image>().fillAmount -= damage;

        // 체력 0 체크
        if (this.HP_BarPlayer2.GetComponent<Image>().fillAmount <= 0)
        {
            ShowWinCanvas(1); // 1P 승리
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
        Time.timeScale = 0; // 게임 정지

        if (winner == 1 && Canvas1PWin != null)
        {
            Canvas1PWin.SetActive(true); // 1P 승리 이미지 활성화
            StartCoroutine(PlayVictoryAndTransition("EndScene1"));
        }
        else if (winner == 2 && Canvas2PWin != null)
        {
            Canvas2PWin.SetActive(true); // 2P 승리 이미지 활성화
            StartCoroutine(PlayVictoryAndTransition("EndScene2"));
        }
    }

    private IEnumerator PlayVictoryAndTransition(string sceneName)
    {
        Time.timeScale = 1; // 씬 전환 전 타임스케일 복구

        if (audioSource != null && victory != null)
        {
            audioSource.PlayOneShot(victory); // 승리 오디오 재생
            yield return new WaitForSeconds(victory.length/2); // 오디오 길이만큼 대기
        }

        SceneManager.LoadScene(sceneName); // 씬 전환
    }
}