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

find - 주어진 원소가 포함된 트리의 루트를 찾는 것.

- 모든 자식 노드가 부모 노드의 포인터를 가지고 있어야 함
- 루트는 자기 자신을 가리킴

union - 루트를 찾고, 한 쪽을 다른 한쪽의 자손으로 넣는 것.

***주의. 루트를 찾지 않으면 하나만 옮겨감 (25.1 - c)***


```cpp
코드 25.1 트리를 이용한 (단순한) 상호 배타적 집합 자료 구조의 구현
// 트리를 이용해 상호 배타적 집합을 구현
struct NaiveDisjointSet {
  vector<int> parent;
  NaiveDisjointSet(int n): parent(n) {
    for(int i = 0; i < n; ++i)
      parent[i] = i;
  }
  // u가 속한 트리의 루트의 번호를 반환
  int find(int u) const {
    if(u == parent[u]) return u;
    return find(parent[u]);
  }
  // u가 속한 트리와 v가 속한 트리를 합침
  void merge(int u, int v) {
    u = find(u); v = find(v);
    // u와 v가 이미 같은 트리에 속하는 경우를 걸러냄
    if(u == v) return;
    parent[u] = v;
  }
};
```

find - O(h), merge - O(h) (h < n)



### 최적화

랭크에 의한 합치기 최적화 (union-by-rank)

> 발생 가능한 문제: 연산 순서에 따라 트리가 한쪽으로 기울어질 수 있음 (연결 리스트 생성) 
- find: O(n), union: O(n)

> 두 트리를 합칠 때 항상 높이가 더 낮은 트리를 더 높은 트리 밑에 집어넣어 높이가 높아지는 상황을 방지
- rank[] - 해당 노드가 한 트리의 루트인 경우 해당 트리의 높이를 저장
- 노드를 합칠 때 높이를 비교, 낮은 쪽을 높은 트리의 서브트리로 포함. 같은 경우에만 높이를 1 늘려줌
- 트리의 높이는 합쳐진 두 트리의 높이가 같을 때만 증가. 높이 h 트리가 생기기 위해선 h - 1인 두 개의 트리가 합쳐져야 함. 
- find: O(lgn), union: O(lgn)

```cpp
코드 25.1 트리를 이용한 (단순한) 상호 배타적 집합 자료 구조의 구현
struct OptimizedDisjointSet {
  vector<int> parent, rank;
  OptimizedDisjointSet(int n): parent(n), rank(n, 1) {
    for(int i = 0; i < n; ++i)
      parent[i] = i;
  }
  // u가 속한 트리의 루트의 번호를 반환
  int find(int u) const {
    if(u == parent[u]) return u;
    // 경로 압축 최적화
    return parent[u] = find(parent[u]);
  }
  // u가 속한 트리와 v가 속한 트리를 합침
  void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return;
    // 랭크에 의한 합치기
    if (rank[u] > rank[v]) swap(u, v);
    // u를 v의 자식으로 넣음
    parent[u] = v;
    if (rank[u] == rank[v]) ++rank[v]
  }
};
```

경로 압축 최적화 (path compression)

> find() 연산의 중복된 계산을 줄임
- 노드 u의 parent를 찾으면 parent[u]에 저장.
- 재귀적 구현으로 find(u)를 호출하면 경로 상의 모든 노드들에도 적용
- 다음 find(u) 호출시 바로 루트를 찾을 수 있다

- find - O(a(n)), union - O(a(n)): 현실적인 모든 입력에 대해 상수 시간

![image](https://github.com/user-attachments/assets/45159a46-ca21-4ca2-b34e-9236d625115a)







## 트라이

![image](https://github.com/user-attachments/assets/b27707bd-cc85-473b-8154-efdce044fec0)


![image](https://github.com/user-attachments/assets/c15f9a80-1ed4-4c9b-9259-35c1b5e3e0f3)


![image](https://github.com/user-attachments/assets/e19e652e-d5f1-4ba1-a92e-49eeea07b957)


![image](https://github.com/user-attachments/assets/c517c5d6-99bc-444c-aa1a-c6f00f8f57a6)


![image](https://github.com/user-attachments/assets/6a708ca6-068b-473f-8288-1359b2ad6b19)


![image](https://github.com/user-attachments/assets/b57c042c-7280-4b8f-a360-676c6348608c)


![image](https://github.com/user-attachments/assets/a6cb3e16-266e-4239-8b5d-46c1cda62667)
