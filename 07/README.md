# Ch 21. 트리의 구현과 순회 & Ch 22. 이진 검색 트리

> 발표일 `24.07.26`
>
> 발표자 `김태훈`

## 트리

- 선형으로 표현하기 힘든, 계층 구조가 있는 경우의 자료를 표현

### 정의 및 용어
- 구성 요소
  ![image](https://github.com/user-attachments/assets/1550fb3c-6080-48c1-a418-4d2eb06e0b52)
  - 노드(node)
    - 부모(parent)
    - 자식(child)
    - 형제(sibling)
    - 선조(ancestor)
    - 자손(descendant)
  - 간선(edge)
  - 루트(root)
  - 잎(leaf)
  - 서브트리(subtree)
- 속성
  - 깊이(depth)
  - 높이(height)
    ```
    class TreeNode {
      constructor(key, value = key, parent = null) {
        this.key = key;
        this.value = value;
        this.parent = parent;
        this.children = [];
      }
    
      get isLeaf() {
        return this.children.length === 0;
      }
    
      get hasChildren() {
        return !this.isLeaf;
      }
    }
    ```
  
### 트리의 순회
- 재귀적 속성을 이용
- n개의 노드에 대한 순회에는 O(n)의 시간이 필요
- 전위 순회(preorder traverse)
  ![image](https://github.com/user-attachments/assets/9bf98f36-e4ed-40fc-adc3-2c3eda65b8ec)

- 중위 순회(inorder traverse)
  ![image](https://github.com/user-attachments/assets/55ff87dc-e2a7-4bb8-a216-a1f422d48f77)

- 후위 순회(postorder traverse)
  ![image](https://github.com/user-attachments/assets/54565854-8b2e-45a5-b042-a640f80e0f2a)


### 예제-요새(FORTRESS)
https://algospot.com/judge/problem/read/FORTRESS
- 트리로 표현
- 가장 긴 경로 찾기
![image](https://github.com/user-attachments/assets/cdd9bd4f-8c06-4149-959a-aafd9a848939)


---
## 이진 검색 트리(binary search tree)
![image](https://github.com/user-attachments/assets/ea6c8c2b-7550-48f6-9dd6-4bcf7d27bbcc)
- 검색 트리
- 이진 트리
  - 검색
   - https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
  - 조작
   - https://www.geeksforgeeks.org/insertion-in-binary-search-tree/
   - https://www.geeksforgeeks.org/deletion-in-binary-search-tree/

 ![image](https://github.com/user-attachments/assets/1dc8ce94-fee7-48f1-b553-00575439bc8d)

x보다 작은 원소의 수 찾기 / k번째 원소 찾기 등은 표준 라이브러리에서 거의 지원하지 않음.
이진 검색 트리의 시간 복잡도는 O(h-트리의 높이), 최소 높이는 O(lgN), 기울어지지 않는 것이 중요
  
### 균형 잡힌 이진 검색 트리(balanced binary search tree)
- 트리의 높이를 항상 O(lgN)이 되도록 유지
- red-black tree
  ![image](https://github.com/user-attachments/assets/921810d6-7cae-4627-89c8-2629eb85cfc2)
  1. 노드는 레드 혹은 블랙 중의 하나이다.
  2. 루트 노드는 블랙이다.
  3. 모든 리프 노드들(NIL)은 블랙이다.
  4. 레드 노드의 자식노드 양쪽은 언제나 모두 블랙이다. (즉, 레드 노드는 연달아 나타날 수 없으며, 블랙 노드만이 레드 노드의 부모 노드가 될 수 있다)
  5. 어떤 노드로부터 시작되어 그에 속한 하위 리프 노드에 도달하는 모든 경로에는 리프 노드를 제외하면 모두 같은 개수의 블랙 노드가 있다.
  **루트 노드부터 가장 먼 잎노드 경로까지의 거리가, 가장 가까운 잎노드 경로까지의 거리의 두 배 보다 항상 작다.**

### 트립(treap)
트리의 형태가 난수에 의해 임의로 결정, 트리 높이의 기대치는 일정
새 노드가 추가될 때 마다 우선순위(priority) 부여, 항상 부모의 우선순위가 자식의 우선순위보다 높은 이진 검색 트리를 만듦.
tree + heap = treap

![image](https://github.com/user-attachments/assets/b2e90581-8bb8-44bc-b1d7-b6044e8be6b0)
- 추가
  ![image](https://github.com/user-attachments/assets/21596a48-d010-4d4a-8f30-5f3abdc2a6c5)
- 삭제
  ![image](https://github.com/user-attachments/assets/cf2ca50e-f30d-4407-8fc8-8ea78753a5a4)




