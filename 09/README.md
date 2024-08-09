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

***랭크에 의한 합치기 최적화 (union-by-rank)***

> 발생 가능한 문제: 연산 순서에 따라 트리가 한쪽으로 기울어질 수 있음 (연결 리스트 생성) 
- find: O(n), union: O(n)

> 두 트리를 합칠 때 항상 높이가 더 낮은 트리를 더 높은 트리 밑에 집어넣어 높이가 높아지는 상황을 방지
- rank[] - 해당 노드가 한 트리의 루트인 경우 해당 트리의 높이를 저장
- 노드를 합칠 때 높이를 비교, 낮은 쪽을 높은 트리의 서브트리로 포함. 같은 경우에만 높이를 1 늘려줌
- 트리의 높이는 합쳐진 두 트리의 높이가 같을 때만 증가. 높이 h 트리가 생기기 위해선 h - 1인 두 개의 트리가 합쳐져야 함. 
- find: O(lgn), union: O(lgn)

```cpp
코드 25.2 최적화된 상호 배타적 집합의 구현
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

***경로 압축 최적화 (path compression)***

> find() 연산의 중복된 계산을 줄임
- 노드 u의 parent를 찾으면 parent[u]에 저장.
- 재귀적 구현으로 find(u)를 호출하면 경로 상의 모든 노드들에도 적용
- 다음 find(u) 호출시 바로 루트를 찾을 수 있다
- find - O(a(n)), union - O(a(n)): 현실적인 모든 입력에 대해 상수 시간

![image](https://github.com/user-attachments/assets/45159a46-ca21-4ca2-b34e-9236d625115a)

<br/>
<br/>

## 트라이

문자열을 비교할 경우, 최악의 경우 문자열 길이에 비례하는 시간이 걸림

문자열을 키로 갖는 N개의 원소를 가진 BST에서 원소를 찾으면, O(lgN)에 문자열의 최대 길이 M을 곱한 O(MlgN)이 됨

트라이를 사용하면, 문자열 집합 내 원하는 원소를 찾는 작업을 O(M)만에 할 수 있다.

<br>


![image](https://github.com/user-attachments/assets/b27707bd-cc85-473b-8154-efdce044fec0)

문자열 집합 S = {"BE", "BET", "BUS", "TEA", "TEN"}를 저장하는 트라이

- 문자열의 접두사들에 대응하는 노드들이 연결된 트리
- 한 접두사의 맨 뒤에 글자를 붙여 다른 접두사를 얻을 수 있으면 부모 자식 관계로 연결
- 노드를 연결하는 간선은 덧붙인 글자에 대응.
- 루트 0, 깊이 1당 길이 1
- 짙은 회색 노드는 종료 노드로, 해당 문자열이 집합에 포함됨

<br/>

### 구현

루트에서 한 노드까지 내려가는 경로에서 만나는 글자를 모으면, 해당 노드의 접두사를 얻을 수 있음

각 노드에 대응하는 문자열을 저장할 필요가 없다!

트라이의 노드 객체 구성
- 자손 노드들을 가리키는 포인터 목록 (고정 길이 배열로 구현. 알파벳이면 26)
- 종료 노드인지 나타내는 불린 값 변수

메모리를 엄청나게 낭비하지만, 다음 노드를 찾는 과정에서 어떤 탐색도 필요하지 않다!


```cpp
코드 26.1 트라이의 노드를 표현하는 객체의 선언
const int ALPHABETS = 26;
int toNumber(char ch) { return ch - 'A'}
// 트라이의 한 노드를 나타내는 객체
struct TrieNode {
  TrieNode* children[ALPHABETS];
  bool terminal;
  TrieNode() : terminal(false) {
    memset(children, 0, sizeof(children));
  }

  // 이 노드를 루트로 하는 트라이에 문자열 key를 추가
  void insert(const char* key) {
    // 문자열이 끝나면 terminal만 참으로 바꾸고 종료
    if(*key == 0) terminal = true;
    else {
      int next = toNumber(*key);
      // 해당 자식 노드가 없다면 생성
      if(children[next] == NULL)
        children[next] == new TrieNode();
      // 해당 자식 노드를 재귀호출
      children[next] -> insert(key + 1);
    }
  }

  // 이 노드를 루트로 하는 트라이에 문자열 key와 대응되는 노드를 찾음
  // 없으면 NULL을 반환
  TrieNode* find(const char* key) {
    if(*key == 0) return this;
    int next = toNumber(*key);
    if(children[next] == NULL) return NULL;
    return children[next] -> find(key + 1)
  }
}
```

> find는 찾아낸 문자열이 대응되는 노드가 종료 노드인지 확인하지 않음. 
- 해당 문자열이 진짜 존재하는지 알려면 반환된 terminal이 true인지 확인해야함.
- 종료 노드가 아닌 노드를 반환할 때 장점은, 문자열의 첫 일부만 가지고도 이 문자열로 시작하는 키가 있는지 확인할 수 있음
- 문자열이 입력되는 중간에 자동 완성하는 프로그램을 구현할 때 아주 유용

> 시간복잡도: find, insert 모두 O(M)
- 문자열의 길이만큼 재귀 호출을 수행
- 트라이에 포함된 다른 문자열의 개수와는 상관이 없음
- 빠른 속도가 필요한 검색 엔진이나 기타 문자열 처리 프로그램에서 자주 사용


문제는 필요 공간이 너무 큼. 
- 알파벳을 저장하면 각 노드는 26개 포인터 저장
- 포인터 크기가 8바이트인 64비트 아키텍처면, 노드 하나 표현에 200여 바이트
- 문자열들이 접두사를 공유하지 않는 최악의 경우, 문자열 길이의 합이 1백만이면 200MB 필요.
- 따라서 트라이는 다루는 문자열의 개수가 그렇게 많지 않을 때 사용됨

<br/>

### 접미사 트리
여러 문자열 대신 한 문자열 S의 모든 접미사를 넣을 수 있음. 이를 접미사 트라이라고 함(suffix trie)

![image](https://github.com/user-attachments/assets/c15f9a80-1ed4-4c9b-9259-35c1b5e3e0f3)

- 문자열의 모든 부분 문자열은 어떤 접미사의 접두사이므로, 접미사 트라이는 한 문자열의 모든 부분 문자열을 저장함.
- 접미사 트라이에서의 검색을 이용하면 어떤 부분 문자열도 빠르게 찾아낼 수 있음.
- 너무 많은 메모리 사용. 원 문자열이 길이가 1000만 되도 접미사 길이의 합은 1000*999/2 ~ 50만. 50만개의 노드를 갖는 트라이는 100MB. 1kB -> 100MB, 십만배

이를 해결하는게 접미사 트리

![image](https://github.com/user-attachments/assets/e19e652e-d5f1-4ba1-a92e-49eeea07b957)
- 접미사 트라이의 많은 부분이 분기 없이 일자로 구성되는 것에 착안
- 각 간선이 문자열의 한 글자가 아니라 여러 글자에 대응시켜, 긴 일자 경로를 압축함
- 전체 노드 개수는 최대 O(N)

그러나 접미사 트리를 만드는 Cost가 큼
- 단순한 알고리즘은 O(N^2), 효율적인 알고리즘은 너무 복잡
- 유용성에 비해 굉장히 제한된 경우에만 사용. 많은 경우 20장의 접미사 배열을 대신 사용.


<br/>

### 트라이를 이용한 다중 문자열 검색

다중 문자열 검색
> 한 문자열 내부에서 서로 다른 여러 개의 부분 문자열을 찾는 문제

> ex. H = "CACACHEFCACHY"안에서 "CACHE", "HE", "CHEF", "ACHY의 출현 위치를 모두 계산

- KMP 문자열 검색 알고리즘을 이용해 각 문자열을 순서대로 찾을 수 있음
- 하나당 수행시간은 H 문자열 길이에 비례하므로 매우 빠르지만, 바늘 문자열 개수만큼 실행해야 함.

이를 KMP의 부분 일치 테이블과 트라이를 활용해 한 번에 찾을 수 있음

KMP 동작 원리
- 바늘 문자열의 각 접두사마다, 이 접두사의 접두사이면서 접미사도 되는 문자열의 최대 길이를 계산
- 대응되지 않으면, 일치하지 않는 부분을 건너뜀
- ex. "CACHE"를 찾는데 "CAC"까지만 일치했다면, CAC의 접두사이자 접미사인 C를 찾아서, A를 건너뛰고 그 다음 C부터 비교
- 따라서 "CACACHE"같은 문자열에서 "CACHE"를 찾을 때도 짚더미의 각 문자를 한 번만 보고 모든 출현 위치를 찾아낼 수 있음
<br/>

바늘 문자열의 실패 함수 정보

![image](https://github.com/user-attachments/assets/c517c5d6-99bc-444c-aa1a-c6f00f8f57a6)

- 오른쪽 실선 화살표 - 대응이 성공했을 경우 움직일 상태
- 왼쪽 점선 화살표 - 대응에 실패했을 떄 움직일 상태
- ex. "CAC" 상태에서 다음 글자가 H면 "CACH"로 이동, H가 아니면 C로 돌아와 다음 글자가 A인지 비교

<br/>
이때 각 바늘 문자열에서 겹치는 접두사를 합쳐 하나로 만들 수 있음

![image](https://github.com/user-attachments/assets/6a708ca6-068b-473f-8288-1359b2ad6b19)
이를 활용하면 모든 바늘 문자열을 한꺼번에 찾을 수 있다!

<br/>

실패 함수를 다음과 같이 정의
> failure(s) = s의 접미사이면서 트라이에 포함된 가장 긴 문자열까지 가는 화살표

![image](https://github.com/user-attachments/assets/b57c042c-7280-4b8f-a360-676c6348608c)

이와 같은 실패 함수를 전처리에서 만들고, 짚더미 문자열의 글자를 순회하며 트라이의 상태를 서로 오가면

모든 바늘 문자열에 대해 동시에 KMP 알고리즘을 수행하는 것과 같은 효과를 얻음

이를 아호-코라식 (Aho-Corasick) 문자열 검색 알고리즘이라고 하고, 긴 문서에서 많은 문자열을 동시에 찾아야 하는 검색 엔진 등에서 유용하게 사용됨