using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class StoryEffect : MonoBehaviour
{
    public TextMeshProUGUI textComponent;                   // 텍스트 변수
    public float EffectSpeed = 0.01f;                       // 텍스트 입력 간격
    private string fullText;
    

    void Start()
    {
        fullText = textComponent.text;                      // 텍스트 문자열 저장
        textComponent.text = "";
        StartCoroutine(TypeText());                         // 텍스트 입력 작업 시작
    }

    IEnumerator TypeText()                                  // 텍스트 한 글자씩 타이핑
    {
        foreach (char c in fullText.ToCharArray())          // 텍스트 문자열 범위만큼 반복
        {
            textComponent.text += c;                        // 한 글자씩 추가 후 작성
            yield return new WaitForSecondsRealtime(EffectSpeed);   // 0.05초 대기 후 다음 문자 추가
        }
    }
}