# Ch 24. 구간 트리

> 발표일 `24.08.02`
>
> 발표자 `곽재영`

<br/>

## 구간 트리
구간 트리(Segment Tree)는 배열의 특정 구간에 대한 정보를 빠르게 처리하기 위해 사용되는 트리 자료 구조이다.

> ex) 어떤 배열의 a 인덱스 부터 b 인덱스 까지의 최소값을 구하려면?
>
> 가장 단순하게 생각해볼 수 있는 것은 a부터 b까지 순회하며 최소값 구하기 -> 시간복잡도 `O(n)`
>
> 하지만 n이 엄청 크고, 이런 조회를 k번 해야한다면? -> 시간복잡도 `O(kn)`

<br/>

vs **부분합**
![image](https://github.com/user-attachments/assets/4c42df89-5639-4f13-9c23-926317c602b1)


부분합을 사용하면 어떤 배열의 구간합을 구하는데 전처리 `O(n)`, 조회 `O(1)`으로 구할 수 있다. (4주차 참고)

하지만, 특정 구간에 대한 정보 중 합과 같은 단순한 정보만 다룰 수 있고, 최소값, 최대값, 최빈값 등은 다룰 수 없다.

또, 중간에 값이 업데이트가 될 때 마다 전처리 과정(`O(n)`)을 매번 거쳐야 한다.

<br/>

구간 트리의 기본적인 아이디어는 주어진 배열의 구간들을 표현하는 이진 트리를 만드는 것이다.

![image](https://github.com/user-attachments/assets/af3dfc5d-d91b-45dd-8c0d-faae75af3a36)

이때, 루트 노드는 해당 배열의 전체 구간을 나타내며, 각 노드의 자식 노드는 그 구간을 절반씩 나눈 구간을 나타낸다.

그리고, 구간 트리는 노드마다 해당 구간에 대한 정보를 저장해 둔다. 예를들어 구간의 최소치를 구하는 구간 트리는 해당 구간의 최소값을 각 노드에 저장해둔다.

이렇게 전처리가 되어있다면, 어떤 구간이 주어지더라도 이 구간을 구간 트리의 노드들의 합집합으로 표현할 수 있다.

<br/>

### 구현

특정 구간의 최소치를 찾는 구간 최소 쿼리(range minimum query, RMQ)를 구현해보자.

먼저, 구간 트리는 비교적 '꽉 찬' 이즌 트리이다. 따라서, 각 노드를 포인터로 연결된 객체로 표현하기보다 배열로 표현하는 것이 메모리를 더 절약할 수 있다.

루트 노드를 1번 원소, 노드 i의 왼쪽 자식과 오른쪽 자식 노드를 각각 2i, 2i + 1번 원소로 표현할 수 있기 때문이다.

<br/>

**초기화**

`init()`은 현재 구간을 두 개로 나눠 재귀 호출한 뒤, 두 구간의 최소치 중 더 작은 값을 선택해 해당 구간의 최소치를 계산한다.

```cpp
// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ{
    // 배열의 길이
    int n;
    // 각 구간의 최소치
    vector<int> rangeMin;
    RMQ(const vector<int>& array){
        n = array.size();
        rangeMin.resize(n * 4);
        init(array, 0, n-1, 1);
    }
    // node 노드가 array[left .. right] 배열을 표현할 때
    // node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
    int init(const vector<int>& array, int left, int right, int node){
        if(left == right)
            return rangeMin[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid +1, right, node * 2 + 1);
        return rangeMin[node] = min(leftMin, rightMin);
    }
};
```

> **시간 복잡도**
>
> 각 노드마다 걸리는 시간은 `O(1)`이고, 초기화 과정에서 각 노드를 딱 한 번 씩만 방문한다. 따라서, 초기화 과정에는 노드의 수와 같은 시간이 걸린다. -> `O(n)`

<br/>

**질의 처리(쿼리)**

질의 연산은 구간 트리에서의 순회를 응용해 간단하게 구현할 수 있다.

`query(left, right, node, nodeLeft, nodeRight) = node`가 표현하는 범위 `[nodeLeft, nodeRight]`와 우리가 최소치를 찾기 원하는 구간 `[left, right]`의 교집합의 최소 원소를 반환하는 재귀 함수이다.

이때, `query`는 다음과 같은 3가지 경우에 놓인다.

- 교집합이 공집합인 경우: 두 구간은 서로 겹치지 않기에, 반홥 값이 존재하지 않는다. 따라서, 반환 값이 무시되도록 아주 큰 값을 반환한다.
- 교집합이 `[nodeLeft, nodeRight]`인 경우: `[left, right]`가 노드가 표현하는 집합을 완전히 포함하는 경우이다. 이 노드에 미리 계산해 둔 최소치를 바로 반환하면 된다.
- 이 외의 모든 경우: 두 개의 자손 노드에 대해 `query()`를 재귀 호출한 뒤, 이 두 값 중 더 작은 값을 반환한다.


```cpp
const int _INT_MAX = numeric_limits<int>::max();

// 배열의 구간 최소 쿼리를 해결하기 위한 구간 트리의 구현
struct RMQ{
    // ..생략..
    // node가 표현하는 범위 array[nodeLeft .. nodeRight]가 주어질 때
    // 이 범위와 array[left .. right]의 교집합의 최소치를 구한다.
    int query(int left, int right, int node, int nodeLeft, int nodeRight){
        // 두 구간이 겹치지 않으면 아주 큰 값을 반환한다: 무시됨
        if (right < nodeLeft || nodeRight < left) return _INT_MAX;
        // node가 표현하는 범위가 array[left .. right]에 완전히 포함되는 경우
        if (left <= nodeLeft && nodeRight <= right)
            return rangeMin[node];
        // 양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) / 2;
        return min(query(left, right, node * 2, nodeLeft, mid),
                   query(left, right, node * 2 +1, mid+1, nodeRight));
    }
    // query()를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right){
        return query(left, right, 1, 0, n-1);
    }
};
```

> **시간 복잡도**
> 
> ![image](https://github.com/user-attachments/assets/8491c161-b040-4b13-93b5-de630fb7aa9b)
>
> 이 그림은 노드가 표현하는 구간과 최소치를 원하는 구간이 겹치는 형태를 보여준다.
>
> 노드가 표현하는 구간을 절반으로 나눠 재귀 호출을 했을 때, 해당 구간이 노드에 완전히 포함되거나 (전부 짙은 색) 아예 포함되지 않을 경우 (전부 옅은 색) 더 이상의 재귀 호출 없이 바로 종료된다.
>
> 그림 (b), (c), (d)에서는 재귀 호출했을 때 양쪽 중 하나는 반드시 바로 종료됨을 알 수 있고, 따라서 양쪽 재귀 호출 둘 중 하나도 바로 종료되지 않고 탐색이 계속 되기 위해서는 그림 (a)처럼 두 두간이 겹쳐야 한다.
>
> 그러나 이 경우 (a)에서 구간을 반으로 쪼갠 후에는 항상 그림 (c)나 (d)의 경우만 발생하기 때문에 이러한 경우는 최대 한 번 밖에 생기지 않는다.
>
> 따라서, 시간 복잡도는 `O(log n)`이다.

<br/>

**갱신**

특정 index의 값이 바뀌었을 경우는 어떻게 해야할까?

다시 초기화 과정을 거쳐 새로 트리를 생성할 수도 있겠지만, 그렇게 하지 않고 이 위치를 포함하는 노드들만 갱신해주면 `O(log n)`에 구간 트리를 갱신할 수 있을 것이다.

갱신 과정은 `query()`와 `init()`을 합친 것처럼 구현된다.

해당 노드가 표현하는 구간에 index가 포함되지 않는다면 그냥 무시하고, 포함된다면 재귀 호출 해서 두 자식 구간의 최소치를 계산한 뒤 다시 최소치를 구하면 된다.

```cpp
struct RMQ{
    // .. 생략 ..
    // array[index] = newValue로 바뀌었을 때 node를 루트로 하는
    // 구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
        // index가 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if (index < nodeLeft || nodeRight < index)
            return rangeMin[node];
        // 트리의 리프까지 내려온 경우
        if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
        int mid = (nodeLeft + nodeRight) / 2;
        return rangeMin[node] = min(
                                    update(index, newValue, node*2, nodeLeft, mid),
                                    update(index, newValue, node*2+1,mid+1, nodeRight));
    }
    // update()를 외부에서 호출하기 위한 인터페이스
    int update(int index, int newValue){
        return update(index, newValue, 1, 0, n-1);
    }
};
```

<br/>

## 펜윅 트리

펜윅 트리(Fenwick Tree)혹은 이진 인덱스 트리(binary indexed tree)는 구간 트리의 궁극적인 진화 형태이다.

펜윅 트리의 중요한 아이디어는 구간 합 대신 부분 합만을 빠르게 계산할 수 있는 자료 구조를 만들어도 구간 합을 계산할 수 있다는 것이다.

부분 합만을 계산한다고 했을 때, 구간 트리가 미리 계산해 저장하는 정보의 상당 수는 필요가 없다.

예를 들어 [8, 15] 구간의 구간 합은 부분 합만을 구한다면 필요가 없다. [0, 15] 값이 필요하다면 루트에 있는 값을 바로 사용할 테고, 다른 위치의 부분 합을 구할 때는 이 값을 쓸 수가 없다.

따라서 이런 식으로 하나의 구간 밑에 두 개의 작은 구간이 있을 때 이 두 구간 중 오른쪽 구간은 항상 지워도 된다.

![image](https://github.com/user-attachments/assets/26e58569-c08e-49c6-ac25-824c8ee8c57b)

이렇게 했을 때, 남은 구간의 수는 정확하게 n개이다. 구간 트리가 2n개의 구간을 저장하는 것에 비해 반으로 줄어들었다.

이때, 각 구간이 포함하는 오른쪽 끝 원소들을 보면 이들이 서로 모두 다르고, 펜윅 트리는 이를 이용해 1차원 배열 하나에 각 구간의 합을 저장한다.

> tree[i] = 오른쪽 끝 위치가 A[i]인 구간의 합

이렇게 해서 A[pos] 까지의 구간 합을 구하고 싶다면 pos에서 끝나는 구간의 합 tree[pos]를 답에 더하고, 남은 부분들을 왼쪽에서 찾아 더하면 된다.

<br/>

이제 문제는 pos에서 끝나는 구간 다음의 구간을 어떻게 찾을 것인가이다.

이를 위해 모든 원소의 인덱스를 1씩 더한 후 이진수로 표현해보면 다음과 같다.

![image](https://github.com/user-attachments/assets/8433aff3-dbcc-438d-bb46-598dfded80e0)

규칙: 오른쪽 끝 위치의 이진수 표현에서 마지막 비트를 지우면 다음 구간을 찾을 수 있다.

<br/>

### 구현

펜윅 트리를 처음 생성하면 모든 부분 합이 0으로 초기화되므로, 모든 원소가 0인 배열을 표현하게 된다.

펜윅 트리는 구간 트리처럼 모든 구간에 대해 답을 계산하지 않기 때문에 O(n)에 초기화하기가 불가능하다. 따라서 구간 트리의 갱신 연산처럼 각 위치의 값을 변경하는 연산을 통해 내용을 채워넣어야 한다.

펜윅 트리에서 배열의 값을 변경하는 것은 해당 위치의 값에 숫자를 더하고 빼는 것으로 구현한다. 즉, 해당 위치를 포함하는 모든 구간의 합에 숫자를 더하고 빼주면 된다.

> ex) A[5]를 3 늘리고 싶다면?
>
> A[5]를 포함하는 모든 구간의 합을 3씩 늘려주면 된다.
>
> 이때, tree[5], tree[6], tree[8], tree[16]이 A[5]를 포함하게 되고, 이 인덱스를 이진수로 표현하면 101, 110, 1000, 10000이다.
>
> 규칙은 맨 오른쪽에 있는 1인 비트를 스스로에게 더해주는 연산을 반복하는 것이다.

```cpp
// 펜윅 트리의 구현, 가상의 배열 A[]의 부분 합을
// 빠르게 구현할 수 있도록 한다. 초기화시에는 A[]의
// 원소가 전부 0이라고 생각한다.
struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) : tree(n + 1) {}
    // A[0..pos]의 부분 합을 구한다.
    int sum(int pos) {
        // 인덱스가 1부터 시작한다고 생각하자.
        ++pos;
        int ret = 0;
        while(pos > 0) {
            ret += tree[pos];
            // 다음 구간을 찾기 위해 최종 비트를 지운다.
            pos &= (pos - 1);
        }
        return ret;
    }
    // A[pos]에 val을 더한다.
    void add(int pos, int val) {
        ++pos;
        while(pos < tree.size()) {
            tree[pos] += val;
            pos += (pos & -pos);
        }
    }
};
```

두 연산의 시간 복잡도는 모두 `O(log n)`이다. 반복문이 수행될 때마다 트리의 한 층이 올라가는데, 트리의 높이는 항상 `O(log n)`이기 때문이다.

펜윅 트리의 구현은 매우 간결하기 때문에, 값이 업데이트 될 수 있는 배열의 구간 합을 구할 때는 구간 트리보다 펜윅 트리를 훨씬 자주 쓰게 된다.
