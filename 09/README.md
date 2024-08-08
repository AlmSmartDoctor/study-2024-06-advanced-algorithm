# Ch 25. 상호 배타적 집합 & Ch 26. 트라이

> 발표일 `24.08.09`
>
> 발표자 `서형석`

<br/>

## 상호 배타적 집합 (유니온 파인드)

> ex. 오리엔테이션에서 같은 혈액형끼리 헤쳐 모여! 한다면?
-  A, B, AB, O형으로 나눠지고 각 그룹엔 서로 다른 혈액형이 없음

같은 특성끼리 서로 뭉친 집합이 있는데, 공통 원소가 없는 집합을 상호 배타적 집합!

이때 쓰이는 자료구조를 유니온 파인드!

<br/>

### 구현

필요한 연산
- 초기화 - n개 원소가 각각의 집합에 포함되어 있도록 초기화
- 합치기(union) - 두 원소 a, b가 주어질 때 이들이 속한 두 집합을 하나로 합침
- 찾기(find) - 어떤 원소 a가 주어질 때 이 원소가 속한 집합을 반환

배열로 구현: belongsTo[i] = i번 원소가 속하는 집합의 번호
- init - 한 번 순회. O(n)
- find - 랜덤 엑세스. O(1)
- union - 한 쪽 집합을 모두 순회하며 다른 쪽 집합으로 옮김. O(n)

트리로 구현


![image](https://github.com/user-attachments/assets/2f28ecd5-6c57-4b0e-a74e-c78766162aab)




### 최적화

![image](https://github.com/user-attachments/assets/45159a46-ca21-4ca2-b34e-9236d625115a)







## 트라이

![image](https://github.com/user-attachments/assets/b27707bd-cc85-473b-8154-efdce044fec0)


![image](https://github.com/user-attachments/assets/c15f9a80-1ed4-4c9b-9259-35c1b5e3e0f3)


![image](https://github.com/user-attachments/assets/e19e652e-d5f1-4ba1-a92e-49eeea07b957)


![image](https://github.com/user-attachments/assets/c517c5d6-99bc-444c-aa1a-c6f00f8f57a6)


![image](https://github.com/user-attachments/assets/6a708ca6-068b-473f-8288-1359b2ad6b19)


![image](https://github.com/user-attachments/assets/b57c042c-7280-4b8f-a360-676c6348608c)


![image](https://github.com/user-attachments/assets/a6cb3e16-266e-4239-8b5d-46c1cda62667)
