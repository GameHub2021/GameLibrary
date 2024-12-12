using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class StoryEffect : MonoBehaviour
{
    public TextMeshProUGUI textComponent;                   // �ؽ�Ʈ ����
    public float EffectSpeed = 0.01f;                       // �ؽ�Ʈ �Է� ����
    private string fullText;
    

    void Start()
    {
        fullText = textComponent.text;                      // �ؽ�Ʈ ���ڿ� ����
        textComponent.text = "";
        StartCoroutine(TypeText());                         // �ؽ�Ʈ �Է� �۾� ����
    }

    IEnumerator TypeText()                                  // �ؽ�Ʈ �� ���ھ� Ÿ����
    {
        foreach (char c in fullText.ToCharArray())          // �ؽ�Ʈ ���ڿ� ������ŭ �ݺ�
        {
            textComponent.text += c;                        // �� ���ھ� �߰� �� �ۼ�
            yield return new WaitForSecondsRealtime(EffectSpeed);   // 0.05�� ��� �� ���� ���� �߰�
        }
    }
}